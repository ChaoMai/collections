package scala_tutorial

/**
  * Created by chaomai on 05/03/2017.
  */
// 对于没有指定父类的类，那么父类就是scala.AnyRef

class Complex(real: Double, imaginary: Double) {
  // re_f和re都是method，调用的时候，
  // val c = new Complex(1.2, 3.4)
  // c.re_f和c.re_f()都是可行的，c.re可行，但是c.re()是错误的

  def re_f() = real

  def im_f() = imaginary

  def re = real

  def im = imaginary

  //  override def toString: String = "" + re + (if (im < 0) "" else "+") + im + "i"
  override def toString() = "" + re + (if (im < 0) "" else "+") + im + "i"
}

object ComplexNumbers {
  def main(args: Array[String]): Unit = {
    val c = new Complex(1.2, 3.4)
    println(c)
    println(c.toString)
    println("real part: " + c.re_f)
    println("imaginary part: " + c.im)
  }
}