package mapreduce

import argonaut._, Argonaut._

/**
  * Created by chaomai on 11/04/2017.
  */
object Common {
  val debugEnabled = false

  def debug(fmt: String, args: Any*): Unit =
    if (debugEnabled) println(fmt.format(args: _*))

  case class KeyValue(key: String, value: String)

  implicit def KeyValueEncodeJson: EncodeJson[KeyValue] =
    EncodeJson(kv => Json("key" := kv.key, "value" := kv.value))

  implicit def KeyValueDecodeJson: DecodeJson[KeyValue] =
    DecodeJson(c =>
      for {
        key <- (c --\ "key").as[String]
        value <- (c --\ "value").as[String]
      } yield KeyValue(key, value))

  val mapPhase = "Map"
  val reducePhase = "Reduce"

  def reduceName(jobName: String, mapTask: Int, reduceTask: Int): String =
    "mrtmp." + jobName + "-" + mapTask.toString + "-" + reduceTask.toString

  def mergeName(jobName: String, reduceTask: Int): String =
    "mrtmp." + jobName + "-" + reduceTask.toString
}
