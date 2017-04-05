package fpinscala.chapter4

/**
  * Created by chaomai on 31/03/2017.
  */
object Chapter4Module {
  def main(args: Array[String]): Unit = {
    println(mean(Seq()))

    val l1 = List(Some(1), Some(2), Some(3))
    val l2 = List(Some(1), None, Some(3))

    println(l1)
    println(sequence(l1))
    println(sequence(l2))
    println(sequence1(l1))
    println(sequence2(l1))
    println(sequence2(l2))

    val l3 = List("1", "2", "3", "4", "5")
    val l4 = List("a", "b", "c")

    println(traverse(l3)(i => Try(i.toInt)))
    println(traverse(l4)(i => Try(i.toInt)))
    println(traverse1(l3)(i => Try(i.toInt)))
    println(traverse1(l4)(i => Try(i.toInt)))

    val l5 = List(Right(1), Right(2), Right(3))
    val l6 =
      List(Right(1), Left("error1"), Left("error2"), Left("error3"), Right(3))

    println(sequence3(l5))
    println(sequence3(l6))

    println(sequence4(l5))
    println(sequence4(l6))

    println(sequence5(l5))
    println(sequence5(l6))

    println(Person.mkPerson("chaomai", 20))
    println(Person.mkPerson("chaomai", -1))
    println(Person.mkPerson("", 20))
    println(Person.mkPerson("", -1))

    println(Person.mkPerson1("chaomai", 20))
    println(Person.mkPerson1("chaomai", -1))
    println(Person.mkPerson1("", 20))
    println(Person.mkPerson1("", -1))

    println(Person.mkPerson2("chaomai", 20))
    println(Person.mkPerson2("chaomai", -1))
    println(Person.mkPerson2("", 20))
    println(Person.mkPerson2("", -1))

    // the perfect one
    println(Person.mkPerson3("chaomai", 20))
    println(Person.mkPerson3("chaomai", -1))
    println(Person.mkPerson3("", 20))
    println(Person.mkPerson3("", -1))
  }

  def mean(xs: Seq[Double]): Option[Double] =
    if (xs.isEmpty) None
    else Some(xs.sum / xs.length)

  //  从输入值的角度来考虑：有了xs的mean，那么需要一个function来用这个mean
  //  而这个function里肯定也是有mean的，即返回Option
  def variance(xs: Seq[Double]): Option[Double] = {
    mean(xs) flatMap (m => mean(xs map (x => math.pow(x - m, 2.0))))
  }

  def Try[A](a: => A): Option[A] =
    try Some(a)
    catch { case e: Exception => None }

  def map2[A, B, C](a: Option[A], b: Option[B])(f: (A, B) => C): Option[C] = {
    a flatMap (aa => (b map (bb => f(aa, bb))))
    //      b.flatMap(bb => a map (aa => f(aa, bb)))
  }

  def map2_1[A, B, C](a: Option[A], b: Option[B])(f: (A, B) => C): Option[C] =
    (a, b) match {
      case (None, _) => None
      case (_, None) => None
      case (Some(x), Some(y)) => Some(f(x, y))
    }

  // 在每层使用flatMap提取出Option的值，最后由map里面的f调用来构造Option结果
  def map3[A, B, C, D](a: Option[A], b: Option[B], c: Option[C])(
      f: (A, B, C) => D): Option[D] = {
    a flatMap (aa => (b flatMap (bb => (c map (cc => f(aa, bb, cc))))))
  }

  def sequence[A](a: List[Option[A]]): Option[List[A]] = a match {
    case Nil => Some(Nil)
    //      case h :: t => h flatMap (hh => sequence(t) map (hh :: _))
    //      case x :: xs => sequence(xs) flatMap (e => (x map (xx => xx :: e)))
    case x :: xs => map2(x, sequence(xs))(_ :: _)
  }

  //  因为foldRight的第一个参数为Some(Nil)的关系，此时返回值会被推导为Some(Nil.type)，
  //  但所需的返回值实际的类型是Option[List[A]]，因此会报错，需要显示指明。
  def sequence1[A](a: List[Option[A]]): Option[List[A]] =
    //      a.foldRight[Option[List[A]]](Some(Nil))((x, t) => map2(x, t)(_ :: _))
    a.foldRight[Option[List[A]]](Some(Nil))((x, t) =>
      x flatMap (xx => (t map (tt => xx :: tt))))

  def traverse[A, B](a: List[A])(f: A => Option[B]): Option[List[B]] =
    //      a.foldRight[Option[List[B]]](Some(Nil))((x, xs) =>
    //        (f(x) flatMap (xx => (xs map (xsxs => xx :: xsxs)))))
    a.foldRight[Option[List[B]]](Some(Nil))((x, xs) => map2(f(x), xs)(_ :: _))

  def traverse1[A, B](a: List[A])(f: A => Option[B]): Option[List[B]] =
    a match {
      case Nil => Some(Nil)
      case x :: xs => map2(f(x), traverse1(xs)(f))(_ :: _)
    }

  def sequence2[A](a: List[Option[A]]): Option[List[A]] = traverse(a)(x => x)

  def Try1[A](a: => A): Either[Exception, A] =
    try Right(a)
    catch { case e: Exception => Left(e) }

  def sequence3[E, A](es: List[Either[E, A]]): Either[E, List[A]] = es match {
    case Nil => Right(Nil)
    //    case x :: xs => x flatMap (xx => (sequence3(xs) map (xsxs => xx :: xsxs)))
    case x :: xs => sequence3(xs) flatMap (t => (x map (xx => xx :: t)))
    //    case x :: xs => x map2 (sequence3(xs))((a, b)=> a :: b)
  }

  def sequence4[E, A](es: List[Either[E, A]]): Either[E, List[A]] =
    es.foldRight[Either[E, List[A]]](Right(Nil))((x, xs) =>
      (xs flatMap (xsxs => (x map (xx => xx :: xsxs)))))

  def sequence5[E, A](es: List[Either[E, A]]): Either[E, List[A]] =
    traverse3(es)(x => x)

  //  应该先对h apply f，这样才能在第一个Left时返回
  def traverse2[E, A, B](as: List[A])(
      f: A => Either[E, B]): Either[E, List[B]] = as match {
    case Nil => Right(Nil)
    case h :: t => (f(h) map2 traverse2(t)(f))(_ :: _)
  }

  //  问题同traverse2
  def traverse3[E, A, B](as: List[A])(
      f: A => Either[E, B]): Either[E, List[B]] =
    //    as.foldRight[Either[E, List[B]]](Right(Nil))((x, xs) =>
    //      (xs flatMap (xsxs => f(x) map (xx => xx :: xsxs))))
    as.foldRight[Either[E, List[B]]](Right(Nil))(
      (a, b) => f(a).map2(b)(_ :: _))
}
