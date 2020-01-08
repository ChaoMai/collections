package fpinscala.chapter8

import org.scalacheck.{Gen, Properties}
import org.scalacheck.Prop.forAll

/**
  * Created by chaomai on 21/05/2017.
  */
object TestChapter8 extends Properties("TestChapter8") {
  val initList = Gen.listOf(Gen.choose(0, 100))
  val sumProp = forAll(initList)(ns => ns.reverse.sum == ns.sum)
  sumProp.check
}
