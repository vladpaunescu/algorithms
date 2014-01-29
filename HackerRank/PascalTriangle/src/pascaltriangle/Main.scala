/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package pascaltriangle

object Main {
    def pascal(line: Int, col:Int, pr:Boolean):List[List[Int]] = {
        if(line == 1 && col == 1){
            if(pr) { println("pizda");}
            1;
        } else if(line < col){
          println("aici");
            0;
        } else {
            if(pr) { print(pascal(line - 1, col, true) + pascal(line - 1, col - 1, true)); print(' '); }
            if(line == col){
                println();
            }
            pascal(line - 1, col, false) + pascal(line - 1, col - 1, false);
        }
       
        
    }
    def solve(n: Int){
            pascal(n, n, true);
    }
    def main(args: Array[String]) {
       solve(4);
    }
}
