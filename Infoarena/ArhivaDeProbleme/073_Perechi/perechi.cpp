/* 
 * File:   luna.cpp
 * Author: Vlad
 *
 * Created on January 17, 2014, 11:54 PM
 */

#include <cstdio>

using namespace std;
int N, k;
int primes[10000], exp[10000];


void computeFactorsDecomposition() {
    k = 0;
    for (int div = 2; div * div <= N; ++div) {
        if (N % div == 0) {
            primes[k] = div;
            exp[k] = 0;
            while (N % div == 0) {
                exp[k]++;               
                N /= div;
            }
            k++;
        }
    }
    
    // check prime
    if(N > 1){
        primes[k] = N;
        exp[k] = 1;
        k++;
    }    
}

int main(int argc, char** argv) {
    freopen("perechi.in", "r", stdin);
    freopen("perechi.out", "w", stdout);
    scanf("%d", &N);
    computeFactorsDecomposition();
    // compute number of factors
    
    long result = 1;
    for(int i = 0; i < k; ++i){
        //printf("%d %d\n", primes[i], exp[i]);
        result *= (2 * exp[i] + 1);
    }
    result = (result + 1)/2;
    printf("%ld\n", result);

    return 0;
}

