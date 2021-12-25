package com.ckelly.day6

import scala.collection.mutable
import scala.io.Source
import scala.util.Using
import scala.util.matching.Regex

object LanternFishSolver {
  val lineRegex: Regex = "(\\d+),(\\d+) -> (\\d+),(\\d+)".r

  def solvePartOne(filename: String, days: Int = 80): Long = {
    val startingFish: Seq[Int] = Using(Source.fromURL(getClass.getResource(filename))) { file =>
      file.getLines().toSeq.head.split(",").map(_.toInt).toSeq
    }.getOrElse(Seq[Int]())

    val fishMap: mutable.Map[Int, Long] =
      mutable.Map(0 -> 0L, 1 -> 0L, 2 -> 0L, 3 -> 0L, 4 -> 0L, 5 -> 0L, 6 -> 0L, 7 -> 0L, 8 -> 0L)

    for (fish <- startingFish) fishMap.update(fish, fishMap(fish) + 1)

    for {
      day <- 0 until days
    } {
      val growthFish = fishMap(0)
      fishMap(0) = fishMap(1)
      fishMap(1) = fishMap(2)
      fishMap(2) = fishMap(3)
      fishMap(3) = fishMap(4)
      fishMap(4) = fishMap(5)
      fishMap(5) = fishMap(6)
      fishMap(6) = fishMap(7) + growthFish
      fishMap(7) = fishMap(8)
      fishMap(8) = growthFish
    }
    fishMap.values.sum
  }
}
