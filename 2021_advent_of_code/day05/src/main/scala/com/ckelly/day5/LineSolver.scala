package com.ckelly.day5

import scala.collection.mutable
import scala.io.Source
import scala.util.Using
import scala.util.matching.Regex

object LineSolver {
  val lineRegex: Regex = "(\\d+),(\\d+) -> (\\d+),(\\d+)".r

  def solvePartOne(filename: String): Int = {
    Using(Source.fromURL(getClass.getResource(filename))) { file =>
      val pointMap: mutable.HashMap[Point, Int] = mutable.HashMap()
      for {
        line <- file.getLines().map(toLine).filter(_.nonDiagonal)
        point <- line.points.iterator
      } {
        if (pointMap.contains(point)) pointMap.update(point, pointMap(point) + 1)
        else pointMap.put(point, 1)
      }

      pointMap.count(kv => kv._2 >= 2)
    }.getOrElse(0)
  }

  def solvePartTwo(filename: String): Int = {
    Using(Source.fromURL(getClass.getResource(filename))) { file =>
      val pointMap: mutable.HashMap[Point, Int] = mutable.HashMap()
      for {
        line <- file.getLines().map(toLine)
        point <- line.points.iterator
      } {
        if (pointMap.contains(point)) pointMap.update(point, pointMap(point) + 1)
        else pointMap.put(point, 1)
      }

      pointMap.count(kv => kv._2 >= 2)
    }.getOrElse(0)
  }

  def toLine(string: String): Line = {
    Line(toPoints(string))
  }

  def toPoints(string: String): (Point, Point) = {
    string match {
      case lineRegex(x1, y1, x2, y2) => (Point(x1.toInt, y1.toInt), Point(x2.toInt, y2.toInt))
    }
  }

}
