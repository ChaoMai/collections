# Currying

一个Curryied函数是，把一个接受多个参数的函数重写为，一个首先接受第一个参数并返回一个函数接受第二个参数...的函数。

例如：foldLeft。

https://oldfashionedsoftware.com/2009/07/10/scala-code-review-foldleft-and-foldright/

# Currying和Partially Applied Function

* http://stackoverflow.com/questions/14309501/scala-currying-vs-partially-applied-functions
* http://stackoverflow.com/questions/8650549/using-partial-functions-in-scala-how-does-it-work/8650639#8650639


# trait and class

* http://stackoverflow.com/questions/1991042/what-is-the-advantage-of-using-abstract-classes-instead-of-traits
* http://stackoverflow.com/questions/2005681/difference-between-abstract-class-and-trait
* http://www.artima.com/pins1ed/traits.html#12.7


# Functions and Methods

In Scala there is a rather arbitrary distinction between functions defined as _methods_, which are introduced with the `def` keyword, and function values, which are the first-class objects we can pass to other functions, put in collections, and so on.

* https://www.google.com/search?q=difference+scala+function+method
* http://www.cnblogs.com/shihuc/p/5082701.html
* http://stackoverflow.com/questions/4839537/functions-vs-methods-in-scala
* http://stackoverflow.com/questions/2529184/difference-between-method-and-function-in-scala
* http://jim-mcbeath.blogspot.com/2009/05/scala-functions-vs-methods.html
* https://dzone.com/articles/revealing-scala-magician%E2%80%99s
* https://tpolecat.github.io/2014/06/09/methods-functions.html
* https://www.quora.com/What-is-the-difference-between-function-and-method-in-Scala
* https://softwarecorner.wordpress.com/2013/09/06/scala-methods-and-functions/
* http://www.marcinkossakowski.com/difference-between-functions-and-methods-in-scala/
* http://japgolly.blogspot.com/2013/10/scala-methods-vs-functions.html
* http://blog.vmoroz.com/posts/2016-06-01-scala-should-i-use-a-method-or-a-function.html


# Functional Combinators

* [Explanation of combinators](http://stackoverflow.com/questions/7533837/explanation-of-combinators-for-the-working-man)

`List(1, 2, 3) map squared`把函数`squared`应用到了`List(1, 2, 3)`的每个元素上，并返回一个新的List。这个操作叫做map组合子（map combinators）。


# PartialFunction and Partially Applied Function


# Rank-1 polymorphism and Higher-Rank Polymorphism

* https://apocalisp.wordpress.com/2010/07/02/higher-rank-polymorphism-in-scala/
    * related:
    * https://apocalisp.wordpress.com/2010/10/26/type-level-programming-in-scala-part-7-natural-transformation%C2%A0literals/
    * https://apocalisp.wordpress.com/2011/03/20/towards-an-effect-system-in-scala-part-1/
* http://existentialtype.net/2008/03/09/higher-rank-impredicative-polymorphism-in-scala/


# Existential Types

* http://www.drmaciver.com/2008/03/existential-types-in-scala/

# Algebraic Data Type

* http://tpolecat.github.io/presentations/algebraic_types.html
* https://www.youtube.com/watch?v=YScIPA8RbVE

# Variant

## Covariant and contravariant

对于所有类型`X`和`Y`，以及类型`Co[+A]`，`Ctr[-A]`，`Iv[A]`。如果X是Y的子类，

covariant：`Co[X]`是`Co[Y]`的子类。在类型参数A前加上+表示covariant。
contravariant：`Ctr[Y]`是`Ctr[X]`的子类。在类型参数A前加上-表示contravariant。
invariant：`Iv[X]`和`Iv[Y]`无关。

```
┌───┐     ┌───────┐     ┌───────┐
│ Y │     │ Co[Y] │     │Ctr[X] │
└───┘     └───────┘     └───────┘
  ▲           ▲             ▲
  │           │             │
  │           │             │
┌───┐     ┌───────┐     ┌───────┐
│ X │     │ Co[X] │     │Ctr[Y] │
└───┘     └───────┘     └───────┘
```

表述covariant的另一种方式是，在所有上下文中，都可安全的把`A`转换为`A`父类。contravariant类似。

```scala
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
val variant_b2: variant1[Bird] = new variant1[Chicken]
                │            │       │               │
                └────────────┘       └───────────────┘
                      ▲                       │
                      └───────────────────────┘
                           to supper class

class contravariant2[-A]

val contravariant_b3: contravariant2[Bird] = new contravariant2[Animal]
// error:
// val contravariant_b4: contravariant2[Bird] = new contravariant2[Chicken]
```

## Covariant and Contravariant Positions

```scala
trait Function1 [-T1, +R] extends AnyRef
```

以函数为例，

contravariant (positive) position：一个类型在函数结果的类型中。更一般的来说，是函数产生的值的类型。
covariant (negative) position：一个类型在函数参数的类型中。更一般的来说，是函数所使用的值的类型。

```
                   ┌────────────────────────┐
                   │ contravariant position │
                   └────────────────────────┘
                                ▲
             ┌──────────────────┘
             │
  def foo(a: A): B
                 │
                 └────────────┐
                              ▼
                   ┌────────────────────┐
                   │ covariant position │
                   └────────────────────┘
```

对于高阶函数，从外层向内分析。类型最终是什么position由分析过程中，各个类型的“累加”得到。就函数`foo`而言，`A => B`是在contravariant position；就函数`f`而言，`A`是在contravariant position，`B`是在covariant position。因此，最终`A`是在covariant position（可以理解为两个negative position合并，负负得正），而`B`是在contravariant position。

```
                    ┌───────────────────────┐
                    │ A: covariant position │
                    └───────────────────────┘
                                ▲
                                │                    ┌───────────────────────────┐
                                                     │ B: contravariant position │
                ┌ ─ ─ ─ ─ ─ ─ ─ ┴ ─ ─ ─ ─ ─ ─ ─ ─    └───────────────────────────┘
                                                 │                 ▲
                ├──────────────────────────────────────────────────┴──────────┐
                │                                │                            │
                │                   ┌────────────────────────┐                │
   ┌────────────────────────┐       │ contravariant position │     ┌────────────────────┐
   │ contravariant position │       └────────────────────────┘     │ covariant position │
   └────────────────────────┘                    ▲                 └────────────────────┘
                ▲                    ┌───────────┘                            ▲
                │                    │    ┌───────────────────────────────────┘
                │                    │    │
             ┌────┐       ┌───────▶  A => B
             │    │───────┘
  def foo(f: A => B): C
                      │
                      └────────────┐
                                   ▼
                        ┌────────────────────┐
                        │ covariant position │
                        └────────────────────┘
```

Scala要求类型本身的variant与类型所在位置的variant一致。

```scala
// error 1
trait Option[+A] {
  def orElse(o: Option[A]): Option[A]
  ...
}

// error 2
class V1[+A]
class V2[-B] extends V1[B]
```

这个定义将会导致编译错误，`Error:... covariant type A occurs in contravariant position in type`。`orElse`函数接受参数`Option[A]`，这个位置（contravariant position）是只能将`A`转换为`A`的子类型的地方。但是类型`A`是covariant的，也就是说在所有上下文中，都可安全的把`A`转换为`A`父类。这里出现了冲突。

对于`orElse`，解决方式是不使用`A`，使用边界限定类型为`A`的父类。

```scala
def orElse[B >: A](o: Option[B]): Option[B] = this match {
    case None => ob
    case _ => this
}
```

那为什么不，

```scala
// 1.
def orElse[B <: A](o: Option[B]): Option[B]

// 2.
def orElse[B](o: Option[B]): Option[B]
```

`orElse`返回值可能的类型为`Option[B]`或`Option[A]`，

* 对于1，`B`是`A`的子类，`Option[B]`是`Option[A]`的子类，当返回`this`时，类型为`Option[A]`，这里无法从父类转换到子类。
* 对于2，当返回`this`时，类型为`Option[A]`，和`Option[B]`完全无关，类型不匹配。

