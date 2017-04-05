package fpinscala.chapter4

/**
  * Created by chaomai on 31/03/2017.
  */
sealed trait Option[+A] {
  def map[B](f: A => B): Option[B] = this match {
    case None => None
    case Some(a) => Some(f(a))
  }

  //  依次有下面几种情况：
  //  1. this对象为None
  //  2. f调用失败
  //  3. f调用成功
  def flatMap[B](f: A => Option[B]): Option[B] = this match {
    case None => None
    case Some(a) => f(a)
  }

  def flatMap1[B](f: A => Option[B]): Option[B] = this map (f) getOrElse None

  def getOrElse[B >: A](default: => B): B = this match {
    case None => default
    case Some(a) => a
  }

  def orElse[B >: A](ob: => Option[B]): Option[B] = this match {
    case None => ob
    case _ => this
  }

  //  不能直接this getOrElse ob，返回值不对，需要map先封装一次
  def orElse1[B >: A](ob: => Option[B]): Option[B] =
    this map (Some(_)) getOrElse ob

  //  Error:(37, 15) covariant type A occurs in contravariant position in type => fpinscala.chapter4.Option[A] of value ob
  //  def orElse2(ob: => Option[A]): Option[A] = this match {
  //    case None => ob
  //    case _ => this
  //  }

  def filter(f: A => Boolean): Option[A] = this match {
    case Some(a) if f(a) => this
    case _ => None
  }

  //  如果不是None的话，需要一种方法“解构”出Some(a)里面的a
  def filter1(f: A => Boolean): Option[A] =
    this flatMap (x => if (f(x)) Some(x) else None)
}

case class Some[+A](get: A) extends Option[A]

case object None extends Option[Nothing]
