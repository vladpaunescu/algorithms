#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

// #define L 1000
#define P 1000000007
#define MAX 2000002
using namespace std;

long fact[MAX];

void computeFact(){
    fact[0] = 1;
    for(int i = 1; i < MAX; ++i){
        fact[i] = (i * fact[i-1]) % P;
    }
}
// (a * b * c) mod x = ((((a mod x) * (b mod x)) mod x) * (c mod x)) mod x
long power(int a, int n){
      
    if( n == 0){
        return 1;
    }
    if(n % 2 == 0){
        return  (power(a, n/2) * power(a, n/2)) % P;
    }
    return  ((power(a, n/2) * power(a, n/2) % P) * a) % P;
}

//function modular_pow(base, exponent, modulus)
//    result := 1
//    while exponent > 0
//        if (exponent mod 2 == 1):
//           result := (result * base) mod modulus
//        exponent := exponent >> 1
//        base = (base * base) mod modulus
//    return result

long modularPow(long base, long exponent, long modulus){
    long result = 1;
    while(exponent > 0){
        if (exponent % 2 == 1){
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base ) % modulus;
    }
    return result;
}



long  combine(int m, int n) {
    // solution is (m + n - 2)! / (n - 1)! (m-1)!  mod p
    //    According to [Fermat’s little theorem’
    //a^(p-1) mod p = 1
    //Multiplying both side by a^(-1) we can get inverse of a.
    //a^(p-1)* a^(-1) mod p = a^(-1) mod p
    //a^(-1) mod p = a^(p-2) mod p.
    //As you already know, solution is
    //((n-1+m-1)! / (n-1)!*(m-1)!) mod p
    //= (n-1+m-1)! * (n-1)!^(-1) ^ (m-1)!^(-1)         mod p
    //= (n-1+m-1)! * (n-1)!^(p-2) * (m-1)!^(p-2)       mod p
    // a*b mod m = ((a mod m)*(b mod m)) mod m
    long a, b, c;
    a = fact[n-1 + m-1];
    b = fact[n-1];
    c = fact[m-1];
    b = modularPow(b, P-2, P);
    c = modularPow(c, P-2, P);
    
    return ((a * b) % P * c) % P;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int t;
    int m, n;
    computeFact();

    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cin >> m >> n;
        long comb = combine(m, n);
        cout << comb << endl;
    }
    return 0;
}
