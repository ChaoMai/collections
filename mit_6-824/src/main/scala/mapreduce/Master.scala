package mapreduce

import argonaut._, Argonaut._
import better.files._
import mapreduce.Common._
import mapreduce.CommonMap._
import mapreduce.CommonReduce._

/**
  * Created by chaomai on 11/04/2017.
  */
case class Master(address: String)

case class MasterStats(stats: List[Int])

case class JobInfo(jobName: String, files: List[String], nReduce: Int)

object Master {
  def Sequential(
      master: Master,
      jobName: String,
      files: List[String],
      nReduce: Int,
      mapF: (String, String) => List[KeyValue],
      reduceF: (String, List[String]) => String): (MasterStats, JobInfo) = {
    val jobInfo = JobInfo(jobName, files, nReduce)
    val r = run(
      master,
      jobInfo, {
        case `mapPhase` =>
          @annotation.tailrec
          def loop(i: Int, f: List[String]): Unit = f match {
            case Nil => Nil
            case h :: t => {
              doMap(jobName, i, h, nReduce, mapF)
              loop(i + 1, t)
            }
          }

          loop(0, files)

        case `reducePhase` =>
          (0 until nReduce).foreach(i =>
            doReduce(jobName, i, mergeName(jobName, i), files.length, reduceF))
      }
    ) _

    (r(() => MasterStats(List(files.length + nReduce))), jobInfo)
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

  def cleanupFiles(jobInfo: JobInfo): Unit = {
    def removeFile(f: String): Unit = File(f).delete()

    for {
      i <- jobInfo.files.indices
      j <- 0 until jobInfo.nReduce
    } yield removeFile(reduceName(jobInfo.jobName, i, j))

    for {
      i <- 0 until jobInfo.nReduce
    } yield removeFile(mergeName(jobInfo.jobName, i))

//    removeFile("mrtmp." + jobInfo.jobName)
  }

  def run(master: Master, jobInfo: JobInfo, schedule: String => Unit)(
      finish: () => MasterStats): MasterStats = {
    println(
      "%s: Starting Map/Reduce task %s".format(master.address,
                                               jobInfo.jobName))

    schedule(mapPhase)
    schedule(reducePhase)
    merge(jobInfo)

    println("%s: Map/Reduce task completed\n".format(master.address))

    finish()
  }
}
