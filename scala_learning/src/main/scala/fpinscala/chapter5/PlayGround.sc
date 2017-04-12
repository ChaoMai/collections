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

println(sf.headOption)
println(sf.headOption)

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
},
  () => Cons(() => {
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

//val c = Stream.cons({
//  println("eval 2");
//  2
//}, Stream.cons({
//  println("eval 1");
//  1
//}, Empty))

val c = Cons(() => {
  println("eval 3")
  3
}, () => Cons(() => {
  println("eval 2")
  2
}, () => Cons(() => {
  println("eval 1")
  1
}, () => Empty)))

println(c.take(2))
println(c.take(2).toList)
println(c.take(2).toList)

val d = Cons(() => {
  println("eval 3")
  3
}, () => Cons(() => {
  println("eval 2")
  2
}, () => Cons(() => {
  println("eval 1")
  1
}, () => Empty)))

//val d = Stream.cons({
//  println("eval 2");
//  2
//}, Stream.cons({
//  println("eval 1");
//  1
//}, Empty))

println(d.take1(2))
println(d.take1(2).toList)
println(d.take1(2).toList)

PrintMessage("drop")

println(sf.drop(3).toList)
println(sf.drop(10).toList)

PrintMessage("takeWhile")

println(sf.takeWhile(x => x % 2 == 0).toList)
