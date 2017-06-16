package mapreduce

import argonaut._
import Argonaut._
import akka.actor.{Actor, ActorRef}
import akka.event.Logging
import better.files._
import mapreduce.Common.{
  debug,
  mapPhase,
  mergeName,
  reduceName,
  reducePhase,
  KeyValue,
  Phase
}

/**
  * Created by chaomai on 07/05/2017.
  */
case class MasterInfo(address: String, actor: ActorRef)
case class JobStats(stats: List[Int], jobInfo: JobInfo)
case class JobInfo(jobName: String, files: List[String], nReduce: Int)

abstract class Master(val address: String) extends Actor {
  val log = Logging(context.system, this)

  def runner(masterAddress: String, jobInfo: JobInfo, schedule: Phase => Unit)(
      finish: () => JobStats): JobStats = {
    log.info(
      "%s: Starting Map/Reduce task %s".format(self.path.address.toString,
                                               jobInfo.jobName))

    schedule(mapPhase)
    schedule(reducePhase)
    merge(jobInfo)

    log.info(
      "%s: Map/Reduce task completed\n".format(self.path.address.toString))

    finish()
  }

  def merge(jobInfo: JobInfo): Unit = {
    debug("Merge phase")

    val mergedFile = File("mrtmp." + jobInfo.jobName)

    (0 until jobInfo.nReduce)
      .map(mergeName(jobInfo.jobName, _))
      .map(File(_))
      .foldRight(Nil: List[KeyValue])((f, acc) =>
        f.lines.map(l => l.decodeOption[KeyValue].get).toList ++ acc)
      .sortBy(_.key)
      .foreach(kv => mergedFile.appendLine("%s: %s".format(kv.key, kv.value)))
  }
}

object Master {
  def cleanupFiles(jobInfo: JobInfo): Unit = {
    def removeFile(f: String): Unit = File(f).delete()

    for {
      i <- jobInfo.files.indices
      j <- 0 until jobInfo.nReduce
    } yield removeFile(reduceName(jobInfo.jobName, i, j))

    for {
      i <- 0 until jobInfo.nReduce
    } yield removeFile(mergeName(jobInfo.jobName, i))

    removeFile("mrtmp." + jobInfo.jobName)
  }
}
