package scala_by_example.chapter2

/**
  * Created by chaomai on 07/03/2017.
  */
object sort {
  def sort(xs: Array[Int]): Unit = {
    def swap(i: Int, j: Int): Unit = {
      val t = xs(i)
      xs(i) = xs(j)
      xs(j) = t
    }

    def sort1(l: Int, r: Int): Unit = {
      val pivot = xs((l + r) / 2)
      var i = l
      var j = r

      while (i <= j) {
        while (xs(i) < pivot) {
          i += 1
        }
        while (xs(j) > pivot) {
          j -= 1
        }
        if (i <= j) {
          swap(i, j)
          i += 1
          j -= 1
        }
      }

      if (l > i) {
        sort1(l, j)
      }
      if (j < r) {
        sort1(i, r)
      }
    }

    sort1(0, xs.length - 1)
  }

  def main(args: Array[String]): Unit = {
    val xs = Array[Int](5, 1, 2, 4, 3)
    sort(xs)
    println(xs)
  }
}