// Function Composition
def f(s: String) = "f(" + s + ")"
def g(s: String) = "g(" + s + ")"

// compose
// f(g(x))
val fComposeG = f _ compose g _
// val fComposeG = f _ compose g

fComposeG("yay")

// andThen
// g(f(x))
val fAndThenG = f _ andThen g _
// val fAndThenG = f _ andThen g

fAndThenG("yay")

// Currying vs Partial Application

// case statements
// case语句是function的子类，叫做PartialFunction

// collection of multiple case statements
// 多个PartialFunction compose在一起

// Understanding PartialFunction
// 对给定的输入参数类型，Function可接受该类型的任何值
// 对给定的输入参数类型，PartialFunction只能接受该类型的某些特定的值
// PartialFunction和Partially Applied Function不同
val one: PartialFunction[Int, String] = {
  case 1 => "one"
}

// isDefinedAt可以确定PartialFunction是否能接受一个给定值
one.isDefinedAt(1)
one.isDefinedAt(2)

val two: PartialFunction[Int, String] = {
  case 2 => "two"
}
val three: PartialFunction[Int, String] = {
  case 3 => "three"
}
val wildcard: PartialFunction[Int, String] = {
  case _ => "something else"
}
val partial = one orElse two orElse three orElse wildcard

partial(2)
partial(10)

case class PhoneExt(name: String, ext: Int)

val extensions = List(PhoneExt("steve", 100), PhoneExt("robey", 200))

val predicate: PartialFunction[PhoneExt, Boolean] = {
  case a: PhoneExt => a.ext < 200
}

extensions.filter { case PhoneExt(name, extension) => extension < 200 }
// extensions.filter { case PhoneExt(_, extension) => extension < 200 }
extensions.filter(predicate)
