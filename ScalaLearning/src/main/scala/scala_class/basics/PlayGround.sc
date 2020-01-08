// Expressions
1 + 1

// Values
val two = 1 + 1
// two = 1

// Variables
var name = "mike"
name = "chaomai"

// Functions
def addOne(m: Int): Int = m + 1
val three = addOne(two)

def f_three() = 1 + two
f_three()
f_three

def f1_three = 1 + two
// f1_three()
f1_three

// Anonymous Functions
val func_of_anonymous = (x: Int) => x + 1
func_of_anonymous(1)

def timesTwo(i: Int): Int = {
  println("Hello, World")
  i * 2
}

timesTwo(2)

// Partial application
def adder(m: Int, n: Int): Int = m + n
val add2 = adder(2, _: Int)
add2(3)

def multiply(m: Int)(n: Int): Int = m * n
multiply(2)(3)
val timesThree = multiply(3) _
timesThree(4)

// Curried functions
val curriedAdd = (adder _).curried
val addThree = curriedAdd(3)
addThree(4)

def suber(a: Int, b: Int, c: Int, d: Int) = a - b - c - d
val curriedSub = (suber _).curried

// Variable length arguments
def capitalizedAll(args: String*) = {
  args.map(arg => arg.capitalize)
}

capitalizedAll("chao", " ", "mai")

// Classes
class Calculator {
  val brand = "HP"

  def add(m: Int, n: Int): Int = m + n
}

val calc = new Calculator
calc.add(1, 2)
calc.brand

// Constructor
// 构造函数并不是类中特殊的方法，他们是在类的方法定义之外的代码
class Calculator2(brand: String) {
  val color: String = if (brand == "TI") {
    "blue"
  } else if (brand == "HP") {
    "black"
  } else {
    "white"
  }

  def add(m: Int, n: Int): Int = m + n
}

val calc2 = new Calculator2("HP")
calc2.color

// Expressions
// 在Calculator2中，color是被绑定到一个if/else表达式的
// scala中很多东西都是表达式

// Aside: Functions vs Methods
// 函数和方法在大部分情况下都是可交换的
class C {
  var acc = 0

  def minc = {
    acc + 1
  }

  def finc = { () => acc + 1 }
}

val c = new C
c.minc
c.finc
c.finc()

// Inheritance
// Effective Scala指出如果子类与父类实际上没有区别，类型别名是优于继承的
class ScientificCalculator(brand: String) extends Calculator2(brand) {
  def log(m: Double, base: Double): Double = math.log(m) / math.log(base)
}

// Overloading methods
class EvenMoreScientificCalculator(brand: String) extends ScientificCalculator(brand) {
  def log(m: Int): Double = log(m, math.exp(1))
}

// Abstract Classes
abstract class Shape {
  def getArea(): Int
}

class Circle(r: Int) extends Shape {
  override def getArea(): Int = {
    r * r * 3
  }
}

// var s = new Shape
var cir = new Circle(3)
cir.getArea()

// Traits
// traits是字段和行为的集合
// 1. 优先使用traits，class可以extends多个trait，而不能extends多个class
// 2. 当需要构造函数的时候，使用abstract class
trait Car {
  def brand: String
}

trait Shiny {
  val shineRefraction: Int
}

class BMW extends Car {
  val brand = "BMW"
}

class BMW2 extends Car with Shiny {
  val brand = "BMW"
  val shineRefraction = 12
}

// Types
trait Cache[K, V] {
  def get(key: K): V

  def put(key: K, value: V)

  def delete(key: K)
}

//def remove[K](key: K)

// 这是Scala的泛型明显区别于C++的地方
// 在定义的时候就是错误的，因为并不知道类型T是否有+这个操作
// def gen_add[T](m: T, n: T): T = m + n
// gen_add(1, 3)
// gen_add(1.2, 1.4)