package fpinscala.chapter7

import java.util.concurrent.Executors
import fpinscala.chapter7.Par._

/**
  * Created by chaomai on 01/05/2017.
  */
object Chapter7Module {
  def main(args: Array[String]): Unit = {
    val es = Executors.newCachedThreadPool()

    println(run(es)(sum(0 until 100)).get)
  }

  def sum(ints: IndexedSeq[Int]): Par[Int] =
    if (ints.length <= 1) Par.unit(ints.headOption getOrElse 0)
    else {
      val (l, r) = ints.splitAt(ints.length / 2)
      Par.map2(Par.fork(sum(l)), Par.fork(sum(r)))(_ + _)
    }
}
