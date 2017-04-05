package scala_tutorial

/**
  * Created by chaomai on 05/03/2017.
  */
object Timer {
  def oncePerSecond(callback: () => Unit): Unit = {
    while (true) {
      callback()
      Thread sleep 1000
    }
  }

  def timeFlies(): Unit = {
    println("time flies like an arrow ...")
  }

  def main(args: Array[String]): Unit = {
    // oncePerSecond(timeFlies)
    oncePerSecond(() => println("time flies like an arrow ..."))
  }
}