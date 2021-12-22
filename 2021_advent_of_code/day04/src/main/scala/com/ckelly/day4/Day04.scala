package com.ckelly.day4

import scala.collection.mutable
import scala.io.Source

object Day04 extends App {
  def solvePartOne(filename: String): Int = {
    val (draws, boards) = parseInput(Source.fromResource(filename).getLines())
    var output: Int = 0
    for {
      draw <- draws if output <= 0
    } {
      boards.foreach(_.checkNumber(draw))
      output = boards.find(_.checkWin) match {
        case Some(board) => draw * board.sumRemaining
        case _ => 0
      }
    }
    output
  }

  def solvePartTwo(filename: String): Int = {
    val (draws, boards) = parseInput(Source.fromResource(filename).getLines())
    var boardsMap = boards.map(b => (b.getId, b)).toMap
    var winners = Seq[Int]()
    for {
      draw <- draws
    } {
      boardsMap.values.foreach(_.checkNumber(draw))
      while(boardsMap.values.exists(_.checkWin)) {
        boardsMap.values.find(_.checkWin) match {
          case Some(board) =>
            boardsMap -= board.getId
            winners = (draw * board.sumRemaining) +: winners
          case _ =>
        }
      }
    }
    winners.head
  }

  def parseInput(iter: Iterator[String]): (Seq[Int], Seq[BingoBoard]) = {
    val draw = iter.next().split(',').map(_.toInt).toSeq
    iter.next()
    var rows = mutable.Buffer[mutable.Seq[Int]]()
    val boards = mutable.Buffer[BingoBoard]()
    var count = 1
    for { line <- iter} {
      if (line.isBlank || !iter.hasNext) {
        rows ++= toColumns(rows)
        boards += BingoBoard(count, rows.toSeq)
        if (iter.hasNext) {
          count += 1
          rows = mutable.Buffer[mutable.Seq[Int]]()
        }
      }
      else {
        rows += mutable.Seq() ++ line.trim.split("\\s+").map(_.strip().toInt)
      }
    }
    (draw, boards.toSeq)
  }

  def toColumns(buffer: mutable.Buffer[mutable.Seq[Int]]): mutable.Buffer[mutable.Seq[Int]] = {
    val transpose = buffer.transpose
    val cols = mutable.Buffer[mutable.Seq[Int]]()
    for (item <- transpose) {
      cols += mutable.Seq() ++ item
    }
    cols
  }


  println(s"First part:  ${solvePartOne("input.txt")}")
  println(s"Second part:  ${solvePartTwo("input.txt")}")
}
