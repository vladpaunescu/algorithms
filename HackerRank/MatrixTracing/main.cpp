#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

// #define L 1000
# define mod 1000000007
using namespace std;

// int pas[L+1][L+1];

long long prod(int inf, int sup){
    long long res = inf;
    for(int i = inf + 1; i <= sup; i++){
        res*=i;
        if (res > mod){
            res = res % mod;
        }
    }
    return res;
}

long combine(int m, int n){
    if(m < n){
        int temp = m;
        m = n;
        n = temp;
    }
   
    int i = m + n - 2;
    int j = n - 1;
    
    if (i - j > j){
        j = i-j;
    }
    
    return (prod(i - j +1, i) / prod(1, j)) % mod;
}

//void buildPascal(){
//    for(int i = 1; i <= L; i++){
//        pas[i][1] = pas[1][i] = 1;
//    }
//    for(int i = 2; i <= L; i++){
//        for(int j = 2; j <= L;j++){
//            pas[i][j] = (pas[i-1][j] + pas[i][j-1]) % 1000000007;
//        }
//    }
//}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int t;
    int m, n;
  //  buildPascal();
    
    cin >>t;
    for(int i = 1; i <= t; ++i){
        cin>>m>>n;
        long comb = combine(m,n);
        cout<<comb<<endl;
    }
    return 0;
}
