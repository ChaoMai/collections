name := "mit_6-824"

version := "1.0"

scalaVersion := "2.12.2"

libraryDependencies += "org.scalactic" %% "scalactic" % "3.0.1"
libraryDependencies += "org.scalatest" %% "scalatest" % "3.0.1" % "test"
libraryDependencies += "com.github.pathikrit" %% "better-files" % "3.0.0"
libraryDependencies += "io.argonaut" %% "argonaut" % "6.2-RC2"
libraryDependencies += "com.typesafe.akka" %% "akka-actor" % "2.5.2"
libraryDependencies += "com.typesafe.akka" %% "akka-testkit" % "2.5.2" % Test
libraryDependencies += "com.typesafe.akka" %% "akka-remote" % "2.5.2"
