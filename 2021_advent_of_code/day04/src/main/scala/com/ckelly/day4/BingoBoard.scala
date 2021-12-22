package com.ckelly.day4

import scala.collection.mutable
import scala.collection.mutable.{Set => MSet}

class BingoBoard(id: Int, board: Seq[MSet[Int]]){
  def checkNumber(number: Int): Unit = {
    for { set <- board } {
      if (set.contains(number)) set -= number
    }
  }

  def sumRemaining: Int =board.foldLeft(Set[Int]())(_ ++ _).sum

  def checkWin: Boolean = board.exists(s => s.isEmpty)

  def getId: Int = id

}

object BingoBoard {
  def apply(id: Int, board: Seq[mutable.Seq[Int]]): BingoBoard = {
    val newBoard: Seq[mutable.Set[Int]] = board.map(b => b.foldLeft(mutable.Set[Int]())(_ += _))
    new BingoBoard(id, newBoard)
  }
}
