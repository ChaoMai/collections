package mapreduce

import java.io.File

import akka.actor.{
  Actor,
  ActorPath,
  ActorRef,
  ActorSelection,
  ActorSystem,
  Kill,
  Props
}
import akka.event.Logging
import com.typesafe.config.ConfigFactory
import mapreduce.Common.{mapPhase, reducePhase, MapFunc, Phase, ReduceFunc}
import mapreduce.CommonMap.doMap
import mapreduce.CommonReduce.doReduce

/**
  * Created by chaomai on 05/05/2017.
  */
case class DoMapTaskArgs(jobName: String,
                         mapTaskNumber: Int,
                         inFile: String,
                         nReduce: Int,
                         mapF: MapFunc)

case class DoReduceTaskArgs(jobName: String,
                            reduceTaskNumber: Int,
                            outFile: String,
                            nMap: Int,
                            reduceF: ReduceFunc)

class Worker(masterPath: ActorPath, name: String, nRPC: Int) extends Actor {
  val log = Logging(context.system, this)
  var concurrent = 0
  var nTasks = 0

  val masterActor: ActorSelection = context.actorSelection(masterPath)
  masterActor ! Registration(context.self.path)

  def doTask[T, R](phase: Phase,
                   jobName: String,
                   taskNumber: Int,
                   file: String,
                   nOther: Int,
                   func: T => R): Unit = {
    nTasks += 1

    if (nRPC >= 0 && nTasks >= nRPC) {
      context.self ! Kill
    }

    concurrent += 1

    if (concurrent > 1)
      log.error(
        "Worker.DoTask: more than one DoTask sent concurrently to a single worker")

    phase match {
      case `mapPhase` =>
        doMap(jobName, taskNumber, file, nOther, func.asInstanceOf[MapFunc])
      case `reducePhase` =>
        doReduce(jobName,
                 taskNumber,
                 file,
                 nOther,
                 func.asInstanceOf[ReduceFunc])
    }

    concurrent -= 1

    masterActor ! context.self.path
  }

  override def receive: Receive = {
    case DoMapTaskArgs(jobName, mapTaskNumber, inFile, nReduce, mapF) =>
      doTask(mapPhase, jobName, mapTaskNumber, inFile, nReduce, mapF.tupled)

    case DoReduceTaskArgs(jobName, reduceTaskNumber, outFile, nMap, reduceF) =>
      doTask(reducePhase,
             jobName,
             reduceTaskNumber,
             outFile,
             nMap,
             reduceF.tupled)
  }
}

object Worker {
  def runWorker(masterPath: ActorPath, name: String, nRPC: Int): ActorRef = {
    val confFile = getClass.getClassLoader.getResource(name + ".conf").getFile
    val conf = ConfigFactory.parseFile(new File(confFile))
    val system = ActorSystem("MapReduce", conf)
    system.actorOf(Props(new Worker(masterPath, name, nRPC)), name = "master")
  }
}
