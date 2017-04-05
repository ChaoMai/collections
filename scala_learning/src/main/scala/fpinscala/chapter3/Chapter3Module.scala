package fpinscala.chapter3

/**
  * Created by chaomai on 27/03/2017.
  */
object Chapter3Module {
  def main(args: Array[String]): Unit = {
    val ex1: List[Double] = Nil
    val ex2: List[Int] = Cons(1, Nil)
    val ex3: List[String] = Cons("a", Cons("b", Nil))

    println(List.product(ex1))
    println(List.sum(ex2))
    println(List(1, 2, 3, "a"))
    println(List.fill(5, "a"))

    val l1 = List(1, 2, 3, 4, 5)

    l1 match {
      case _ => 42
    }

    l1 match {
      case Cons(h, _) => h
      case _ => Nil
    }

    l1 match {
      case Cons(_, t) => t
      case _ => Nil
    }

    l1 match {
      case Cons(x, Cons(2, Cons(4, _))) => x
      case Nil => 42
      case Cons(x, Cons(y, Cons(3, Cons(4, _)))) => x + y
      case Cons(h, t) => h + List.sum(t)
      case _ => Nil
    }

    println(List.fill(5, "a"))

    println(List.tail(l1))
    // error: println(List.tail(Nil))
    println(List.tail(List(1)))

    // error: println(List.setHead(List(), 10))
    // error: println(List.setHead(Nil, 10))
    println(List.setHead(l1, 10))

    println(List.drop(l1, 3))
    println(List.drop(l1, 5))
    println(List.drop(l1, 30))
    println(List.drop(Nil, 3))

    println(List.dropWhile(l1)((_: Int) => true))
    println(List.dropWhile(l1)((x: Int) => x % 2 == 0))
    println(List.dropWhile1(l1, (x: Int) => x % 2 == 0))
    println(List.dropWhile2(l1, (x: Int) => x % 2 == 0))

    println(List.append(l1, List(6, 7, 8)))

    println(List.init(l1))
    println(List.init(List(1)))
    // error: println(List.init(Nil))
    println(List.init1(l1))
    println(List.init1(List(1)))
    println(List.init2(l1))
    println(List.init2(List(1)))

    println(List.product1(ex1))
    println(List.sum1(ex2))

    println(List.foldRight(l1, Nil: List[Int])(Cons(_, _)))

    println(List.length(l1))
    println(List.length1(l1))

    println(List.product2(List(1.0, 2.0, 3.0)))
    println(List.sum2(l1))
    println(List.length2(l1))

    println(List.reverse(l1))
    println(List.reverse1(l1))

    println(List.ldToString(List(1.2, 2.3, 3.4)))

    println(List.foldLeft(l1, Nil: List[Int])((x, y) => Cons(y, x)))
    println(
      List.foldLeftViaFoldRight(l1, Nil: List[Int])((x, y) => Cons(y, x)))
    println(
      List.foldLeftViaFoldRight1(l1, Nil: List[Int])((x, y) => Cons(y, x)))
    println(
      List.foldLeftViaFoldRight2(l1, Nil: List[Int])((x, y) => Cons(x, y)))

    type A = Int
    type B = List[Int]

    type BtoB = B => B

    def f = (b: B, a: A) => Cons(a, b)

    def delayer: BtoB = (b: B) => b

    def combinerDelayer =
      (a: A, delayerFunc: BtoB) => ((b: B) => delayerFunc(f(b, a)))

    println(
      combinerDelayer(1, combinerDelayer(2, combinerDelayer(3, delayer)))(Nil)
    )

    println(
      combinerDelayer(1, combinerDelayer(2, (b1: B) => delayer(f(b1, 3))))(Nil)
    )

    println(
      combinerDelayer(1, (b2: B) => ((b1: B) => delayer(f(b1, 3)))(f(b2, 2)))(
        Nil)
    )

    println(
      (
          (b3: B) =>
            (
                (b2: B) => ((b1: B) => delayer(f(b1, 3)))(f(b2, 2))
            )(f(b3, 1))
      )(Nil)
    )

    println(
      (
          (b1: B) => delayer(f(b1, 3))
      )(Cons(2, Cons(1, Nil)))
    )

    println(List.foldRight(l1, Nil: List[Int])(Cons(_, _)))
    println(List.foldRightViaFoldLeft(l1, Nil: List[Int])(Cons(_, _)))
    println(List.foldRightViaFoldLeft1(l1, Nil: List[Int])(Cons(_, _)))
    println(
      List.foldRightViaFoldLeft2(l1, Nil: List[Int])((x, y) => Cons(y, x)))

    println(List.append1(l1, List(6, 7, 8)))
    println(List.append1(l1, Nil))
    println(List.concat(List(l1, List(6, 7, 8), List(1, 2, 3, 4, 5))))
    println(List.concat1(l1, List(6, 7, 8), List(1, 2, 3, 4, 5)))
    println(List.concat2(l1, List(6, 7, 8), List(1, 2, 3, 4, 5)))
    println(List.concat3(l1, List(6, 7, 8), List(1, 2, 3, 4, 5)))

    println(List.add1(l1))
    println(List.add1_1(l1))

    println(List.filter(l1)(x => x % 2 != 0))
    println(List.filter1(l1)(x => x % 2 != 0))

    println(List.flatMap(List(1, 2, 3))(i => List(i, i)))
    println(List.flatMap1(List(1, 2, 3))(i => List(i, i)))

    println(List.addPairwise(l1, l1))
    println(List.addPairwise(l1, Nil))
    println(List.addPairwise(Nil, l1))
    println(List.addPairwise(l1, List(1, 2, 3)))
    println(List.addPairwise(List(1, 2, 3), l1))

    println(List.zipWith(l1, List(1, 2, 3))(_.toString + _.toString))

    println(List.hasSubsequence(l1, List(2, 3)))

    val t1: Tree[Int] = Internals(
      Internals(Leaf(1), Leaf(2)),
      Internals(Leaf(3), Internals(Leaf(4), Leaf(5))))

    val t2: Tree[Int] = Internals(Leaf(1), Leaf(2))

    println(Tree.size(t1))
    //    println(Tree.size1(t1))
    println(Tree.size(t2))

    println(Tree.maximum(t1))

    println(Tree.depth(t1))

    println(Tree.map(t1)(x => x * x))

    println(Tree.size2(t1))
    println(Tree.maximum2(t1))
    println(Tree.depth2(t1))
    println(Tree.map2(t1)(x => x * x))
    println(Tree.map3(t1)(x => x * x * x))
  }
}
