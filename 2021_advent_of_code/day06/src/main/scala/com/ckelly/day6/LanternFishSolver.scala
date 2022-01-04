package com.ckelly.day6

import scala.collection.mutable
import scala.io.Source
import scala.util.Using
import scala.util.matching.Regex

object LanternFishSolver {
  val lineRegex: Regex = "(\\d+),(\\d+) -> (\\d+),(\\d+)".r

  def solvePartOne(filename: String, days: Int = 80): Long = {
    val startingFish: Iterator[Int] = Using(Source.fromURL(getClass.getResource(filename))) { file =>
      file.getLines().toSeq.head.split(",").map(_.toInt).iterator
    }.getOrElse(Iterator.empty[Int])

    val allFish: Array[Int] = Array.ofDim(9)

    for (fish <- startingFish) allFish(fish) += 1

    for {
      day <- 0 until days
    } {
      val growthFish = allFish(0)
      allFish(0) = allFish(1)
      allFish(1) = allFish(2)
      allFish(2) = allFish(3)
      allFish(3) = allFish(4)
      allFish(4) = allFish(5)
      allFish(5) = allFish(6)
      allFish(6) = allFish(7) + growthFish
      allFish(7) = allFish(8)
      allFish(8) = growthFish
    }
    allFish.sum
  }
}
