package com.ckelly.day3

import scala.annotation.tailrec
import scala.io.Source

object Day03 extends App {
  def solvePartOne(filename: String): Int = {
    val transposed = Source.fromResource(filename).getLines().map(_.toCharArray.map(_.asDigit)).toArray.transpose
    val transposedSum = transposed.map(_.sum)
    val gamma = transposedSum.map(sum => if (sum >= transposed.head.length / 2) '1' else '0').mkString
    val epsilon = transposedSum.map(sum => if (sum >= transposed.head.length / 2) '0' else '1').mkString
    Integer.parseInt(gamma, 2) * Integer.parseInt(epsilon, 2)
  }

  def solvePartTwo(filename: String): Int = {
    val start = Source.fromResource(filename).getLines().toSeq
    Integer.parseInt(sieve(start, 0 ).head, 2) * Integer.parseInt(sieve(start, 0, false).head, 2)
  }

  @tailrec
  def sieve(seq: Seq[String], index: Int, takeLarger: Boolean = true): Seq[String] = {
    if (seq.length == 1 || index > seq.head.length) seq
    else {
      val zeros = seq.filter(_.charAt(index) == '0')
      val ones = seq.filter(_.charAt(index) == '1')
      if (takeLarger) {
        if (zeros.length > ones.length) sieve(zeros, index + 1) else sieve(ones, index + 1)
      }
      else {
        if (zeros.length <= ones.length) sieve(zeros, index + 1, takeLarger) else sieve(ones, index + 1, takeLarger)
      }
    }
  }


  println(s"First part:  ${solvePartOne("input.txt")}")
  println(s"Second part:  ${solvePartTwo("input.txt")}")
}
