import fpinscala.chapter4._

class Animal(v: String) {
  override def toString: String = v
}

class Dog(v: String) extends Animal(v) {
  override def toString: String = v
}

class Poodle(v: String) extends Dog(v) {
  override def toString: String = v
}

val a: Option[Animal] = Some(new Animal("animal"))
val ad: Option[Animal] = Some(new Dog("dog"))
val d: Option[Dog] = Some(new Dog("dog"))
val d1: Option[Dog] = Some(new Dog("dog1"))
val dp: Option[Dog] = Some(new Poodle("poodle_dog"))
val p: Option[Poodle] = Some(new Poodle("poodle_pure"))

d.orElse(a)
None.orElse(a)

d.orElse(d1)
None.orElse(d1)

d.orElse(dp)
None.orElse(dp)

d.orElse(p)
None.orElse(p)

class V1[+A]

class V2[-B] extends V1[B]
