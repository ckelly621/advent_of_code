package com.ckelly.day7

import com.ckelly.day7.CrabSolver.{crabMoves, crabMoves2, solve}

object Day07 extends App {
  println(s"First part:  ${solve("/input.txt", crabMoves)}")
  println(s"Second part:  ${solve("/input.txt", crabMoves2)}")
}
