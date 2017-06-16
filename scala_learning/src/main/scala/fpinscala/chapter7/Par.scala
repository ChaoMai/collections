package fpinscala.chapter7

import java.util.concurrent.{Callable, ExecutorService, Future, TimeUnit}

/**
  * Created by chaomai on 05/05/2017.
  */
object Par {
  type Par[A] = ExecutorService => Future[A]

  def fork[A](a: => Par[A]): Par[A] =
    es =>
      es.submit(new Callable[A] {
        override def call(): A = a(es).get
      })

  def unit[A](a: A): Par[A] = (_: ExecutorService) => UnitFuture(a)

  def lazyUnit[A](a: => A): Par[A] = fork(unit(a))

  def run[A](es: ExecutorService)(a: Par[A]): Future[A] = a(es)

  def map2[A, B, C](a: Par[A], b: Par[B])(f: (A, B) => C): Par[C] = es => {
    val af = a(es)
    val bf = b(es)
    Map2Future(af, bf, f)
  }

  def map2_1[A, B, C](a: Par[A], b: Par[B])(f: (A, B) => C): Par[C] = es => {
    val af = a(es)
    val bf = b(es)
    UnitFuture(f(af.get, bf.get))
  }

  def asyncF[A, B](f: A => B): A => Par[B] = a => lazyUnit(f(a))

  case class Map2Future[A, B, C](a: Future[A], b: Future[B], f: (A, B) => C)
      extends Future[C] {
    @volatile var cache: Option[C] = None
    override def isDone: Boolean = cache.isDefined
    override def isCancelled: Boolean = a.isCancelled || b.isCancelled
    override def cancel(evenIfRunning: Boolean): Boolean =
      a.cancel(evenIfRunning) || b.cancel(evenIfRunning)
    override def get: C = compute(Long.MaxValue)
    override def get(timeout: Long, units: TimeUnit): C =
      compute(TimeUnit.NANOSECONDS.convert(timeout, units))

    private def compute(timeoutInNanos: Long): C = cache match {
      case Some(c) => c
      case None =>
        val start = System.nanoTime
        val ar = a.get(timeoutInNanos, TimeUnit.NANOSECONDS)
        val stop = System.nanoTime
        val aTime = stop - start

        val br = b.get(timeoutInNanos - aTime, TimeUnit.NANOSECONDS)
        val ret = f(ar, br)
        cache = Some(ret)
        ret
    }
  }

  private case class UnitFuture[A](get: A) extends Future[A] {
    override def isDone: Boolean = true
    override def get(timeout: Long, unit: TimeUnit): A = get
    override def isCancelled: Boolean = false
    override def cancel(mayInterruptIfRunning: Boolean): Boolean = false
  }
}
