/* 
 * File:   sum.cpp
 * Author: vpaunescu
 *
 * Created on January 24, 2014, 1:59 PM
 */

#include <iostream>

using namespace std;

int s[100][100];
int main(int argc, char** argv) {
    int n = 10;  
    for(int i = 1; i <= n; i++)
        s[i][i] = 1;

    for(int i = 2; i <= n; i++){
        for(int j = 1; j <= i; j++){           
            for(int k = i-1; k >= i/2.0; k--){
                if (k == i-k){
                    s[i][j]--;
                }
                s[i][j] += s[i-k][min(j, i-k)] ;             
            }
        }
    }
    
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <=n;j++){
            cout<<s[i][j]<<" ";
        }
        cout<<endl;
    }
    
    return 0;
}

