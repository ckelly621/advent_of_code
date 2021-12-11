package com.ckelly.day2

import scala.io.Source

object Day02 extends App {
  def solvePartOne(filename: String): Int = {
    val point = Source.fromResource(filename).getLines().map(Movement.apply).foldLeft(Point())(Movement.movePoint)
    Math.abs(point.x * point.y)
  }

  def solvePartTwo(filename: String): Int = {
    val point = Source.fromResource(filename).getLines().map(Movement3.apply).foldLeft(Point3())(Movement3.movePoint)
    point.x * point.y
  }

  case class Point(x: Int = 0, y: Int = 0)
  case class Movement(moveX: Int, moveY: Int)

  object Movement {
    def movePoint(point: Point, movement: Movement): Point = Point(point.x + movement.moveX, point.y + movement.moveY)
    def apply(line: String): Movement = {
      val cols = line.split("\\s")
      val spacesToMove = cols(1).toInt
      cols.head match {
        case "forward" => Movement(spacesToMove, 0)
        case "up"       => Movement(0, spacesToMove)
        case "down"     => Movement(0, -1 * spacesToMove)
      }
    }
  }

  case class Point3(x: Int = 0, y: Int = 0, z: Int = 0)
  case class Movement3(moveX: Int, moveY: Int, moveZ: Int)

  object Movement3 {
    def movePoint(point: Point3, movement: Movement3): Point3 = {
      if (movement.moveX > 0) {
        Point3(point.x + movement.moveX, point.y + (point.z * movement.moveX), point.z + movement.moveZ)
      }
      else Point3(point.x + movement.moveX, point.y + movement.moveY, point.z + movement.moveZ)
    }
    def apply(line: String): Movement3 = {
      val cols = line.split("\\s")
      val spacesToMove = cols(1).toInt
      cols.head match {
        case "forward" => Movement3(spacesToMove, 0, 0)
        case "up"       => Movement3(0, 0, -spacesToMove)
        case "down"     => Movement3(0, 0, spacesToMove)
      }
    }
  }


  println(s"First part:  ${solvePartOne("input.txt")}")
  println(s"Second part:  ${solvePartTwo("input.txt")}")
}