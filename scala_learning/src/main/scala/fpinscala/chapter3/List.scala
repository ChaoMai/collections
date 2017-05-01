package fpinscala.chapter3

/**
  * Created by chaomai on 26/03/2017.
  */
sealed trait List[+A]

case object Nil extends List[Nothing]

//sealed trait List[A]
//case class Nil[A]() extends List[A]
//case class Cons[A](head: A, tail: List[A]) extends List[A]

case class Cons[+A](head: A, tail: List[A]) extends List[A]

object List {
  def sum(ints: List[Int]): Int = ints match {
    case Nil => 0
    case Cons(x, xs) => x + sum(xs)
  }

  def product(ds: List[Double]): Double = ds match {
    case Nil => 1.0
    case Cons(0.0, _) => 0.0
    case Cons(x, xs) => x * product(xs)
  }

  def apply[A](as: A*): List[A] =
    if (as.isEmpty) Nil
    else Cons(as.head, apply(as.tail: _*))

  def fill[A](n: Int, a: A): List[A] = {
    def loop(n: Int): List[A] =
      if (n <= 0) Nil
      else Cons(a, loop(n - 1))

    loop(n)
  }

  def tail[A](xs: List[A]): List[A] = xs match {
    case Nil => sys.error("tail of empty list")
    case Cons(_, t) => t
  }

  def tail1[A](xs: List[A]): List[A] = xs match {
    case Nil => Nil
    case Cons(_, t) => t
  }

  def setHead[A](l: List[A], h: A): List[A] = l match {
    case Nil => sys.error("setHead on empty list")
    case Cons(_, t) => Cons(h, t)
  }

  def setHead1[A](l: List[A], h: A): List[A] = l match {
    case Nil => Cons(h, Nil)
    case Cons(_, t) => Cons(h, t)
  }

  @annotation.tailrec
  def drop[A](l: List[A], n: Int): List[A] = {
    if (n <= 0) l
    else
      l match {
        case Nil => Nil
        case Cons(_, t) => drop(t, n - 1)
      }
  }

  def dropWhile[A](l: List[A])(f: A => Boolean): List[A] = l match {
    case Cons(h, t) if f(h) => dropWhile(t)(f)
    case _ => l
  }

  def dropWhile1[A](l: List[A], f: A => Boolean): List[A] = l match {
    case Nil => Nil
    case Cons(h, t) =>
      if (f(h)) dropWhile1(t, f) else Cons(h, dropWhile1(t, f))
  }

  def dropWhile2[A](l: List[A], f: A => Boolean): List[A] = l match {
    case Nil => Nil
    case Cons(h, t) if f(h) => dropWhile2(t, f)
    case Cons(h, t) if !f(h) => Cons(h, dropWhile2(t, f))
  }

  def dropWhile3[A](l: List[A], f: A => Boolean): List[A] = l match {
    case Cons(h, t) if f(h) => dropWhile3(t, f)
    case _ => l
  }

  def append[A](a1: List[A], a2: List[A]): List[A] = a1 match {
    case Nil => a2
    case Cons(h, t) => Cons(h, append(t, a2))
  }

  def init[A](l: List[A]): List[A] = l match {
    case Nil => sys.error("init of empty list")
    case Cons(_, Nil) => Nil
    case Cons(h, t) => Cons(h, init(t))
  }

  def init1[A](l: List[A]): List[A] = {
    import collection.mutable.ListBuffer
    val buf = new ListBuffer[A]

    def loop(l: List[A]): List[A] = l match {
      case Nil => sys.error("init of empty list")
      case Cons(_, Nil) => Nil
      case Cons(h, t) => {
        buf.append(h)
        loop(t)
      }
    }

    loop(l)
    List(buf.toList: _*)
  }

  def init2[A](l: List[A]): List[A] = {
    import collection.mutable.ListBuffer
    val buf = new ListBuffer[A]

    @annotation.tailrec
    def loop(l: List[A]): List[A] = l match {
      case Nil => sys.error("init of empty list")
      case Cons(_, Nil) => List(buf.toList: _*)
      case Cons(h, t) => {
        buf.append(h)
        loop(t)
      }
    }

    loop(l)
  }

  def foldRight[A, B](as: List[A], z: B)(f: (A, B) => B): B = as match {
    case Nil => z
    case Cons(x, xs) => f(x, foldRight(xs, z)(f))
  }

  // 直到整个list“展开”，f才开始work，因此是不能够将f apply到当前的z与x的
  // 因此下面的优化是错误的
  //  @annotation.tailrec
  //  def foldRight1[A, B](as: List[A], z: B)(f: (A, B) => B): B = as match {
  //    case Nil => z
  //    case Cons(x, xs) => foldRight1(xs, f(x, z))(f)
  //  }

  def foldRightViaFoldLeft[A, B](as: List[A], z: B)(f: (A, B) => B): B =
    //    foldLeft(reverse(as), z)((b: B, a: A) => f(a, b))
    foldLeft(reverse(as), z)((b, a) => f(a, b))

  def foldRightViaFoldLeft1[A, B](l: List[A], z: B)(f: (A, B) => B): B =
    foldLeft(l, (b: B) => b)((g, a) => b => g(f(a, b)))(z)

  // f的参数顺序其实都ok，只要逐层构造delayer就ok
  def foldRightViaFoldLeft2[A, B](l: List[A], z: B)(f: (B, A) => B): B = {
    type BtoB = B => B

    def delayer: BtoB = (b: B) => b

    def combinerDelayer =
      (a: A, delayerFunc: BtoB) => ((b: B) => delayerFunc(f(b, a)))

    def go: BtoB = foldLeft(l, delayer)((x, y) => combinerDelayer(y, x))

    go(z)
  }

  def sum1(ns: List[Int]) = foldRight(ns, 0)(_ + _)

  def product1(ns: List[Double]) = foldRight(ns, 1.0)(_ * _)

  def length[A](as: List[A]): Int = {
    @annotation.tailrec
    def loop(l: List[A], n: Int): Int = l match {
      case Nil => n
      case Cons(_, xs) => loop(xs, n + 1)
    }

    loop(as, 0)
  }

  def length1[A](as: List[A]): Int = foldRight(as, 0)((_, y) => 1 + y)

  // foldLeft的处理与foldRight相反
  @annotation.tailrec
  def foldLeft[A, B](as: List[A], z: B)(f: (B, A) => B): B = as match {
    case Nil => z
    case Cons(x, xs) => foldLeft(xs, f(z, x))(f)
  }

  def foldLeftViaFoldRight[A, B](l: List[A], z: B)(f: (B, A) => B): B =
    foldRight(l, (b: B) => b)((a, g) => b => g(f(b, a)))(z)

  //  1. foldLeftViaFoldRight1中的go，把foldRight展开后，结果如下
  //  go:
  //
  //  foldRight(List(1,2,3), delayer)(combinerDelayer)(Nil)
  //
  //  combinerDelayer(1, foldRight(List(2,3), delayer)(combinerDelayer))
  //
  //  combinerDelayer(
  //    combinerDelayer(2, foldRight(List(3), delayer)(combinerDelayer)), 1
  //  )
  //
  //  combinerDelayer(1,
  //    combinerDelayer(2,
  //      combinerDelayer(3, foldRight(Nil, delayer)(combinerDelayer))
  //    )
  //  )
  //
  //  combinerDelayer(1,
  //    combinerDelayer(2,
  //      combinerDelayer(3, delayer)
  //    )
  //  )
  //
  //  2. 根据combinerDelayer的定义继续展开
  //
  //  combinerDelayer(1,
  //    combinerDelayer(2,
  //      (b1: B) => delayer(f(b1, 3))
  //    )
  //  )
  //
  //  combinerDelayer(1,
  //    (b2: B) => (
  //      (b1: B) => delayer(f(b1, 3))
  //    )(f(b2, 2))
  //  )
  //
  //  (b3: B) => (
  //    (b2: B) => (
  //      (b1: B) => delayer(f(b1, 3))
  //    )(f(b2, 2))
  //  )(f(b3, 1))
  //
  //  3. 带入Nil
  //
  //  (
  //    (b3: B) => (
  //      (b2: B) => (
  //        (b1: B) => delayer(f(b1, 3))
  //      )(f(b2, 2))
  //    )(f(b3, 1))
  //  )(Nil)
  //
  //  (
  //    (b2: B) => (
  //      (b1: B) => delayer(f(b1, 3))
  //    )(f(b2, 2))
  //  )(Cons(1, Nil))
  //
  //  (
  //    (b1: B) => delayer(f(b1, 3))
  //  )(Cons(2, Cons(1, Nil)))
  //
  //  delayer(Cons(3, Cons(2, Cons(1, Nil))))
  //
  //  4. 最后得到
  //
  //  Cons(3, Cons(2, (Cons(1, Nil))))
  //
  //  这个方式是从展开foldRight的角度来思考的，但是并不直观，需要展开两次，
  //  一是foldRight，二是combinerDelayer。
  //  书上提供的方法直接从delayerFunc入手，更能直观的看出“delay调用”的过程。
  //
  //  这里本以为1中combinerDelayer得到的function能够带入Nil直接计算，但其实不是，
  //  还需要进一步的展开，下面的例子只是为了展示，接受一个参数的function，
  //  在它的外层套了多个function以后，仍然是接受一个参数的function。
  //
  //  可以结合下面的例子来理解，
  //  def f1: (Int => Int) = a => a + 1
  //
  //  def f2: ((Int, Int) => Int) = (a, b) => a * b
  //
  //  在最里层中，f2的第二个参数是一个function，这里没有问题，因为v是一个function
  //  def v: (Int => Int) = p => f2(3, f2(2, f2(1, f1(p))))
  //
  //  v(1)
  //  结合这个例子可以看出，delayer（也就是上面例子的f1）实际上就是一个“子结构”，
  //  每次delayer的构造都是在上一个delayer的基础上构造的

  def foldLeftViaFoldRight1[A, B](l: List[A], z: B)(f: (B, A) => B): B = {
    type BtoB = B => B

    def delayer: BtoB = (b: B) => b

    def combinerDelayer =
      (a: A, delayerFunc: BtoB) => ((b: B) => delayerFunc(f(b, a)))

    def go: BtoB = foldRight(l, delayer)(combinerDelayer)

    go(z)
  }

  // f的参数顺序其实都ok，只要逐层构造delayer就ok
  def foldLeftViaFoldRight2[A, B](l: List[A], z: B)(f: (A, B) => B): B = {
    type BtoB = B => B

    def delayer: BtoB = (b: B) => b

    def combinerDelayer =
      (a: A, delayerFunc: BtoB) => ((b: B) => delayerFunc(f(a, b)))

    def go: BtoB = foldRight(l, delayer)(combinerDelayer)

    go(z)
  }

  //  下面非尾递归的版本的实现并不正确，因为f对参数的apply实际上等到了as完全展开才进行，
  //  不符合foldLeft的本意
  //  def foldLeft1[A, B](as: List[A], z: B)(f: (B, A) => B): B = as match {
  //    case Nil => z
  //    case Cons(x, xs) => f(foldLeft1(xs, z)(f), x)
  //  }

  def sum2(ns: List[Int]) = foldLeft(ns, 0)(_ + _)

  def product2(ns: List[Double]) = foldLeft(ns, 1.0)(_ * _)

  def length2[A](as: List[A]): Int = foldLeft(as, 0)((x, _) => x + 1)

  def reverse[A](l: List[A]): List[A] =
    foldLeft(l, Nil: List[A])((x, y) => Cons(y, x))

  def reverse1[A](l: List[A]): List[A] = {
    @annotation.tailrec
    def loop(l: List[A], m: List[A]): List[A] = l match {
      case Nil => m
      case Cons(x, xs) => {
        loop(xs, Cons(x, m))
      }
    }

    loop(l, Nil)
  }

  def append1[A](a1: List[A], a2: List[A]): List[A] =
    //    foldRight(a1, a2)((a, b) => Cons(a, b))
    foldRight(a1, a2)(Cons(_, _))

  def concat[A](l: List[List[A]]): List[A] = foldRight(l, Nil: List[A])(append)

  def concat1[A](l: List[A]*): List[A] = {
    def loop(x: List[A], as: List[A]*)(
        f: (List[A], List[A]) => List[A]): List[A] = {
      if (as.isEmpty) Nil
      else f(as.head, loop(x, as.tail: _*)(f))
    }

    loop(Nil, l: _*)(append)
  }

  def concat2[A](l: List[A]*): List[A] = {
    // Seq[List[A]] => List[A]
    def loop(x: List[A], as: List[A]*)(
        f: (List[A], List[List[A]]) => List[List[A]]): List[List[A]] = {
      if (as.isEmpty) Nil: List[List[A]]
      else f(as.head, loop(x, as.tail: _*)(f))
    }

    foldRight(loop(Nil, l: _*)(Cons(_, _)), Nil: List[A])(append)
  }

  // concat2是多余。。。Seq[List[A]] => List[A]直接List(l.toList: _*)即可
  def concat3[A](l: List[A]*): List[A] =
    foldRight(List(l.toList: _*), Nil: List[A])(append)

  def add1(l: List[Int]): List[Int] = {
    def loop(l: List[Int])(f: Int => Int): List[Int] = l match {
      case Nil => Nil
      case Cons(x, xs) => Cons(x + 1, loop(xs)(f))
    }

    loop(l)(a => a + 1)
  }

  def add1_1(l: List[Int]): List[Int] =
    foldRight(l, Nil: List[Int])((h, t) => Cons(h + 1, t))

  def ldToString(l: List[Double]): List[String] =
    foldRight(l, Nil: List[String])((h, t) => Cons(h.toString, t))

  def map[A, B](as: List[A])(f: A => B): List[B] =
    foldRight(as, Nil: List[B])((h, t) => Cons(f(h), t))

  def filter[A](as: List[A])(f: A => Boolean): List[A] =
    foldRight(as, Nil: List[A])((h, t) => if (f(h)) Cons(h, t) else t)

  def filter1[A](as: List[A])(f: A => Boolean): List[A] =
    flatMap(as)(x => if (f(x)) List(x) else Nil: List[A])

  def flatMap[A, B](as: List[A])(f: A => List[B]): List[B] =
    foldRight(as, Nil: List[B])((h, t) => concat(List(f(h), t)))

  def flatMap1[A, B](as: List[A])(f: A => List[B]): List[B] =
    concat(map(as)(f))

  def addPairwise(l1: List[Int], l2: List[Int]): List[Int] = (l1, l2) match {
    case (Nil, _) => Nil
    case (_, Nil) => Nil
    case (Cons(x1, xs1), Cons(x2, xs2)) => Cons(x1 + x2, addPairwise(xs1, xs2))
  }

  def addPairwise1(l1: List[Int], l2: List[Int]): List[Int] = (l1, l2) match {
    case (Nil, Nil) => Nil
    case (Cons(_, _), Nil) => Nil
    case (Nil, Cons(_, _)) => Nil
    case (Cons(x1, xs1), Cons(x2, xs2)) => Cons(x1 + x2, addPairwise(xs1, xs2))
  }

  def zipWith[A, B, C](l1: List[A], l2: List[B])(f: (A, B) => C): List[C] =
    (l1, l2) match {
      case (Nil, _) => Nil
      case (_, Nil) => Nil
      case (Cons(x1, xs1), Cons(x2, xs2)) =>
        Cons(f(x1, x2), zipWith(xs1, xs2)(f))
    }

  @annotation.tailrec
  def startsWith[A](l: List[A], prefix: List[A]): Boolean = (l, prefix) match {
    case (_, Nil) => true
    case (Cons(x1, xs1), Cons(x2, xs2)) if x1 == x2 => startsWith(xs1, xs2)
    case _ => false
  }

  @annotation.tailrec
  def hasSubsequence[A](sup: List[A], sub: List[A]): Boolean = sup match {
    case Nil => sub == Nil
    case _ if startsWith(sup, sub) => true
    case Cons(_, t) => hasSubsequence(t, sub)
  }
}
