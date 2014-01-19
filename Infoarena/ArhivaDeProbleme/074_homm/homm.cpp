/* 
 * File:   luna.cpp
 * Author: Vlad
 *
 * Created on January 17, 2014, 11:54 PM
 */

#include <cstdio>

using namespace std;
int M, N, K, totalWays;
int map[101][101], ways[20][102][102];
int l1 , c1, l2,c2;

void solve(){
    ways[0][l1][c1] = 1;
    for(int step = 1; step <= K; ++step){
        for(int i = 1; i <= M; ++i){
            for(int j = 1; j <= N; j++){
                if(map[i][j] == 0){
                        ways[step][i][j] = ways[step-1][i-1][j]+
                                ways[step-1][i][j-1]+
                                ways[step-1][i+1][j]+
                                ways[step-1][i][j+1];
                }
            }
        }
    }
    totalWays = 0;
    for(int step = 0; step <= K; ++step){
        totalWays += ways[step][l2][c2];
    }  
    
}


int main(int argc, char** argv) {
    freopen("homm.in", "r", stdin);
    freopen("homm.out", "w", stdout);
    scanf("%d %d %d", &M, &N, &K);
    for(int i = 1; i <= M; i++){
        for(int j = 1; j <= N; j++){
            scanf("%d", &map[i][j]);
        }
    }
    scanf("%d %d %d %d", &l1, &c1, &l2, &c2);
    solve();
    printf("%d\n", totalWays);  

    return 0;
}

