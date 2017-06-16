package mapreduce

import argonaut._
import Argonaut._
import better.files._
import mapreduce.Common._
import org.scalatest._

/**
  * Created by chaomai on 11/04/2017.
  */
object Helper {
  val nNumber = 1000
  val nMap = 100
  val nReduce = 50

  def makeInputs(n: Int): List[String] = {
    val names = (0 until n).map("824-mrinput-%d.txt".format(_)).toList
    val nums = names.zipWithIndex.map(p =>
      (p._1, p._2 * (nNumber / n) until (p._2 + 1) * (nNumber / n)))

    nums.foreach(p => {
      p._2.foreach(i => File(p._1).appendLine(i.toString))
    })

    names
  }

  def cleanup(jobInfo: JobInfo): Unit = {
    jobInfo.files.foreach(f => File(f).delete())
    Master.cleanupFiles(jobInfo)
  }

  def mapFunc(file: String, value: String): List[KeyValue] = {
    debug("Map %s", value.toString)
    value.split(" ").map(w => KeyValue(w, "")).toList
  }

  def reduceFunc(key: String, values: List[String]): String = {
    values.foreach(debug("Reduce %s %s", key, _))
    ""
  }
}

trait UnitSpec extends fixture.FlatSpec

trait MapReduceFixtureParam extends UnitSpec {
  case class FixtureParam(jobStats: JobStats)
}

trait MapReduceBehaviors extends MapReduceFixtureParam {
  this: fixture.FlatSpec =>
  def InputNumberMatchesOutput(): Unit = {
    "Each input number" should "show up in the output file in string sorted order" in {
      f =>
        {
          val jobInfo = f.jobStats.jobInfo

          val lines = jobInfo.files
            .flatMap(filename =>
              File(filename).lines.foldRight(Nil: List[String])((l, acc) =>
                List(l) ++ acc))
            .sortBy(x => x)

          val mappedRet =
            (0 until jobInfo.nReduce)
              .flatMap(i => File(mergeName(jobInfo.jobName, i)).lines)
              .map(l => l.decodeOption[KeyValue].get)
              .toList
              .sortBy(x => x.key)

          assert(lines.length == Helper.nNumber)
          assert(mappedRet.length == Helper.nNumber)

          (lines zip mappedRet).foreach(e => assert(e._1 == e._2.key))
          f.jobStats.stats.foreach(i => assert(i >= 0))
        }
    }
  }
}

class TestSequentialSingle extends MapReduceBehaviors {
  override def withFixture(test: OneArgTest): Outcome = {
    val (_, jobStats) =
      MasterOfSequential.run("test_address",
                             "test",
                             Helper.makeInputs(1),
                             1,
                             Helper.mapFunc,
                             Helper.reduceFunc)

    val theFixture = FixtureParam(jobStats)

    try super.withFixture(test.toNoArgTest(theFixture))
    finally Helper.cleanup(jobStats.jobInfo)
  }

  behavior of "Sequential Single"
  it should behave like InputNumberMatchesOutput
}

class TestSequentialMany extends MapReduceBehaviors {
  override def withFixture(test: OneArgTest): Outcome = {
    val (_, jobStats) =
      MasterOfSequential.run("test_address",
                             "test",
                             Helper.makeInputs(5),
                             3,
                             Helper.mapFunc,
                             Helper.reduceFunc)

    val theFixture = FixtureParam(jobStats)

    try super.withFixture(test.toNoArgTest(theFixture))
    finally Helper.cleanup(jobStats.jobInfo)
  }

  behavior of "Sequential Many"
  it should behave like InputNumberMatchesOutput
}

class TestBasic extends MapReduceBehaviors {
  override def withFixture(test: OneArgTest): Outcome = {
    val (master, jobStats) =
      MasterOfDistributed.run("test_address",
                                                     "test",
                                                     Helper.makeInputs(5),
                                                     3,
                                                     Helper.mapFunc,
                                                     Helper.reduceFunc)

    Worker.runWorker(master.actor.path, "worker1", -1)
    Worker.runWorker(master.actor.path, "worker2", -1)

//    val theFixture = FixtureParam(jobStats)
//
//    try super.withFixture(test.toNoArgTest(theFixture))
//    finally Helper.cleanup(jobStats.jobInfo)
  }
//
//  behavior of "Distribute Basic"
//  it should behave like InputNumberMatchesOutput
}

//class TestOneFailure extends MapReduceBehaviors {
//  override def withFixture(test: OneArgTest): Outcome = {
//    val (master, jobStats) = MasterOfDistributed.run("test_address",
//                                                     "test",
//                                                     Helper.makeInputs(5),
//                                                     Helper.nReduce,
//                                                     Helper.mapFunc,
//                                                     Helper.reduceFunc)
//
//    Worker.runWorker(master.actor.path, "worker1", -1)
//    Worker.runWorker(master.actor.path, "worker2", 10)
//
//    val theFixture = FixtureParam(jobStats)
//
//    try super.withFixture(test.toNoArgTest(theFixture))
//    finally Helper.cleanup(jobStats.jobInfo)
//  }
//
//  behavior of "Distribute One Failure"
//  it should behave like InputNumberMatchesOutput
//}
//
//class TestManyFailure extends MapReduceBehaviors {
//  override def withFixture(test: OneArgTest): Outcome = {
//    val (master, jobStats) = MasterOfDistributed.run("test_address",
//                                                     "test",
//                                                     Helper.makeInputs(5),
//                                                     Helper.nReduce,
//                                                     Helper.mapFunc,
//                                                     Helper.reduceFunc)
//
//    Worker.runWorker(master.actor.path, "worker1", -1)
//    Thread.sleep(2000)
//
//    Worker.runWorker(master.actor.path, "worker2", 10)
//    Thread.sleep(2000)
//
//    Worker.runWorker(master.actor.path, "worker3", 10)
//    Thread.sleep(2000)
//
//    val theFixture = FixtureParam(jobStats)
//
//    try super.withFixture(test.toNoArgTest(theFixture))
//    finally Helper.cleanup(jobStats.jobInfo)
//  }
//
//  behavior of "Distribute Many Failure"
//  it should behave like InputNumberMatchesOutput
//}
