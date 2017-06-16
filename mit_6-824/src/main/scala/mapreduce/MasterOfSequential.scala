package mapreduce

import java.io.File

import akka.actor.{ActorSystem, PoisonPill, Props}
import akka.pattern.ask
import akka.util.Timeout
import com.typesafe.config.ConfigFactory

import scala.concurrent.Await
import scala.concurrent.duration._
import mapreduce.Common.{mapPhase, mergeName, reducePhase, MapFunc, ReduceFunc}
import mapreduce.CommonMap.doMap
import mapreduce.CommonReduce.doReduce

/**
  * Created by chaomai on 07/05/2017.
  */
class MasterOfSequential(address: String) extends Master(address) {
  override def receive: Receive = {
    case RunArgs(jobName, files, nReduce, mapF, reduceF) => {
      val jobInfo = JobInfo(jobName, files, nReduce)

      val r = runner(
        address,
        jobInfo, {
          case `mapPhase` =>
            files.indices.foreach(i =>
              doMap(jobName, i, files(i), nReduce, mapF))

          case `reducePhase` =>
            (0 until nReduce).foreach(
              i =>
                doReduce(jobName,
                         i,
                         mergeName(jobName, i),
                         files.length,
                         reduceF))
        }
      ) _

      val jobStats = r(() => JobStats(List(files.length + nReduce), jobInfo))
      val m = MasterInfo(address, self)

      sender ! (m, jobStats)
    }
  }
}

object MasterOfSequential {
  def run(masterAddress: String,
          jobName: String,
          files: List[String],
          nReduce: Int,
          mapF: MapFunc,
          reduceF: ReduceFunc): (MasterInfo, JobStats) = {
    val confFile =
      getClass.getClassLoader.getResource("master.conf").getFile
    val conf = ConfigFactory.parseFile(new File(confFile))
    val system = ActorSystem("MapReduce", conf)
    val master = system.actorOf(Props(new MasterOfSequential(masterAddress)),
                                name = "master")

    implicit val timeout = Timeout(5 seconds)
    val future = master ? RunArgs(jobName, files, nReduce, mapF, reduceF)
    val ret =
      Await.result(future, Duration.Inf).asInstanceOf[(MasterInfo, JobStats)]
    master ! PoisonPill

    ret
  }
}
