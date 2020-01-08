import fpinscala.chapter5._
import fpinscala.util.Util.PrintMessage

// by value，调用apply时就计算了参数
val sf = Stream(
  {
    println("eval 1")
    1
  }, {
    println("eval 2")
    2
  }, {
    println("eval 3")
    3
  }, {
    println("eval 4")
    4
  }, {
    println("eval 5")
    5
  }, {
    println("eval 6")
    6
  }, {
    println("eval 7")
    7
  }
)

PrintMessage("headOption")

sf.headOption
sf.headOption

PrintMessage("Stream.cons")

val a = Stream.cons({
  println("eval 2")
  2
}, Stream.cons({
  println("eval 1")
  1
}, Empty))

// by name，首次使用第一个元素是第一个println(a.headOption)，此时完成计算并cache，
// 第二次reference不再计算，其实reference到的实际上是那个lazy val。
println(a.headOption)
println(a.headOption)

PrintMessage("Cons")

val b = Cons(() => {
  println("eval 2")
  2
}, () => Cons(() => {
  println("eval 1")
  1
}, () => Empty))

// 没有cache，每次reference都会重新计算
println(b.headOption)
println(b.headOption)

PrintMessage("toList")

println(sf.toList)

PrintMessage("take")

println(sf.take(3).toList)
println(sf.take(10).toList)

// val c = Stream.cons({
//   println("eval 2");
//   2
// }, Stream.cons({
//   println("eval 1");
//   1
// }, Empty))

val c = Cons(() => {
  println("eval 5")
  5
}, () => Cons(() => {
  println("eval 4")
  4
}, () => Cons(() => {
  println("eval 3")
  3
}, () => Cons(() => {
  println("eval 2")
  2
}, () => Cons(() => {
  println("eval 1")
  1
}, () => Empty)))))

println(c.take(2))
println(c.take(2).toList)
println(c.take(2).toList)

// val d = Cons(() => {
//   println("eval 3")
//   3
// }, () => Cons(() => {
//   println("eval 2")
//   2
// }, () => Cons(() => {
//   println("eval 1")
//   1
// }, () => Empty)))

val d = Stream.cons({
  println("eval 2")
  2
}, Stream.cons({
  println("eval 1")
  1
}, Empty))

println(d.take1(2))
println(d.take1(2).toList)
println(d.take1(2).toList)

PrintMessage("drop")

println(sf.drop(3).toList)
println(sf.drop(10).toList)

PrintMessage("takeWhile")

println(sf.takeWhile(x => x % 2 == 0).toList)
println(sf.takeWhile1(x => x % 2 == 0).toList)
println(sf.takeWhile2(x => x % 2 == 0).toList)
println(sf.takeWhile3(x => x % 2 == 0).toList)

PrintMessage("exists")

c.exist(i => i == 3)
c.exist1(i => i == 3)
c.exist2(i => i == 3)

PrintMessage("forAll")

c.forAll(i => i >= 3)
c.forAll(i => i >= 4)

c.forAll1(i => i >= 3)
c.forAll1(i => i >= 4)

PrintMessage("map")

c.map(i => i * 2)
c.map(i => i * 2).toList

PrintMessage("filter")

c.filter(i => i % 2 != 0)
c.filter(i => i % 2 != 0).toList

PrintMessage("append")

b.append(c)
c.append(b)
b.append(c).toList

b.append1(c)
c.append1(b)
b.append1(c).toList

PrintMessage("flatMap")

c.flatMap(i => Stream(i, i))
c.flatMap(i => Stream(i, i)).toList

PrintMessage("ones")

Stream.ones.take(5)
Stream.ones.take(5).toList
Stream.ones.take(5).toList

Stream.ones.forAll(_ != 1)

// won't stop
// ones.forAll(_ == 1)

PrintMessage("constant")

Stream.constant({
  println("five")
  5
}).take(5).toList
Stream.constant(List(1)).take(5).toList

Stream.constant1({
  println("five")
  5
}).take(5).toList
Stream.constant1(List(1)).take(5).toList

PrintMessage("from")

Stream.from(10).take(10).toList

PrintMessage("fib")

Stream.fibs.take(10).toList

PrintMessage("unfold")

Stream.unfold((0, 1))(p => Some(p._1, (p._1 + p._2, p._1))).take(10).toList

Stream.onesViaUnfold.take(5).toList
Stream.constantViaUnfold(List(1, 2, 3)).take(5).toList
Stream.fibsViaUnfold.take(10).toList
Stream.fromViaUnfold(10).take(10).toList

c.mapViaUnfold(i => i * 2).toList
c.takeViaUnfold(5).toList
c.takeViaUnfold(15).toList
c.takeWhileViaUnfold(_ % 2 != 0).toList
c.zipWith(b)(_ * _).toList
c.zip(b).toList
c.zipAll(b).toList
c.zipAll1(b).toList

PrintMessage("startsWith")

c startsWith b
Stream(1, 2, 3) startsWith Stream(1, 2)
Stream(1, 2) startsWith Stream(1, 2, 3)

PrintMessage("tails")

c.tails.map(_.toList)
c.tails1.map(_.toList).toList

PrintMessage("hasSubsequence")

c.hasSubsequence(b)

PrintMessage("scanRight")

sf.take(5).scanRight(0)(_ + _).toList
sf.take(5).scanRight1(0)(_ + _).toList

c.scanRight(0)(_ + _).toList
c.scanRight1(0)(_ + _).toList

val sum: (Int, Int) => Int = _ + _

val f: (Int, => (Int, Stream[Int])) => (Int, Stream[Int]) = (e, acc_s) => {
  val acc_e = sum(e, acc_s._1)
  (acc_e, Stream.cons(acc_e, acc_s._2))
}

val acc_s = f(5, c.drop(1).foldRight((0, Stream(0)))(f))
acc_s._1
acc_s._2.take(3).toList

lazy val c1 = sf.map(x => {
  println(x)
  x * 2
})

c1.toList
c1.drop(2).toList
