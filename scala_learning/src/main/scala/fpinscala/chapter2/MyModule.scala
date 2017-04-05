package fpinscala.chapter2

/**
  * Created by chaomai on 25/03/2017.
  */
object MyModule {
  def abs(n: Int): Int =
    if (n < 0) -n
    else n

  def factorial(n: Int): Int = {
    @annotation.tailrec
    def go(n: Int, acc: Int): Int =
      if (n <= 0) acc
      else go(n - 1, n * acc)

    go(n, 1)
  }

  def fib(n: Int): Int = {
    @annotation.tailrec
    def go(n: Int, a: Int, b: Int): Int = {
      if (n <= 0) a
      else go(n - 1, b, a + b)
    }

    go(n, 0, 1)
  }

  // 无尾递归，n很大时，无法计算
  def fib1(n: Int): Int = {
    def go(n: Int): Int = {
      if (n <= 0) 0
      else if (n == 1) 1
      else go(n - 1) + go(n - 2)
    }

    go(n)
  }

  private def formatResult(name: String, n: Int, f: Int => Int) = {
    val msg = "The %s of %d is %d."
    msg.format(name, n, f(n))
  }

  private def formatAbs(x: Int): String = {
    formatResult("absolute", x, abs)
  }

  private def formatAbs1(x: Int): String = {
    val msg = "The absolute value of %d is %d."
    msg.format(x, abs(x))
  }

  private def formatFactorial(n: Int) = {
    formatResult("factorial", n, factorial)
  }

  private def formatFactorial1(n: Int) = {
    val msg = "The factorial value of %d is %d."
    msg.format(n, factorial(n))
  }

  private def formatFib(n: Int) = {
    formatResult("fib", n, fib)
  }

  def findFirst[A](as: Array[A], p: A => Boolean): Int = {
    @annotation.tailrec
    def loop(n: Int): Int = {
      if (n >= as.length) -1
      else if (p(as(n))) n
      else loop(n + 1)
    }

    loop(0)
  }

  def isSorted[A](as: Array[A], ordered: (A, A) => Boolean): Boolean = {
    @annotation.tailrec
    def loop(n: Int): Boolean = {
      if (n + 1 >= as.length) true
      else if (ordered(as(n), as(n + 1))) loop(n + 1)
      else false
    }

    loop(0)
  }

  def isSorted1[A](as: Array[A], ordered: (A, A) => Boolean): Boolean = {
    @annotation.tailrec
    def loop(n: Int): Boolean = {
      if (n + 1 >= as.length) true
      else if (!ordered(as(n), as(n + 1))) false
      else loop(n + 1)
    }

    loop(0)
  }

  def isSorted2[A](as: Array[A], ordered: (A, A) => Boolean): Boolean = {
    @annotation.tailrec
    def loop(n: Int, prev: A, res: Boolean): Boolean = {
      if (!res) false
      else if (n >= as.length) true
      else {
        var tmpRes = true
        if (ordered(prev, as(n))) tmpRes = true
        else tmpRes = false
        loop(n + 1, as(n), tmpRes)
      }
    }

    loop(1, as(0), true)
  }

  def partial1[A, B, C](a: A, f: (A, B) => C): B => C =
    (b: B) => f(a, b)

  def curry[A, B, C](f: (A, B) => C): A => (B => C) =
  //    f.curried
  //    (a: A) => (b: B) => f(a, b)
    a => b => f(a, b)


  def uncurry[A, B, C](f: A => B => C): (A, B) => C =
  //    (a: A, b: B) => f(a)(b)
    (a, b) => f(a)(b)

  def compose[A, B, C](f: B => C, g: A => B): A => C =
  //    f compose g
  //    (a: A) => f(g(a))
    a => f(g(a))

  def main(args: Array[String]): Unit = {
    println(formatAbs(-42))
    println(formatFactorial(7))
    println(formatFib(20))
    println(findFirst(Array[String]("abc", "bcd"), (str: String) => str == "bcd"))
    println(isSorted(Array(1), (a: Int, b: Int) => a < b))
    println(isSorted(Array(1, 2, 3, 4, 5, 6), (a: Int, b: Int) => a < b))
    println(isSorted(Array(1, 2, 3, 4, 7, 5, 6), (a: Int, b: Int) => a < b))
    println(isSorted(Array(1, 1, 3, 4), (a: Int, b: Int) => a <= b))
  }
}