/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package sumpartitionsdistinctterms

import math._;

object Solution {

  // ways[i][j] = ways[i][j - 1] + ways[i - j^p][j-1];
  def ways(n: Int, largestNumber: Int, p: Int): Int = {
    if (n == 0) {
      1;
    } else if (largestNumber == 0) {
      0;
    } else if (n < 0) {
      0;
    } else {
      ways(n, largestNumber - 1, p) +
        ways(n - math.pow(largestNumber, p).toInt, largestNumber - 1, p);
    }
  }

  def numberOfWays(X: Int, N: Int): Int = {
    ways(X, getLargestNumber(0, X, X, N), N);
  }

  def getLargestNumber(a: Int, b: Int, X: Int, N: Int): Int = {
    val m: Int = (a + b) / 2;
    val result: Int = math.pow(m, N).toInt;
    val nextResult: Int = math.pow(m + 1, N).toInt;

    if (result > X) {
      getLargestNumber(a, m - 1, X, N);
    } else if (result <= X && nextResult > X) {
      m;
    } else {
      getLargestNumber(m + 1, b, X, N);
    }
  }

  def main(args: Array[String]) {
    //    println(numberOfWays(100, 2));
    println(numberOfWays(readInt(), readInt()));
}
  }