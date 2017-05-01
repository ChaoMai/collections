package mapreduce

import mapreduce.Common.KeyValue

/**
  * Created by chaomai on 12/04/2017.
  */
object WordCount {
  def main(args: Array[String]): Unit = {
    if (args.length < 4) println("%s: see usage comments in file".format(args))
    val paras = args.tail

    val mapF: (String, String) => List[KeyValue] =
      (_, contents) =>
        contents
          .split("[^a-zA-Z]+")
          .map(_.trim)
          .filter(_.length > 0)
          .map(KeyValue(_, "1"))
          .toList

    val reduceF: (String, List[String]) => String =
      (_, values) => values.foldRight(0)((n, acc) => n.toInt + acc).toString

    val master = Master("master")

    (paras.head, paras.tail) match {
      case ("master", t) =>
        (t.head, t.tail) match {
          case ("sequential", as) => {
            if (!as.exists(s => s.contains('*'))) Master.Sequential(master, "wcseq", as.toList, 3, mapF, reduceF)
            else println("cannot use glob in parameters")
          }
          case (masterAddr, as) => ???
        }

      case ("worker", t) => ???
      case _ => println("%s: see usage comments in file".format(args))
    }
  }
}