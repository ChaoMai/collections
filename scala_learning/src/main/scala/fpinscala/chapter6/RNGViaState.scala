package fpinscala.chapter6

/**
  * Created by chaomai on 30/04/2017.
  */
trait RNGViaState {
  def nextInt: (Int, RNGViaState)
}

object RNGViaState {
  case class SimpleRNG(seed: Long) extends RNGViaState {
    override def nextInt: (Int, RNGViaState) = {
      val newSeed = (seed * 0x5DEECE66DL + 0xBL) & 0xFFFFFFFFFFFFL
      val nextRNG = SimpleRNG(newSeed)
      val n = (newSeed >>> 16).toInt
      (n, nextRNG)
    }
  }

  type RandViaState[+A] = State[RNGViaState, A]

  val int: RandViaState[Int] = State(s => s.nextInt)

  def unit[A](a: A): RandViaState[A] = State(rng => (a, rng))

  def ints(count: Int): RandViaState[List[Int]] =
    sequence(List.fill(count)(int))

  def sequence[A](fs: List[RandViaState[A]]): RandViaState[List[A]] =
    fs.foldRight(unit(List[A]()))((f, acc) => f.map2(acc)(_ :: _))
}
