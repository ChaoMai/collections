package fpinscala.util

/**
  * Created by chaomai on 03/04/2017.
  */
object Util {
  private val Seperator = "----------"

  def PrintMessage(): Unit = {
    println(Seperator + Seperator)
  }

  def PrintMessage(msg: String): Unit = {
    println(Seperator + msg + Seperator)
  }
}
