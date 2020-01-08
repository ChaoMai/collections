// # static types
// 类型系统是一个语法方法，
// 它们根据程序计算的值的种类对程序短语进行分类，
// 通过分类结果错误行为进行自动检查。
//
// 类型允许你表示函数的定义域和值域。
//
// 一般说来，类型检查只能保证 不合理 的程序不能编译通过。
// 它不能保证每一个合理的程序都 可以 编译通过。
//
// 需要注意的是，所有的类型信息会在编译时被删去，
// 因为它已不再需要。这就是所谓的擦除。

// # Types in Scala
// 特性：
// 参数多态性（Parametric polymorphism），
// （局部）类型推导（(local) type inference），
// 存在量化（existential quantification），
// 视图（views）

// # Parametric polymorphism
val mems = 2 :: 1 :: "bar" :: "foo" :: Nil
mems.head

// 多态性是由type variables来实现的
def drop1[A](l: List[A]) = l.tail
drop1(mems)
drop1(List(1, 2, 3))

// ## Scala has rank-1 polymorphism
// 下面两个例子错误的原因在于，
// 函数f要一个A类型的参数，
// 但是传递进去的是B和Int
// 对于第二个例子必须提供一个Int->A的隐式转换
// error:
// def foo[A, B](f: A => List[A], b: B) = f(b)
// error:
// def foo[A, B](f: A => List[A], b: Int) = f(b)

def toList[A](a: A) = List(a)

// rank-1 polymorphism如下例
def foo[A](f: A => List[A], i: A) = f(i)
// 这里使用的时候，必须指定Int，否则toList是Nothing=>List[Nothing]，
// 因此也说明了B必须是Int
// error: foo(toList, 1)
foo(toList[Int], 1)

// ## Higher-Rank polymorphism
def bar[A](f: A => List[A], e1: A, e2: String): (List[A], List[String]) = (f(e1), List[String](e2))
bar(toList[Int], 1, "str")

// apply f to e2 won't work,
// because String is not A
// error:
// def bar[A](f: A => List[A], e1: A, e2: String): (List[A], List[String]) = (f(e1), f(e2))

// generic version of bar won't work,
// because B is not A
// error:
// def bar[A, B](f: A => List[A], e1: A, e2: B): (List[A], List[B]) =
//  (f(e1), f(e2))

// # Type inference
// 对于静态类型，一个反对的声音是会带来很多的语法开销，
// scala的解决方案是type inference
// scala通过，推断约束并尝试统一类型，来实现type inference
// { x => x}

def id[T](x: T) = x
val x1 = id(322)
val x2 = id("hey")
val x3 = id(Array(1, 2, 3, 4))

// # Variance
// scala需要结合多态性来解释类层次，
// 类层次可以表达子类之间的关系。
// 在混合OO和多态性时，一个核心问题是：
// 如果T'是T一个子类，
// Container[T']应该被看做是Container[T]的子类吗？
// variance可以用来表达这些关系。
// covariant | C[T'] is a subclass of C[T] | [+T]
// contravariant | C[T] is a subclass of C[T'] | [-T]
// invariant | C[T] and C[T’] are not related | [T]
class Covariant[+A]

val cv: Covariant[AnyRef] = new Covariant[String]

// error:
// val cv1: Covariant[String] = new Covariant[AnyRef]

class Contravariant[-A]

val cv2: Contravariant[String] = new Contravariant[AnyRef]

// error:
// val cv3: Contravariant[AnyRef] = new Contravariant[String]

// ## variance的例子1：
// trait Function1 [-T1, +R] extends AnyRef
def f1(m: AnyVal): List[Int] = List[Int](1)
val func1: AnyVal => AnyRef = f1

def f2(m: Any): List[Int] = List[Int](1)
val func2: AnyVal => AnyRef = f2

def f3(m: Float): List[Int] = List[Int](1)
// error:
// val func3: AnyVal => AnyRef = f3

def f4(m: Any): Any = List[Int](1)

// error:
// val func4: AnyVal => AnyRef = f4

// ## variance的例子2：
class Animal {
  val sound = "rustle"
}

class Bird extends Animal {
  override val sound = "call"
}

class Chicken extends Bird {
  override val sound = "cluck"
}

class covariant1[+A]

// error:
// val covariant_b1: covariant1[Bird] = new covariant1[Animal]
val covariant_b2: covariant1[Bird] = new covariant1[Chicken]

class contravariant2[-A]

val contravariant_b3: contravariant2[Bird] = new contravariant2[Animal]
// error:
// val contravariant_b4: contravariant2[Bird] = new contravariant2[Chicken]

// In most situations,
// if you say “I need a _, I have a subclass of _”,
// you’re OK.
def getTweet(b: Bird): String = b.sound
getTweet(new Chicken)

// Function parameters are contravariant.
// If you need a function that takes a Bird
// and you have a function that takes a Chicken,
// that function would choke on a Duck
// error:
// val getTweet1: (Bird => String) = (b: Chicken) => b.sound
val getTweet2: (Bird => String) = (b: Animal) => b.sound
getTweet2(new Chicken)

// A function’s return value type is covariant.
// If you need a function that returns a Bird
// but have a function that returns a Chicken, that’s great.
val hatch: (() => Bird) = (() => new Chicken)

// # Bounds
// bounds可以用来限制多态变量
// error:
// def cacophony[T](things: Seq[T]) = things map (_.sound)
// ## upper bound
// T是Animal的子类
def biophony[T <: Animal](things: Seq[T]) = things map (_.sound)

biophony(Seq(new Chicken, new Bird))

// ## lower bound
val flock = List(new Bird, new Bird)
// def ::[B >: A](x: B): List[B]
// B是A的超类
new Chicken :: flock
new Animal :: flock

// # Quantification
// superfluous type parameter
def count[A](l: List[A]) = l.size

// 可以使用“通配符”
def count1(l: List[_]) = l.size

// count1定义等价于
def count2(l: List[T forSome {type T}]) = l.size

//// “通配符”，基本，等价于T forSome {type T}
//// 例外，
//def drop(l: List[_]) = l.tail
//
//// drop[](val l: List[_]) => List[Any]
//// 此时，返回值的元素类型丢失了
//drop(List[Int](1, 2, 3))
//
//// drop2[T](val l: List[T]) => List[T]
//def drop2[T](l: List[T]) = l.tail
//drop2(List[Int](1, 2, 3))
//
//// drop3[](val l: List[T forSome { type T }])
//// => List[T forSome { type T }]
//def drop3(l: List[T forSome {type T}]) = l.tail
//drop3(List[Int](1, 2, 3))
