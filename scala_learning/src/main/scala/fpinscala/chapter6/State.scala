package fpinscala.chapter6

/**
  * Created by chaomai on 28/04/2017.
  */
// 可以看作是对 state action，S => (A, S) 的封装
case class State[S, +A](run: S => (A, S)) {
  def map[B](f: A => B): State[S, B] = flatMap(a => State.unit(f(a)))

  def map1[B](f: A => B): State[S, B] = State { s =>
    val (a, s1) = run(s)
    (f(a), s1)
  }

  def map2[B, C](sb: State[S, B])(f: (A, B) => C): State[S, C] =
    flatMap(a => sb.map(b => f(a, b)))

  def map2_1[B, C](sb: State[S, B])(f: (A, B) => C): State[S, C] = State { s =>
    val (a, s1) = run(s)
    val (b, s2) = sb.run(s1)
    (f(a, b), s2)
  }

  def flatMap[B](f: A => State[S, B]): State[S, B] = State { s =>
    val (a, s1) = run(s)
    f(a).run(s1)
  }
}

object State {
  def unit[S, A](a: A): State[S, A] = State(s => (a, s))

  // foldRight 实际上需要遍历 list 两次，因为有一个展开（把值放到 stack），
  // 然后再 fold 的过程。
  def sequenceViaFoldRight[S, A](sas: List[State[S, A]]): State[S, List[A]] =
    sas.foldRight(unit[S, List[A]](List[A]()))((s, acc) => s.map2(acc)(_ :: _))

  // foldLeft 是尾递归，更高效。
  def sequenceViaFoldLeft[S, A](sas: List[State[S, A]]): State[S, List[A]] =
    sas.foldLeft(unit[S, List[A]](List[A]()))((acc, s) => s.map2(acc)(_ :: _))

  def sequence[S, A](sas: List[State[S, A]]): State[S, List[A]] = {
    def go(s: S, actions: List[State[S, A]], acc: List[A]): (List[A], S) =
      actions match {
        case Nil => (acc.reverse, s)
        case h :: t => {

          val (v, s1) = h.run(s)
          go(s1, t, v :: acc)
        }
      }

    State(s => go(s, sas, List[A]()))
  }

  def modify[S](f: S => S): State[S, Unit] =
    for {
      s <- get
      _ <- set(f(s))
    } yield ()

  def modify1[S](f: S => S): State[S, Unit] =
    get[S].flatMap(s => set(f(s)).map(i => i))

  def get[S]: State[S, S] = State(s => (s, s))

  def set[S](s: S): State[S, Unit] = State(_ => ((), s))
}
