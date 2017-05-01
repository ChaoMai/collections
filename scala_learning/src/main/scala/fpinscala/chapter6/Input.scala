package fpinscala.chapter6

/**
  * Created by chaomai on 01/05/2017.
  */
sealed trait Input

case object Coin extends Input

case object Turn extends Input

case class Machine(lockedState: Boolean, candies: Int, coins: Int)

object Candy {
  def update =
    (i: Input) =>
      (s: Machine) =>
        (i, s) match {
          case (_, Machine(_, 0, _)) => s
          case (Coin, Machine(false, _, _)) => s
          case (Turn, Machine(true, _, _)) => s
          case (Coin, Machine(true, candy, coin)) =>
            Machine(false, candy, coin + 1)
          case (Turn, Machine(false, candy, coin)) =>
            Machine(true, candy - 1, coin)
    }

  def simulateMachine(inputs: List[Input]): State[Machine, (Int, Int)] =
    for {
      _ <- State.sequence(inputs map (State.modify[Machine] _ compose update))
      s <- State.get
    } yield (s.coins, s.candies)
}

object Machine {
  def trans: Input => Machine => Machine =
    i =>
      m =>
        i match {
          case Coin =>
            m match {
              case Machine(true, 0, _) => m
              case Machine(true, candies, coins) =>
                Machine(false, candies, coins + 1)

              case Machine(false, _, _) => m
            }

          case Turn =>
            m match {
              case Machine(true, _, _) => m
              case Machine(false, candies, coins) =>
                Machine(true, candies - 1, coins)
            }
    }

  def simulateMachine(inputs: List[Input]): State[Machine, (Int, Int)] =
    for {
      //      _ <- State.sequence(inputs.map(i => State.modify(trans(i))))

      // val fm: (Machine => Machine) => State[Machine, Unit] = State.modify[Machine] _
      // trans: (Input) => (Machine) => Machine
      _ <- State.sequence(inputs.map(State.modify1[Machine] _ compose trans))
      s <- State.get
    } yield (s.coins, s.candies)
}
