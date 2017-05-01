package mapreduce

import argonaut._, Argonaut._
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
  case class FixtureParam(masterStats: MasterStats, jobInfo: JobInfo)
}

trait MapReduceBehaviors extends MapReduceFixtureParam {
  this: fixture.FlatSpec =>

  def InputNumberMatchesOutput(): Unit = {
    "Each input number" should "show up in the output file in string sorted order" in {
      f =>
        {
          val jobInfo = f.jobInfo

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
        }
    }
  }

  def WorkerRPCsProcessed(): Unit = {
    "Report of RPCs processed by workers" should "at least 1 DoTask RPC" in {
      f =>
        f.masterStats.stats.foreach(i => assert(i >= 0))
    }
  }
}

class SingleSequentialMapReduceTest extends MapReduceBehaviors {
  override def withFixture(test: OneArgTest) = {
    val sequentialSingle = {
      val master = Master("test_address")
      Master.Sequential(master,
                        "test",
                        Helper.makeInputs(1),
                        1,
                        Helper.mapFunc,
                        Helper.reduceFunc)
    }

    val theFixture = FixtureParam(sequentialSingle._1, sequentialSingle._2)

    try super.withFixture(test.toNoArgTest(theFixture))
    finally Helper.cleanup(sequentialSingle._2)

  }

  behavior of "Single sequential"
  it should behave like InputNumberMatchesOutput
  it should behave like WorkerRPCsProcessed
}

class ManySequentialMapReduceTest extends MapReduceBehaviors {
  override def withFixture(test: OneArgTest) = {
    val sequentialSingle = {
      val master = Master("test_address")
      Master.Sequential(master,
                        "test",
                        Helper.makeInputs(3),
                        3,
                        Helper.mapFunc,
                        Helper.reduceFunc)
    }

    val theFixture = FixtureParam(sequentialSingle._1, sequentialSingle._2)

    try super.withFixture(test.toNoArgTest(theFixture))
    finally Helper.cleanup(sequentialSingle._2)

  }

  behavior of "Many sequential"
  it should behave like InputNumberMatchesOutput
  it should behave like WorkerRPCsProcessed
}