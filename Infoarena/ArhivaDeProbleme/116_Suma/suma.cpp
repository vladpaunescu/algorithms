/* 
 * File:   luna.cpp
 * Author: Vlad
 *
 * Created on January 17, 2014, 11:54 PM
 */

#include <cstdio>

using namespace std;


int main(int argc, char** argv) {
    freopen("suma.in", "r", stdin);
    freopen("suma.out", "w", stdout);
    int N, P, S, a, b, c;
    scanf("%d %d", &N , &P);
    // S = (n-1) * n * (n+1)/3 se divide sigur cu 3
    // (a * b * c) mod x = ((((a mod x) * (b mod x)) mod x) * (c mod x)) mod x
    if((N-1) % 3 == 0){
        a = (N-1)/3;
        b = N;
        c = N+1;      
    } else if (N % 3 == 0){
        a = N - 1;
        b = N / 3;
        c = N + 1;
    } else{
        a = N - 1;
        b = N;
        c = (N + 1) / 3;
    }
    
    S = ((a % P) * (b % P)) % P;
    S = (S * (c % P)) % P;
   
    printf("%d\n", S);

    return 0;
}

