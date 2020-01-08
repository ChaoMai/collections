package fpinscala.chapter4

/**
  * Created by chaomai on 01/04/2017.
  */
case class Person(name: Name, age: Age)

sealed class Name(val value: String)

sealed class Age(val value: Int)

object Person {
  def mkName(name: String): Either[String, Name] =
    if (name == "" || name == null) Left("Name is empty.")
    else Right(new Name(name))

  def mkAge(age: Int): Either[String, Age] =
    if (age < 0) Left("Age is out of range.")
    else Right(new Age(age))

  def mkPerson(name: String, age: Int): Either[String, Person] =
    (mkName(name) map2 mkAge(age))(Person(_, _))

  def mkPerson1(
      name: String,
      age: Int): Either[(Either[String, Name], Either[String, Age]), Person] =
    (mkName(name), mkAge(age)) match {
      case (Right(n), Right(a)) => Right(Person(n, a))
      case (Left(n), Left(a)) => Left((Left(n), Left(a)))
      case (Left(n), Right(a)) => Left((Left(n), Right(a)))
      case (Right(n), Left(a)) => Left((Right(n), Left(a)))
    }

  def mkPerson2(name: String,
                age: Int): Either[List[Either[String, _]], Person] =
    (mkName(name), mkAge(age)) match {
      case (Right(n), Right(a)) => Right(Person(n, a))
      case (Left(n), Left(a)) => Left(List(Left(n), Left(a)))
      case (Left(n), Right(a)) => Left(List(Left(n)))
      case (Right(n), Left(a)) => Left(List(Left(a)))
    }

  def mkName1(name: String): Partial[String, Name] =
    if (name == "" || name == null) Errors(Seq("Name is empty."))
    else Success(new Name(name))

  def mkAge1(age: Int): Partial[String, Age] =
    if (age < 0) Errors(Seq("Age is out of range."))
    else Success(new Age(age))

  def mkPerson3(name: String, age: Int): Partial[String, Person] =
    (mkName1(name) map2 mkAge1(age))(Person(_, _))
}
