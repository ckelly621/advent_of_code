package com.ckelly.day6

import com.ckelly.day6.LanternFishSolver.solvePartOne
import org.junit.runner.RunWith
import org.specs2.mutable.Specification
import org.specs2.runner.JUnitRunner

@RunWith(classOf[JUnitRunner])
class LanternFishSolverTest extends Specification {
  "Day06" should {
    "should return 5934 for part one" in {
      solvePartOne("/example.txt") mustEqual 5934L
    }
    "should return 26984457539 for part two" in {
      solvePartOne("/example.txt", 256) mustEqual 26984457539L
    }
  }
}
