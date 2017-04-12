package mapreduce

import argonaut._, Argonaut._
import better.files._
import mapreduce.Common._

/**
  * Created by chaomai on 11/04/2017.
  */
object CommonMap {
  def doMap(jobName: String,
            mapTaskNumber: Int,
            inFile: String,
            nReduce: Int,
            mapF: (String, String) => List[KeyValue]): Unit = {
    val intermediateFiles =
      (0 until nReduce).map(i => File(reduceName(jobName, mapTaskNumber, i)))

    File(inFile).lines
      .flatMap(l => mapF(inFile, l))
      .foreach(kv => {
        intermediateFiles((kv.key.hashCode & 0x7FFFFFFF) % nReduce)
          .appendLine(kv.asJson.nospaces)
      })
  }
}
