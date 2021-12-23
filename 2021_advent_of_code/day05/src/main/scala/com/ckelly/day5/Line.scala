package com.ckelly.day5

case class Line(points: Seq[Point]) extends LineUtils

case object Line {
  def apply(points: (Point, Point)): Line = {
    val (p1, p2) = points
    if (p2.x == p1.x) {
      val minY = Math.min(p1.y, p2.y)
      val maxY = Math.max(p1.y, p2.y)
      lazy val points = for (y <- minY to maxY) yield Point(p1.x, y)
      Line(points)
    }
    else if (p2.y == p1.y)  {
      val minX = Math.min(p1.x, p2.x)
      val maxX = Math.max(p1.x, p2.x)
      lazy val points = for (x <- minX to maxX) yield Point(x, p1.y)
      Line(points)
    }
    else if ((p2.y - p1.y) % (p2.x - p1.x) == 0) {
      val m: Int = (p2.y - p1.y) / (p2.x - p1.x)
      val minX = Math.min(p1.x, p2.x)
      val maxX = Math.max(p1.x, p2.x)
      val y0 = if (p1.x == minX) p1.y else p2.y
      lazy val points = for (x <- minX to maxX) yield Point(x, y0 + Math.abs(x - minX) * m)
      Line(points)
    }
    else {
      val m: Int = (p2.x - p1.x) / (p2.y - p1.y)
      val minY = Math.min(p1.y, p2.y)
      val maxY = Math.max(p1.y, p2.y)
      val x0 = if (p1.y == minY) p1.x else p2.x
      lazy val points = for (y <- minY to maxY) yield Point(x0 + Math.abs(y - minY) * m, y)
      Line(points)
    }
  }
}

case class Point(x: Int, y: Int)

trait LineUtils {
  def points: Seq[Point]
  def diagonal: Boolean = {
    val p1 = points.head
    val p2 = points.reverse.head
    p1.x != p2.x && p1.y != p2.y
  }
  def nonDiagonal: Boolean = !diagonal
}
