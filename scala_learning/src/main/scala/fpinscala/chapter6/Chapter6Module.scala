package fpinscala.chapter6

/**
  * Created by chaomai on 01/05/2017.
  */
object Chapter6Module {
  def main(args: Array[String]): Unit = {
    val is = List(Coin, Turn, Coin, Turn, Coin, Coin, Turn, Turn, Coin, Turn)
    val machine = Machine(true, 10, 5)

    println(Candy.simulateMachine(is).run(machine))
    println(Machine.simulateMachine(is).run(machine))

    val machine1 = Machine(false, 2, 0)

    println(Candy.simulateMachine(is).run(machine1))
    println(Machine.simulateMachine(is).run(machine1))
  }
}
