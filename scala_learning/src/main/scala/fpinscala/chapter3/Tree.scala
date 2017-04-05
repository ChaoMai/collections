package fpinscala.chapter3

/**
  * Created by chaomai on 31/03/2017.
  */
sealed trait Tree[+A]

case class Leaf[A](value: A) extends Tree[A]

case class Internals[A](left: Tree[A], right: Tree[A]) extends Tree[A]

object Tree {

  def leaf[A](a: A): Tree[A] = Leaf(a)

  def internals[A](l: Tree[A], r: Tree[A]): Tree[A] = Internals(l, r)

  def size[A](t: Tree[A]): Int = t match {
    case Leaf(_) => 1
    case Internals(a, b) => size(a) + size(b) + 1
  }

  // 下面的实现是错误的，第二个case中，当前Internals被计数了两次
  //  def size1[A](t: Tree[A]): Int = {
  //    def loop(t: Tree[A], c: Int): Int = t match {
  //      case Leaf(_) => c
  //      case Internals(a, b) => loop(a, c + 1) + loop(b, c + 1)
  //    }
  //
  //    loop(t, 0)
  //  }

  def size2[A](t: Tree[A]): Int =
    //    fold(t)(_ => 1)((m, n) => m + n + 1)
    fold(t)(_ => 1)(1 + _ + _)

  def maximum(t: Tree[Int]): Int = t match {
    case Leaf(l) => l
    case Internals(a, b) => maximum(a) max maximum(b)
  }

  def maximum2(t: Tree[Int]): Int =
    //    fold(t)(x => x)((m, n) => m max n)
    fold(t)(a => a)(_ max _)

  def depth[A](t: Tree[A]): Int = t match {
    case Leaf(_) => 0
    case Internals(a, b) => 1 + (depth(a) max depth(b))
    //    case Internals(a, b) => (depth(a) + 1) max (depth(b) + 1)
  }

  def depth2[A](t: Tree[A]): Int = fold(t)(_ => 0)((m, n) => 1 + (m max n))

  def map[A, B](t: Tree[A])(f: A => B): Tree[B] = t match {
    case Leaf(l) => Leaf(f(l))
    case Internals(a, b) => Internals(map(a)(f), map(b)(f))
  }

  // Rank-1 polymorphism
  // fold(t)(x => Leaf(f(x)))会把返回值先推断为Leaf[B]，
  // 而下一个函数Internals(_, _)返回的是Internals[B]，因此类型不匹配。
  // 需要显式的指明x => Leaf(f(x)): Tree[B]，或者定义helper function。
  def map2[A, B](t: Tree[A])(f: A => B): Tree[B] =
    fold(t)(x => Leaf(f(x)): Tree[B])(Internals(_, _))

  def map3[A, B](t: Tree[A])(f: A => B): Tree[B] =
    fold(t)(x => leaf(f(x)))(internals)

  def fold[A, B](t: Tree[A])(l: A => B)(b: (B, B) => B): B = t match {
    case Leaf(n) => l(n)
    case Internals(x, y) => b(fold(x)(l)(b), fold(y)(l)(b))
  }
}
