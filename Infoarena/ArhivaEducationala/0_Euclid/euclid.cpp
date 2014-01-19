#include <cstdio>

int gcd(int a, int b){
    while(b){
        int quot = b;
        b = a % quot;
        a = quot;
    }
    return a;
}

int main(int argc, char** argv) {
    freopen("euclid2.in", "r", stdin);
    freopen("euclid2.out", "w", stdout);
    
    int t;
    int a, b;
    scanf("%d", &t);
    for(; t; --t){
        scanf("%d %d", &a, &b);
        int div = gcd(a,b);
        printf("%d\n", div);
    }   
    
            
    return 0;
}

