package mapreduce

import argonaut._, Argonaut._
import better.files._
import mapreduce.Common._

/**
  * Created by chaomai on 11/04/2017.
  */
object CommonReduce {
  def doReduce(jobName: String,
               reduceTaskNumber: Int,
               outFile: String,
               nMap: Int,
               reduceF: ReduceFunc): Unit = {
    val f = File(outFile)

    val mappedKVs = (0 until nMap)
      .map(reduceName(jobName, _, reduceTaskNumber))
      .flatMap(
        filename =>
          File(filename).lines
            .map(l => l.decodeOption[KeyValue].get)
            .toList)

    mappedKVs
      .sortBy(_.key)
      .groupBy(_.key)
      .map(gs => (gs._1, reduceF(gs._1, gs._2.map(_.value).toList)))
      .foreach(kv =>
        f.appendLine(Json("key" := kv._1, "value" := kv._2).nospaces))
  }
}
