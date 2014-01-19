#include <cstdio>
#include <assert.h>

// see http://infoarena.ro/algoritmul-lui-euclid
void euclid(int a, int b, int *d, int *x, int *y){
    if(b == 0){
        *d = a;
        *x = 1;
        *y = 0;                
    } else {
        int x0, y0;
        // solve b * x0 + (a % b) * y0 = d
        euclid(b, a % b, d, &x0, &y0);
        
        // a * x + b * y = d
        *x = y0;
        *y = x0 - (a/b) * y0;
    }
}

int main(int argc, char** argv) {
    freopen("euclid3.in", "r", stdin);
    freopen("euclid3.out", "w", stdout);
    
    int t;
    for(scanf("%d", &t), assert(t <= 100); t; --t){ 
       int a, b, c; 
       scanf("%d %d %d", &a, &b, &c);
       // solve a*x + b*y = c      
       int x, y, d;
       euclid(a, b, &d, &x, &y);
       if(c % d){
            // no solution if c is not a multiple of d
            printf("0 0\n");
        } else {
            // solution for a * x + b * y = c, c = m*d;
            int m = c/d;
            x *= m;
            y *= m;
            printf("%d %d\n", x, y);
        }
    }   
    return 0;
}

