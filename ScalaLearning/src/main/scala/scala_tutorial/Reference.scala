package scala_tutorial

/**
  * Created by chaomai on 07/03/2017.
  */

class Ref[T] {
  // _ represents a default value.
  // This default value is
  // 0 for numeric types,
  // false for the Boolean type,
  // () for the Unit type,
  // null for all object types.
  private var contents: T = _

  def set(value: T) {
    contents = value
  }

  def get: T = contents
}

object Reference {
  def main(args: Array[String]): Unit = {
    val cell = new Ref[Int]
    cell.set(13)
    println("Reference contains the half of " + cell.get * 2)
  }
}