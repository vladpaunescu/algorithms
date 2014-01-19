#include <cstdio>
#define NMAX 101



int main(int argc, char** argv) {
    freopen("royfloyd.in", "r", stdin);
    freopen("royfloyd.out", "w", stdout);
    
    int n;
    scanf("%d", &n);
    int i, j, k;
    int a[NMAX][NMAX];  
    // read adj matrix
    for(i = 1; i <= n; ++i){
        for(j = 1; j <= n; ++j){
            scanf("%d", &a[i][j]);
        }
    }
    
    // floyd warshall
    for(k = 1; k <= n; ++k){
        for(i = 1; i <= n ; ++i){
            for(j = 1; j <= n; ++j){
                if(a[i][k] && a[k][j] &&
                        (a[i][j] > a[i][k] + a[k][j] || !a[i][j]) &&
                        i != j){
                    a[i][j] = a[i][k] + a[k][j];
                 }
            }
        }
    }

    // print
    for(i = 1; i <= n; ++i){
        for(j = 1; j <= n; ++j){
            printf("%d ", a[i][j]);
        }
        putchar('\n');
    }
    return 0;
}

