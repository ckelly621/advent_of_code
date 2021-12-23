package com.ckelly.day5

import com.ckelly.day5.LineSolver.{solvePartOne, solvePartTwo}
import org.junit.runner.RunWith
import org.specs2.mutable.Specification
import org.specs2.runner.JUnitRunner

@RunWith(classOf[JUnitRunner])
class LineSolverTest extends Specification {
  "Day05" should {
    "should return 5 for part one" in {
      solvePartOne("/example.txt") mustEqual 5
    }
    "should return 12 for part two" in {
      solvePartTwo("/example.txt") mustEqual 12
    }
  }
}
