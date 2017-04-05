package scala_tutorial

/**
  * Created by chaomai on 05/03/2017.
  */

abstract class Tree

// 1. 由于是case class，在创建类的时候就不是必须要new来创建了
// 2. 构造函数的参数的getter function会被自动定义
// 3. equal和hashCode会默认提供，which work on the structure of the instances and not on their identity
// 4. toString默认提供，对于x+1，会输出Sum(Var(x), Const(1))
// 5. instances of these classes can be decomposed through pattern matching
case class Sum(l: Tree, r: Tree) extends Tree

case class Var(n: String) extends Tree

case class Const(v: Int) extends Tree

object Calculator {
  type Environment = String => Int

  def main(args: Array[String]): Unit = {
    val exp: Tree = Sum(Sum(Var("x"), Var("x")), Sum(Const(7), Var("y")))
    val env: Environment = {
      case "x" => 5
      case "y" => 7
    }
    println("Expression: " + exp)
    println("Evaluation with x=5, y=7: " + eval(exp, env))
    println("Derivative relative to x:\n " + derive(exp, "x"))
    println("Simplified derivative relative to x:\n  " + simplify(derive(exp, "x")))
    println("Derivative relative to y:\n " + derive(exp, "y"))
    println("Simplified derivative relative to y:\n  " + simplify(derive(exp, "y")))
  }

  // 首先check t是不是Sum，如果是，则分别把左右子树bind到l和r，然后继续箭头右边的计算
  // 如果不是Sum，这继续往下check
  def eval(t: Tree, env: Environment): Int = t match {
    case Sum(l, r) => eval(l, env) + eval(r, env)
    case Var(n) => env(n)
    case Const(v) => v
  }

  def derive(t: Tree, v: String): Tree = t match {
    case Sum(l, r) => Sum(derive(l, v), derive(r, v))

    // case后面跟着if的表达式叫做guard，当类型匹配且表达式为true的时候，才会成功匹配
    case Var(n) if (n == v) => Const(1)

    // wild-card，匹配任何value，且不bind到一个name
    case _ => Const(0)
  }

  def simplify(t: Tree): Const = t match {
    case Sum(l, r) => (l, r) match {
      case (Const(l), Const(r)) => Const(l + r)

      // 变量绑定，变量s1绑定了模式Sum(_, _)，如果匹配成功，匹配对象就会赋值到定义的变量中
      case (s1@Sum(_, _), s2@Sum(_, _)) => Const(simplify(s1).v + simplify(s2).v)
      case (s1@Sum(_, _), Const(r)) => Const(simplify(s1).v + r)
      case (Const(l), s2@Sum(_, _)) => Const(l + simplify(s2).v)
    }
  }
}