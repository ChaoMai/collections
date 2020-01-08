package akka

import akka.actor.{Actor, ActorSystem, Props}

/**
  * Created by chaomai on 23/04/2017.
  */
class FisrtS extends Actor {
  override def receive: Receive = {
    case "hello" => println("Hello World!")
    case msg: String => println("Got " + msg)
    case _ => println("Unknown message")
  }
}

object HelloWorld {
  def main(args: Array[String]): Unit = {
    val system = ActorSystem("FirstExample")

    val first = system.actorOf(Props[FisrtS], name = "first")

    println("The path associated with first is " + first.path)

    first ! "hello"
    first ! "Goodbye"
    first ! 4

    system.terminate
  }
}
