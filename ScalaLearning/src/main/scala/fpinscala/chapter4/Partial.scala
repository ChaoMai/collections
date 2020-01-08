package fpinscala.chapter4

/**
  * Created by chaomai on 01/04/2017.
  */
sealed trait Partial[+A, +B] {
  def map[C](f: B => C): Partial[A, C] = this match {
    case Errors(a) => Errors(a)
    case Success(b) => Success(f(b))
  }

  def flatMap[AA >: A, C](f: B => Partial[AA, C]): Partial[AA, C] =
    this match {
      case Errors(a) => Errors(a)
      case Success(b) => f(b)
    }

  def map2[AA >: A, C, D](b: Partial[AA, C])(f: (B, C) => D): Partial[AA, D] =
    // 下面的实现不对，无法使用flatMap来累加error
    //    this flatMap (aa => (b map (bb => f(aa, bb))))
    (this, b) match {
      case (Errors(a), Errors(b)) => Errors(a ++ b)
      case (Errors(a), _) => Errors(a)
      case (_, Errors(b)) => Errors(b)
      case (Success(a), Success(b)) => Success(f(a, b))
    }

}

case class Errors[+A](get: Seq[A]) extends Partial[A, Nothing]

case class Success[+B](get: B) extends Partial[Nothing, B]
