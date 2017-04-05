package scala_tutorial

/**
  * Created by chaomai on 08/03/2017.
  */

trait C {
  def value: Int

  def double_value: Int = C.get_double(value)
}

object C {
  def get_double(v: Int): Int = v * 2
}

class ContrateC(v: Int) extends C {
  def value: Int = v
}

object Companion {
  def main(args: Array[String]): Unit = {
    val c = new ContrateC(1)
    println(c.value)
    println(c.double_value)
  }
}