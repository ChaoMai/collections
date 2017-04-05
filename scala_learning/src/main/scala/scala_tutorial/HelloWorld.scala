package scala_tutorial

import java.text.DateFormat._
import java.util.{Locale}

/**
  * Created by chaomai on 05/03/2017.
  */

// singleton object
object HelloWorld {
  def main(args: Array[String]): Unit = {
    println("Hello, world!")
    val now = new java.util.Date
    val df = getDateInstance(LONG, Locale.FRENCH)
    println(df format now)
    println(df.format(now))

    // 必须有括号，不然会被解释为1.，这样就变成了integer加上一个double
    println((1).+(2))
  }
}