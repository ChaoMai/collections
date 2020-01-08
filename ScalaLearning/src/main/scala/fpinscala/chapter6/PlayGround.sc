import fpinscala.chapter6.RNG._
import fpinscala.chapter6.{RNGViaState, State}
import fpinscala.chapter6.RNGViaState.RandViaState

val rng = SimpleRNG(42)
val (n1, rng2) = rng.nextInt
val (n2, rng3) = rng2.nextInt

val (nni1, rng4) = nonNegativeInt(rng)
val (nni2, rng5) = nonNegativeInt(rng4)

val (d1, rng6) = double(rng)
val (d2, rng7) = double(rng6)

val (di1, rng8) = doubleInt(rng)
val (di2, rng9) = doubleInt(rng8)

val (id1, rng10) = intDouble(rng)
val (id2, rng11) = intDouble(rng10)

val (ds, _) = double3(rng)

val (l, _) = ints(5)(rng)
val (l1, _) = ints1(5)(rng)

randIntDouble(rng)

sequence(List(unit(1), unit(2), unit(3)))(rng)._1
intsViaSequence(5)(rng)

nonNegativeLessThan(12)(rng)

rollDie(rng)

val srng = RNGViaState.SimpleRNG(42)

RNGViaState.int.run(srng)

RNGViaState.ints(5).run(srng)

val ns: RandViaState[List[Int]] =
  RNGViaState.int.flatMap(x =>
    RNGViaState.int.flatMap(y =>
      RNGViaState.ints(x).map(xs => xs.map(_ % y))))

val ns1: RandViaState[List[Int]] = for {
  x <- RNGViaState.int
  y <- RNGViaState.int
  xs <- RNGViaState.ints(x)
} yield xs.map(_ % y)
