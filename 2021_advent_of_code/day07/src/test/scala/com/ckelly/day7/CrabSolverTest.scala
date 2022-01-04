package com.ckelly.day7

import com.ckelly.day7.CrabSolver.{crabMoves, crabMoves2, solve}
import org.junit.runner.RunWith
import org.specs2.mutable.Specification
import org.specs2.runner.JUnitRunner

@RunWith(classOf[JUnitRunner])
class CrabSolverTest extends Specification {
  "Day07 crab solver" should {
    "should return 37 for part one" in {
      solve("/example.txt", crabMoves) mustEqual 37
    }
    "should return 168 for part two" in {
      solve("/example.txt", crabMoves2) mustEqual 168
    }
  }
}
