package com.eigengo.lift.spark

import akka.actor.ActorSystem
import com.eigengo.lift.spark.JobManagerProtocol.BatchJobSubmit
import com.typesafe.config.ConfigFactory

object Main extends App {

  override def main(args: Array[String]): Unit = {
    val system = ActorSystem("Spark job manager")

    val config = ConfigFactory.load()
    val master = config.getString("spark.master")

    val manager = system.actorOf(JobManager.props(master, config))

    manager ! BatchJobSubmit("PrintSequence")
  }
}
