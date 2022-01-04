package com.ckelly.day7

import scala.io.Source
import scala.util.Using
import scala.util.control.Breaks.{break, breakable}

object CrabSolver {

  def solve(filename: String, moves: (Int, (Int, Int)) => Int): Long = {
    val crabMap = Using(Source.fromURL(getClass.getResource(filename))) { file =>
      file.getLines().toSeq.head.split(",").map(_.toInt).toSeq
    }.getOrElse(Seq[Int]()).groupBy[Int](identity).map(kv => kv._1 -> kv._2.size)

    val minValue = crabMap.keys.min
    val maxValue = crabMap.keys.max
    var min = Int.MaxValue
    breakable {
      for { i <- minValue to maxValue} {
        val newValue = crabMap.iterator.foldLeft(0)(_ + moves(i, _))
        if (newValue < min) min = newValue
        else break()
      }
    }
    min
  }

  def crabMoves(mode: Int, kv: (Int, Int)): Int = Math.abs(mode - kv._1) * kv._2
  def crabMoves2(value: Int, kv: (Int, Int)): Int = sumFrom1ToN(Math.abs(value - kv._1)) * kv._2
  def sumFrom1ToN(n: Int): Int = n * (n + 1) / 2
}
