package fpinscala.chapter5

/**
  * Created by chaomai on 03/04/2017.
  */
sealed trait Stream[+A] {
  def headOption: Option[A] = this match {
    case Empty => None
    case Cons(h, _) => Some(h())
  }

  def toList: List[A] = {
    @annotation.tailrec
    def loop(s: Stream[A], acc: List[A]): List[A] = s match {
      case Empty => acc
      case Cons(h, t) => loop(t(), h() :: acc)

      //      case Cons(h, t) => loop(t(), h() :: acc)
      //      case _ => acc
    }

    loop(this, Nil).reverse
  }

  def toList1: List[A] = this match {
    case Empty => Nil
    case Cons(h, t) => h() :: t().toList1

    //    case Cons(h,t) => h() :: t().toList1
    //    case _ => List()
  }

  // take和take1等价，take1写法更好看，两者都不会引发多余的求值
  def take(n: Int): Stream[A] = this match {
    case Empty => Empty
    case Cons(h, t) if n > 0 => Cons(h, () => t().take(n - 1))
    case Cons(_, _) if n <= 0 => Empty
  }

  // why h() in Stream.cons(h(), t().take1(n - 1))
  def take1(n: Int): Stream[A] = this match {
    case Cons(h, t) if n > 1 => Stream.cons(h(), t().take1(n - 1))
    case Cons(h, _) if n == 1 => Stream.cons(h(), Stream.empty)
    case _ => Stream.empty
  }

  def drop(n: Int): Stream[A] = this match {
    case Cons(_, t) if n > 0 => t().drop(n - 1)
    case _ => this
  }

  def drop1(n: Int): Stream[A] = this match {
    case Empty => Empty
    case Cons(_, t) if n > 0 => t().drop(n - 1)
    case Cons(h, t) if n <= 0 => Cons(h, t)
  }

  // same as take1, why h()?
  def takeWhile(p: A => Boolean): Stream[A] = this match {
    case Cons(h, t) if p(h()) => Stream.cons(h(), t() takeWhile p)
    case _ => Stream.empty
  }

  def takeWhile1(p: A => Boolean): Stream[A] = this match {
    case Empty => Empty
    case Cons(h, t) if p(h()) => Cons(h, () => t().takeWhile(p))
    case Cons(_, t) => t().takeWhile(p)
  }
}

case object Empty extends Stream[Nothing]

// why not h: => A ?  Due to technical limitations...╮(╯_╰)╭
// case class parameters may not be call-by-name
// case class Cons[+A](h: => A, t: => Stream[A]) extends Stream[A]
case class Cons[+A](h: () => A, t: () => Stream[A]) extends Stream[A]

object Stream {
  // 为了避免直接使用Cons时，会导致对同一表达式多次求值，这里定义一个smart constructor
  // 相当于用一个anonymous function对lazy val进行了wrap
  def cons[A](hd: => A, tl: => Stream[A]): Stream[A] = {
    lazy val head = hd
    lazy val tail = tl
    Cons(() => head, () => tail)
  }

  def empty[A]: Stream[A] = Empty

  def apply[A](as: A*): Stream[A] =
    if (as.isEmpty) empty else cons(as.head, apply(as.tail: _*))
}
