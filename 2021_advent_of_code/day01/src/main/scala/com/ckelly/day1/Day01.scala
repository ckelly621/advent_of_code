package com.ckelly.day1

import scala.io.Source

object Day01 extends App {
  def solvePartOne(filename: String): Int = {
    countIncreased(Source.fromResource(filename).getLines().map(_.toInt))
  }
  def solvePartTwo(filename: String): Int = {
    countIncreased(Source.fromResource(filename).getLines().map(_.toInt).sliding(3).map(_.sum))
  }

  def countIncreased(iter: Iterator[Int]): Int = {
    iter.sliding(2).count{ _ match {
      case Seq(a, b) => b > a
    }}
  }

  println(s"First part:  ${solvePartOne("input.txt")}")
  println(s"Second part:  ${solvePartTwo("input.txt")}")
}