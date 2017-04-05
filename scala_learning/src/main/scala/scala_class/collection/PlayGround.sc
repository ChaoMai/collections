// Arrays
// 有序，可保存重复的元素，mutable
val numbers = Array(1, 2, 3, 4, 5, 1, 2, 3, 4, 5)
numbers(3) = 10

// Lists
// 有序，可保存重复的元素，immutable
val numbers1 = List(1, 2, 3, 4, 5, 1, 2, 3, 4, 5)
// immutable
// numbers1(3) = 10

// Sets
// 无序，无重复元素，immutable
val numbers2 = Set(1, 2, 3, 4, 5, 1, 2, 3, 4, 5)

// Tuple
// tuple把逻辑上相关的items放到一起，可以不需要使用class，方便
val hostPort = ("localhost", 80)

// 和class不同的是，要访问member只能用位置，从1起
hostPort._1
hostPort._2

// tuple可以很好的与pattern matching结合
hostPort match {
  case ("localhost", port) => port
  case (host, port) => (host, port)
}

// ->语法糖可以方便的构造tupel
1 -> 2
"localhost" -> 80

// Maps
// 可保存基本数据类型，immutable
// 这里的->与上面tuple里的是一样的
Map(1 -> 2)
Map("foo" -> "bar")

Map(1 -> "one", 2 -> "two")
Map(1 -> Map("foo" -> "bar"))
Map("timesTwo" -> { (x: Int) => 2 * x })

// Option
// 有可能包含值的容器
// Option是泛型，有两个子类，Some[T]和None
// Map.get使用Option作为返回值类型
val numbersMap = Map("one" -> 1, "two" -> 2)
numbersMap.get("two")
numbersMap.get("three")

// 数据现在是存放在Option里面的，可以提取出来
val result = if (numbersMap.get("two").isDefined) {
  numbersMap.get("two").get * 2
  //  numbersMap("two") * 2
} else {
  0
}

// 更简单的方法是
val result1 = numbersMap.get("two").getOrElse(0) * 2
val result2 = numbersMap.getOrElse("two", 0) * 2

val result3 = numbersMap.get("two") match {
  case Some(n) => n * 2
  case None => 0
}

// Functional Combinators
// map
// List(1, 2, 3) map squared
// 把函数squared应用到了List(1, 2, 3)的每个元素上
// 并返回一个新的List
// 这个操作叫做map组合子（map combinators）
val nums = List(1, 2, 3, 4)
nums.map((i: Int) => i * 2)

def timesTwo(i: Int): Int = i * 2
nums.map(timesTwo)

// foreach
// 类似map，但什么都不返回
// 如果尝试获取返回值，那变量里的值是Unit类型的
nums.foreach((i: Int) => i * 2)
val unit = nums.foreach((i: Int) => i * 2)


// filter
// 移除predicate为false的元素
nums.filter((i: Int) => i % 2 == 0)

// zip
// 聚合两个lists为list of pairs
// 结果的长度将就短的list
List(1, 2, 3).zip(List("a", "b", "c"))
nums.zip(List("a", "b", "c"))
List("a", "b", "c").zip(nums)

// partition
// 根据给定谓词分割
nums.partition(_ % 2 == 0)
val nums1 = Set(1, 2, 3, 4, 5, 1, 2, 3)
nums1.partition(_ % 2 == 0)

// find
// 返回第一个匹配谓词的元素
// 返回类型为Some[T]或None
nums.find((i: Int) => i > 3)

// drop
// 删除前i个元素
nums.drop(2)

// dropWhile
// 删除使谓词为真的元素，直到遇到使谓词为假时停止
nums.dropWhile(_ % 2 != 0)
List(1, 1, 3, 2, 3, 4).dropWhile(_ % 2 != 0)
List(1, 1, 3, 2, 3, 4).dropWhile((i: Int) => i < 3)

// foldLeft
// Applies a binary operator to
// a start value and all elements of this traversable
// or iterator, going left to right.
nums.foldLeft(0) { (m: Int, n: Int) =>
  println("m: " + m + " n: " + n)
  m + n
}

// foldRight
// 和foldLeft一样，只是运行过程相反
nums.foldRight(0) { (m: Int, n: Int) =>
  println("m: " + m + " n: " + n)
  m + n
}

// flatten
// 正如名字所述
List(List(1, 2), List(3, 4)).flatten

// flatMap
// 结合map和flatten，函数会被应用到嵌套的list上
// 对于下面是List(1, 2)和List(3, 4))
List(List(1, 2), List(3, 4)).flatMap(
  (x: List[Int]) => x.map(_ * 2)
)
List(List(1, 2), List(3, 4)).map(
  (x: List[Int]) =>
    x.map((i: Int) => i * 2)
).flatten
List(List(1, 2), List(3, 4)).map(
  (x: List[Int]) => x.map(_ * 2)
).flatten

List(List(1, 2), List(3, 4)).flatMap(
  x => x.zip(List('a', 'b'))
)

// Generalized functional combinators
def ourMap(numbers: List[Int], fn: Int => Int): List[Int] = {
  numbers.foldRight(List[Int]()) {
    (x: Int, xs: List[Int]) =>
      println("x: " + x + " xs: " + xs)
      fn(x) :: xs
  }
}

ourMap(nums, (i: Int) => i + 1)

ourMap(nums, timesTwo)

ourMap(nums, timesTwo(_))

// better way to understand ourMap
val nums2 = List(1, 2, 3)
nums2.foldLeft(List[Int]()) {
  (xs: List[Int], x: Int) =>
    println("xs: " + xs + " x: " + x)
    x :: xs
}

// functional combinators for Map
val extensions = Map("steve" -> 100, "bob" -> 101, "joe" -> 201)

// Yuck! for the tedious positional accessors
extensions.filter(
  (namePhone: (String, Int)) => namePhone._2 < 200
)
extensions.foldLeft(List[Int]()) {
  (xs: List[Int], x: (String, Int)) => x._2 :: xs
}

// nicer way
extensions.filter({
  case (name, extension) => extension < 200
})
