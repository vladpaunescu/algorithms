/* 
 * File:   datorii.cpp
 * Author: Vlad
 *
 * Created on February 8, 2014, 4:20 PM
 */

#include <cstdio>

using namespace std;

int n, m, tree[15002];

void update(int idx, int val){
    while (idx <= n){
        tree[idx] += val;
        idx += (idx & -idx);
    }
}

int query(int idx){
    int sum = 0;
    while(idx){
        sum +=tree[idx];
        idx -= (idx & -idx);
    }
    return sum;
}

int main(int argc, char** argv) {
    freopen("datorii.in", "r", stdin);
    freopen("datorii.out", "w", stdout);
    
    scanf("%d %d", &n, &m);
    for(int i = 1, val; i <= n; i++){
        scanf("%d", &val);
        update(i, val);
    }
    
    int c, p, q;
    for(int i = 1; i <= m; i++){
        scanf("%d %d %d", &c ,&p, &q);
        if (c == 0){
            update(p, -q);
        } else {
            printf("%d\n", query(q) - query(p-1));
        }
    }
    
    return 0;
}

