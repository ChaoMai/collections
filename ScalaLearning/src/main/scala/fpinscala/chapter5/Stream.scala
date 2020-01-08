package fpinscala.chapter5

/**
  * Created by chaomai on 03/04/2017.
  */
sealed trait Stream[+A] {
  def headOption: Option[A] = this match {
    case Empty => None
    case Cons(h, _) => Some(h())
  }

  // 不需要过多考虑，观察对比headOption和foldRight发现
  // 发现case Empty => None和case Empty => z
  def headOption1: Option[A] = foldRight(None: Option[A])((h, _) => Some(h))

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
  // 这里的h()实际上不是对h进行求值
  def take(n: Int): Stream[A] = this match {
    case Cons(h, t) if n > 1 => Stream.cons(h(), t().take(n - 1))
    case Cons(h, _) if n == 1 => Stream.cons(h(), Stream.empty)
    case _ => Stream.empty
  }

  def take1(n: Int): Stream[A] = this match {
    case Empty => Empty
    case Cons(h, t) if n > 0 => Cons(h, () => t().take1(n - 1))
    case Cons(_, _) if n <= 0 => Empty
  }

  def takeViaUnfold(n: Int): Stream[A] = Stream.unfold((n, this)) {
    case (_, Empty) => None
    case (i, Cons(h, t)) if i > 0 => Some(h(), (i - 1, t()))
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

  def takeWhile(p: A => Boolean): Stream[A] = this match {
    case Cons(h, t) if p(h()) => Stream.cons(h(), t() takeWhile p)
    case _ => Stream.empty
  }

  // 只有在p为true的时候才放入结果，p的结果一旦为false就停止
  def takeWhile1(p: A => Boolean): Stream[A] = this match {
    case Cons(h, t) if p(h()) => Cons(h, () => t().takeWhile(p))
    case _ => Empty
  }

  // 这个实现不对，当p为false时，最后一个case对剩下的stream进行takeWhile
  // 但此时应该停止运行了
  def takeWhile2(p: A => Boolean): Stream[A] = this match {
    case Empty => Empty
    case Cons(h, t) if p(h()) => Cons(h, () => t().takeWhile(p))
    case Cons(_, t) => t().takeWhile3(p)
  }

  def takeWhile3(p: A => Boolean): Stream[A] =
    foldRight(Stream.empty[A])((h, t) =>
      if (p(h)) Stream.cons(h, t) else Stream.empty)

  // 如果unfold还在运行，那么当前head（即）会被至少求值一次
  def takeWhileViaUnfold(p: A => Boolean): Stream[A] = Stream.unfold(this) {
    case Cons(h, t) if p(h()) => Some(h(), t())
    case _ => None
  }

  // 下面foldRight的f，相当于这里的||
  def exist(p: A => Boolean): Boolean =
    foldRight(false)((a, acc) => p(a) || acc)

  def exist1(p: A => Boolean): Boolean =
    foldRight(false)((a, acc) => acc || p(a))

  def exist2(p: A => Boolean): Boolean = this match {
    case Cons(h, t) => p(h()) || t().exist2(p)
    case _ => false
  }

  // 注意f的第一个参数不是call by name，这里会引发一次求值
  def foldRight[B](z: => B)(f: (A, => B) => B): B = this match {
    case Empty => z
    case Cons(h, t) => f(h(), t().foldRight(z)(f))
  }

  def forAll(p: A => Boolean): Boolean =
    foldRight(true)((a, acc) => p(a) && acc)

  def forAll1(p: A => Boolean): Boolean =
    foldRight(true)((a, acc) => acc && p(a))

  def map[B](f: A => B): Stream[B] =
    foldRight(Stream.empty[B])((h, t) => Stream.cons(f(h), t))

  def mapViaUnfold[B](f: A => B): Stream[B] = Stream.unfold(this) {
    case Empty => None
    case Cons(a, b) => Some(f(a()), b())
  }

  def filter(p: A => Boolean): Stream[A] =
    foldRight(Stream.empty[A])((h, t) => if (p(h)) Stream.cons(h, t) else t)

  def append[B >: A](a2: => Stream[B]): Stream[B] =
    foldRight(a2)((h, t) => Stream.cons(h, t))

  def append1[B >: A](a2: => Stream[B]): Stream[B] = this match {
    case Empty => a2
    case Cons(h, t) => Stream.cons(h(), t() append1 a2)
  }

  def flatMap[B](f: A => Stream[B]): Stream[B] =
    foldRight(Stream.empty[B])((h, t) => f(h) append t)

  def zipWith[B, C](s2: Stream[B])(f: (A, B) => C): Stream[C] =
    Stream.unfold((this, s2)) {
      case (Cons(h1, t1), Cons(h2, t2)) => Some(f(h1(), h2()), (t1(), t2()))
      case _ => None
    }

  def zip[B](s2: Stream[B]): Stream[(A, B)] = zipWith(s2)((_, _))

  def zipAll[B](s2: Stream[B]): Stream[(Option[A], Option[B])] =
    Stream.unfold((this, s2)) {
      case (Cons(h1, t1), Empty) => Some((Some(h1()), None), (t1(), Empty))
      case (Empty, Cons(h2, t2)) => Some((None, Some(h2())), (Empty, t2()))
      case (Cons(h1, t1), Cons(h2, t2)) =>
        Some((Some(h1()), Some(h2())), (t1(), t2()))
      case _ => None
    }

  def zipAll1[B](s2: Stream[B]): Stream[(Option[A], Option[B])] =
    zipWithAll(s2)((_, _))

  // grammar sugar: def ->[B](y: B): (A, B)
  def zipWithAll[B, C](s2: Stream[B])(
      f: (Option[A], Option[B]) => C): Stream[C] = Stream.unfold((this, s2)) {
    case (Cons(h1, t1), Empty) =>
      Some(f(Some(h1()), None), (t1(), Stream.empty[B]))
    case (Empty, Cons(h2, t2)) =>
      Some(f(None, Some(h2())), (Stream.empty[A], t2()))
    case (Cons(h1, t1), Cons(h2, t2)) =>
      Some(f(Some(h1()), Some(h2())) -> (t1() -> t2()))
    case _ => None
  }

  def startsWith[B >: A](s: Stream[B]): Boolean =
    zipAll(s).takeWhile(_._2.isDefined) forAll {
      case (h, h2) => h == h2
    }

  def startsWith1[B >: A](s: Stream[B]): Boolean =
    zipAll(s)
      .takeWhile(_._2.isDefined)
      .forAll(e => e._1 == e._2)

  // 下面的case不通过，没有考虑第一个stream短的情况
  // error: Stream(1, 2) startsWith Stream(1, 2, 3)
  def startsWith2[B >: A](s: Stream[B]): Boolean =
    zip(s).forAll(e => e._1 == e._2)

  def tails: Stream[Stream[A]] =
    Stream
      .unfold(this) {
        case Empty => None
        case s => Some((s, s drop 1))
      } append Stream(Stream.empty)

  def tails1: Stream[Stream[A]] =
    Stream
      .unfold(this) {
        case Cons(h, t) => Some(Stream.cons(h(), t()), t())
        case Empty => None
      }
      .append(Stream(Stream.empty))

  def hasSubsequence[B >: A](s: Stream[B]): Boolean =
    tails exist (_ startsWith s)

  def scanRight[B](z: B)(f: (A, => B) => B): Stream[B] =
    foldRight((z, Stream(z)))((e, acc_s) => {
      lazy val p1 = acc_s
      val acc_e = f(e, p1._1)
      (acc_e, Stream.cons(acc_e, p1._2))
    })._2

  //  val s = Stream(3, 2, 1)
  //
  //  s.scanRight(0)(_ + _)
  //
  //  <=>
  //
  //  把求和的function叫sum
  //  s.scanRight(0)(sum)
  //
  //  <=>
  //
  //  展开scanRight
  //  s.foldRight((0, Stream(0)))((e, acc_s) => {
  //    val acc_e = sum(e, acc_s._1)
  //    (acc_e, Stream.cons(acc_e, acc_s._2))
  //  })._2
  //
  //  对应以下foldRight的f
  //  f: (Int, (Int, Stream[Int])) => (Int, Stream[Int]) = (e, acc_s) => {
  //    val acc_e = sum(e, acc_s._1)
  //    (acc_e, Stream.cons(acc_e, acc_s._2))
  //  }
  //
  //  进行pattern matching
  //  Cons(3, Stream(2, 1)): f(3, Stream(2, 1).foldRight((0, Stream(0)))(f))
  //
  //  {
  //    val acc_e = sum(3, Stream(2, 1).foldRight((0, Stream(0)))(f)._1)
  //    (acc_e, Stream.cons(acc_e, acc_s._2))
  //  }
  //
  //  {
  //    val acc_e = sum(3,
  //                      {
  //                        val acc_e = sum(2,
  //                                          {
  //                                            val acc_e = sum(1, Empty.foldRight((0, Stream(0)))(f)._1)
  //
  //                                            (acc_e, Stream.cons(acc_e, acc_s._2))
  //                                          }._1
  //                                        )
  //
  //                        (acc_e, Stream.cons(acc_e, acc_s._2))
  //                      }._1
  //                    )
  //    (acc_e, Stream.cons(acc_e, acc_s._2))
  //  }
  //
  //  实际上这里已经得到了计算后续元素所需的中间结果acc_s
  //
  //  {
  //    val acc_e = sum(3,
  //                      {
  //                        val acc_e = sum(2,
  //                                          {
  //                                            val acc_e = sum(1, 0)
  //
  //                                            (acc_e, Stream.cons(acc_e, acc_s._2))
  //                                          }._1
  //                                        )
  //
  //                        (acc_e, Stream.cons(acc_e, acc_s._2))
  //                      }._1
  //                    )
  //    (acc_e, Stream.cons(acc_e, acc_s._2))
  //  }
  //
  //  遍历整个stream，对acc_s._1求值得到6以后，还需要计算acc_s._2，
  //  但Stream.cons的第二个参数是call by name的，因此暂时不会引发求值。
  //
  //  {
  //    val acc_e = 6
  //    (15, Stream.cons(6, acc_s._2))
  //  }
  //
  //  这就是表达式s.scanRight(0)(_ + _)的计算过程。
  //  到目前为止计算了结果的第一个元素。
  //  当需要后续元素时，同样以上述的方式进行计算。
  //  可以发现，计算前面元素的时候，实际上已经得到了计算后续元素所需的中间结果acc_s，
  //  因此scanRight中用lazy缓存了acc_s，后面的计算使用的都是第一次lazy的acc_s。
  //  计算是不需要了，但是还是需要访问acc_s中的各个子stream。
  //  本质上来看，与动态规划的填表有异曲同工之妙，第一次lazy的acc_s相当于dp里的table。

  def scanRight1[B](z: B)(f: (A, => B) => B): Stream[B] =
    foldRight((z, Stream(z)))((e, acc_s) => {
      val acc_e = f(e, acc_s._1)
      (acc_e, Stream.cons(acc_e, acc_s._2))
    })._2

  def scanRight2[B](z: B)(f: (A, => B) => B): Stream[B] =
    Stream
      .unfold(this) {
        case Empty => None
        case s => Some((s, s drop 1))
      }
      .append(Stream(Stream.empty))
      .map(s => s.foldRight(z)(f))
}

case object Empty extends Stream[Nothing]

// why not h: => A ?  Due to technical limitations...╮(╯_╰)╭
// case class parameters may not be call-by-name
// error:
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

  // 当一直遍历的时候，消耗的内存不变
  // 这个实现是依赖于保持共享的，但保持共享是容易出错的
  def ones: Stream[Int] = cons(1, ones)

  val ones1: Stream[Int] = constantViaUnfold(1)

  // 当一直遍历的时候，消耗的内存会逐渐增加
  val onesViaUnfold: Stream[Int] = unfold(1)(_ => Some(1, 1))

  def constant[A](a: A): Stream[A] = {
    lazy val tail: Stream[A] = Cons(() => a, () => tail)
    tail
  }

  def constant1[A](a: A): Stream[A] = {
    lazy val const: Stream[A] = cons(a, const)
    const
  }

  def constant2[A](a: A): Stream[A] = {
    def const: Stream[A] = cons(a, const)
    const
  }

  // error: forward reference extends over definition of value
  // forward reference必须reference到member
  // 如果要在一个block里进行forward reference，被reference对象必须是lazy val的，或是def（method）
  //  def constant3[A](a: A): Stream[A] = {
  //    val const: Stream[A] = Stream.cons(a, const)
  //    const
  //  }

  def constantViaUnfold[A](a: A): Stream[A] = unfold(a)(_ => Some(a, a))

  def from(n: Int): Stream[Int] = cons(n, from(n + 1))

  def fromViaUnfold(n: Int): Stream[Int] = unfold(n)(p => Some(p, p + 1))

  def fibs: Stream[Int] = {
    def loop(p: (Int, Int)): Stream[Int] = {
      cons(p._1, loop((p._1 + p._2, p._1)))
    }

    loop(0, 1)
  }

  val fibs1: Stream[Int] = {
    def go(f0: Int, f1: Int): Stream[Int] = {
      cons(f0, go(f0 + f1, f0))
    }

    go(0, 1)
  }

  val fibsViaUnfold: Stream[Int] =
    unfold((0, 1))(p => Some(p._1, (p._1 + p._2, p._1)))

  // 第二个参数写法等价于，p => p match { case (f0,f1) => ... }
  val fibsViaUnfold1: Stream[Int] = unfold((0, 1)) {
    case (f0, f1) => Some(f1, (f0 + f1, f0))
  }

  def unfold[A, S](z: S)(f: S => Option[(A, S)]): Stream[A] = {
    def loop(s: S): Stream[A] = f(s) match {
      case None => empty
      case Some(p) => cons(p._1, loop(p._2))
    }

    loop(z)
  }

  def unfold1[A, S](z: S)(f: S => Option[(A, S)]): Stream[A] = {
    def loop(e: S): Stream[A] = f(e) match {
      case None => empty
      case Some((h, s)) => cons(h, loop(s))
    }

    loop(z)
  }
}
