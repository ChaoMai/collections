package akka

import akka.actor.{Actor, ActorSystem, Props}

/**
  * Created by chaomai on 23/04/2017.
  */
case class Start(secondPath: String)
case object PING
case object PONG

class PingPong extends Actor {
  override def receive: Receive = {
    case PING =>
      println("PING  |")
      Thread.sleep(500)
      sender ! PONG

    case PONG =>
      println("      |  PONG")
      Thread.sleep(500)
      sender ! PING

    case Start(secondPath) =>
      val second = context.actorSelection(secondPath)
      second ! PING
  }
}

object Server {
  def main(args: Array[String]): Unit = {
    val system = ActorSystem("PingPong")
    val first = system.actorOf(Props[PingPong], name = "first")
    val second = system.actorOf(Props[PingPong], name = "second")

    println(first.path)
    println(second.path)
    first ! Start(second.path.toString)

    println("Server ready")
  }
}
