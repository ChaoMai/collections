package fpinscala.chapter5

import fpinscala.util.Util._

/**
  * Created by chaomai on 21/04/2017.
  */
object Chapter5Module {
  def main(args: Array[String]): Unit = {
    val c = Cons(
      () => {
        println("eval 5")
        5
      },
      () =>
        Cons(() => {
               println("eval 4")
               4
             },
             () =>
               Cons(() => {
                      println("eval 3")
                      3
                    },
                    () =>
                      Cons(() => {
                             println("eval 2")
                             2
                           },
                           () =>
                             Cons(() => {
                               println("eval 1")
                               1
                             }, () => Empty))))
    )

    PrintMessage("scanRight")

    val s2 = c.scanRight(0)(_ + _)
    s2.toList

    PrintMessage("scanRight1")

    val s3 = c.scanRight1(0)(_ + _)
    s3.toList
  }
}
