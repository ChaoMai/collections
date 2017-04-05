// apply
// scala提供的语法糖
class Foo {
}

object FooMaker {
  def apply(): Foo = new Foo
}

val newFoo = FooMaker()

class Bar {
  def apply(): Int = 0
}

val bar = new Bar
bar()

// object
// objects用来存放类的唯一实例
object Timer {
  var count = 0

  def currentCount(): Long = {
    count += 1
    count
  }
}

Timer.currentCount()

// 当class和object有相同的名字的时候，
// 这个object叫做Companion Object。
// Companion Object常用作对象工厂。

class Bar1(foo: String) {}

object Bar1 {
  def apply(foo: String): Bar1 = new Bar1(foo)
}

Bar1("factory")

// Functions are Objects
// Functions是traits的集合
// 接受一个参数的函数是Function1 trait的实例，这个trait定了apply语法糖。
// 这个语法糖帮助统一了对象和函数式编程
// 可以将个class到处传递，并作为函数来使用
// 而函数本质上是类的实例
object addOne extends Function1[Int, Int] {
  override def apply(m: Int): Int = m + 1
}

val plusOne = addOne
addOne(1)

// 和addOne等价
object addOne1 extends (Int => Int) {
  override def apply(m: Int): Int = m + 1
}

val plusOne1 = addOne1
addOne1(2)

// 在类中定义的方法是方法，而不是函数
class AddOne extends Function1[Int, Int] {
  override def apply(m: Int): Int = m + 1
}

val plusOne2 = new AddOne
plusOne2(3)

class AddOne1 {
  def apply(m: Int): Int = m + 1
}

val plusOne3 = new AddOne1
plusOne3(4)

val functionTest: Int => Int = addOne
val functionTest1: Int => Int = addOne1
val functionTest2: Int => Int = plusOne2

// val functionTest3: Int => Int = plusOne3

// Packages
// defined module colorHolder
// Scala的设计者是把对象作为Scala的模块系统的一部分进行设计的
object colorHolder {
  val BLUE = "Blue"
  val RED = "Red"
}

// Pattern Matching

val times = 1

// Matching on values
times match {
  case 1 => "one"
  case 2 => "two"
  case _ => "some other number"
}

// Matching with guards
times match {
  case i if i == 1 => "one"
  case i if i == 2 => "two"
  case _ => "some other number"
}

// Matching on type
def bigger(o: Any): Any = {
  o match {
    case i: Int if i < 0 => i - 1
    case i: Int => i + 1
    case d: Double if d < 0.0 => d - 0.1
    case d: Double => d + 0.1
    case text: String => text + "s"
  }
}

bigger(2)

// Case Classes
case class Calculator(brand: String, model: String)

val hp20b = Calculator("HP", "20b")
val hp20B = Calculator("HP", "20b")
hp20b == hp20B

// Case Classes with pattern matching
// case class时被设计与pattern matching一起使用的
def calcType(calc: Calculator) = calc match {
  case Calculator("HP", "20B") => "financial"
  case Calculator("HP", "48G") => "scientific"
  case Calculator("HP", "30B") => "business"
  //  case Calculator(ourBrand, ourModel) => "Calculator: %s %s is of unknown type".format(ourBrand, ourModel)
  // re-bind the matched value with another name
  case c@Calculator(_, _) => "Calculator: %s of unknown type".format(c)
  // case _ => "Calculator of unknown type"
  // case Calculator(_, _) => "Calculator of unknown type"
}

val hp30b = Calculator("HP", "30B")
calcType(hp20b)
calcType(hp30b)

// Exceptions
// try和if一样，也是面向表达式的
// 但finally不是表达式的一部分
// val result: Int = try {
//   remoteCalculatorService.add(1, 2)
// } catch {
//   case e: ServerIsDownException => {
//     log.error(e, "the remote calculator service is unavailable. should have kept your trusty HP.")
//     0
//   }
// } finally {
//   remoteCalculatorService.close()
// }