/* 
 * File:   hanoi.cpp
 * Author: Vlad
 *
 * Created on February 20, 2014, 11:03 PM
 */

#include <array>
#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

void transfer(const int &n, array<stack<int>, 3> &pegs,
        const int &from, const int &to, const int &use){
    if (n > 0){
        transfer(n - 1, pegs, from, use, to);
        pegs[to].push(pegs[from].top());
        pegs[from].pop();
        cout << "Move from peg " << from << " to peg " << to << "\n";
        transfer(n-1, pegs, use, to, from);
    }
}
        
int main(int argc, char** argv) {
    array<stack<int>, 3 >  pegs;
    int n = 5;
    for(int i = n; i >= 1; --i){
        pegs[0].push(i);
    }

    transfer(n, pegs, 0, 1, 2);
    
    return 0;
}

