package mapreduce

import java.io.File

import akka.actor.{Actor, ActorPath, ActorRef, ActorSystem, PoisonPill, Props}
import akka.event.Logging
import akka.pattern.ask
import akka.util.Timeout
import com.typesafe.config.ConfigFactory

import scala.collection.mutable.Queue
import scala.concurrent.Await
import scala.concurrent.Future
import scala.concurrent.duration._
import mapreduce.Common.{
  mapPhase,
  mergeName,
  reducePhase,
  MapFunc,
  Phase,
  ReduceFunc
}

/**
  * Created by chaomai on 07/05/2017.
  */
case class Registration(worker: ActorPath)
case class ShutdownReply(nTasks: Int)
case class RunArgs(jobName: String,
                   files: List[String],
                   nReduce: Int,
                   mapF: MapFunc,
                   reduceF: ReduceFunc)
case class DoMapTask(mapF: MapFunc)
case class DoReduceTask(reduce: ReduceFunc)
case object PullIdleWorker

class MasterOfDistributed(address: String) extends Master(address) {
  var idleWorkers: Queue[ActorPath] = Queue()

  override def receive: Receive = {
    case args @ RunArgs(_, _, _, _, _) => {
      val runner: ActorRef = context.actorOf(Props[Runner], name = "Runner")

      implicit val timeout = Timeout(5 seconds)
      val future: Future[JobStats] =
        (runner ? args).asInstanceOf[Future[JobStats]]
      val info = MasterInfo(address, context.self)

      (info, future)
    }

    case Registration(worker) =>
      log.info("------------------Registration")
      idleWorkers.enqueue(worker)

    case PullIdleWorker => sender ! idleWorkers.dequeue()
  }
}

object MasterOfDistributed {
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
    val master = system.actorOf(Props(new MasterOfDistributed(masterAddress)),
                                name = "master")

    implicit val timeout = Timeout(5 seconds)

//    val future = master ? RunArgs(jobName, files, nReduce, mapF, reduceF)
//    val ret =
//      Await.result(future, Duration.Inf).asInstanceOf[(MasterInfo, JobStats)]
//    master ! PoisonPill
//
//    ret

    master ! RunArgs(jobName, files, nReduce, mapF, reduceF)
    ???
  }
}

class Runner extends Actor {
  val log = Logging(context.system, this)

  override def receive: Receive = {
    // map phase
    case RunArgs(jobName, files, nReduce, mapF, reduceF) => {
      val jobInfo = JobInfo(jobName, files, nReduce)

      val mapScheduler =
        context.actorOf(
          Props(new Scheduler(jobName, files, nReduce, mapPhase)),
          name = "mapScheduler")

      mapScheduler ! DoMapTask(mapF)
      mapScheduler ! PoisonPill

      val reduceScheduler = context.actorOf(
        Props(new Scheduler(jobName, files, nReduce, reducePhase)),
        name = "reduceScheduler")

      reduceScheduler ! DoReduceTask(reduceF)
      reduceScheduler ! PoisonPill
    }
  }
}

class Scheduler(jobName: String,
                files: List[String],
                nReduce: Int,
                phase: Phase)
    extends Actor {
  val log = Logging(context.system, this)

  val (n_tasks, n_other) = phase match {
    case `mapPhase` => (files.length, nReduce)
    case `reducePhase` => (nReduce, files.length)
  }

  override def receive: Receive = {
    case DoMapTask(mapF) =>
      (0 until n_tasks).foreach { i =>
        implicit val timeout = Timeout(5 seconds)
        val future = context.parent ? PullIdleWorker
        val worker = Await.result(future, Duration.Inf).asInstanceOf[ActorPath]

        context.actorSelection(worker) ! DoMapTaskArgs(jobName,
                                                       i,
                                                       files(i),
                                                       n_other,
                                                       mapF)
      }

    case DoReduceTask(reduceF) =>
      (0 until n_tasks).foreach { i =>
        implicit val timeout = Timeout(5 seconds)
        val future = context.parent ? PullIdleWorker
        val worker = Await.result(future, Duration.Inf).asInstanceOf[ActorPath]

        context.actorSelection(worker) ! DoReduceTaskArgs(jobName,
                                                          i,
                                                          mergeName(jobName,
                                                                    i),
                                                          n_other,
                                                          reduceF)
      }
  }
}
