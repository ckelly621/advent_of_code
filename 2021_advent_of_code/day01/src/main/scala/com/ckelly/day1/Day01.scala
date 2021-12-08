package com.ckelly.day1

import scala.io.Source

object Day01 extends App {
  def solvePartOne(filename: String): Int = {
    Source.fromResource(filename).getLines().map(_.toInt).sliding(2).count(increased)
  }
  def solvePartTwo(filename: String): Int = {
    Source.fromResource(filename).getLines().map(_.toInt).sliding(3).map(_.sum).sliding(2).count(increased)
  }
  def increased(pair: Seq[Int]): Boolean = {
    pair.length == 2 && pair(1) > pair.head
  }

  println(s"First part:  ${solvePartOne("input.txt")}")
  println(s"Second part:  ${solvePartTwo("input.txt")}")
}