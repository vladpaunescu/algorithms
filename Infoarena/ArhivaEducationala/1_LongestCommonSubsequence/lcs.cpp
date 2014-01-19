/* 
 * File:   main.cpp
 * Author: vlad
 *
 * Created on February 10, 2013, 12:21 AM
 */

#include <cstdio>

#define MAX(a,b) (((a)>(b)) ? (a) : (b))
#define FOR(i, a, b) for ((i) = (a); (i) <= (b); ++(i))
#define NMax 1025

int c[NMax][NMax];

void lcs(int a[], int b[], int m, int n){
    int i, j;   
    int sir[NMax];
    // c[i][j] = 0, if i = 0, or j = 0;
    FOR(i, 0, m){
        c[i][0] = 0;
    }    
    FOR(j, 0, n){
        c[0][j] = 0;
    }
    
    FOR(i, 1, m){
        FOR(j , 1, n){
            if(a[i] == b[j]){
                c[i][j] = c[i - 1][j - 1] + 1;
            }
            else {
                c[i][j] = MAX(c[i][j-1], c[i-1][j]);
            }            
        }
    }
   
    int max = c[m][n];
    // trace back the longest common subsequence
    for(i = m, j = n; i && j; ){
        if(a[i] == b[j]){
            sir[max--] = a[i];
            --i, --j;
        }
        else if(c[i - 1][j] > c[i][j - 1]){
            --i;
        }
        else {
            --j;
        }
    }
    
    printf("%d\n", c[m][n]);
    FOR(i, 1, c[m][n]){
        printf("%d ", sir[i]);
    }
}
 
 
int main(int argc, char** argv) {
    freopen("cmlsc.in", "r", stdin);
    freopen("cmlsc.out", "w", stdout);
    
     
    int m, n;
    int a[NMax], b[NMax];
    
    scanf("%d %d", &m, &n);
    int i;
    FOR(i, 1, m){
        scanf("%d", a + i);
    }
    FOR(i, 1, n){
        scanf("%d", b + i);
    }
    
    lcs(a,b, m, n);
   
    return 0;
}

