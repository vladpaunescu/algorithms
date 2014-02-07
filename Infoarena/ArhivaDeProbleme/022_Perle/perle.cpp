/* 
 * File:   perle.cpp
 * Author: Vlad
 *
 * Created on February 7, 2014, 12:03 PM
 */

#include <cstdio>

using namespace std;


int n;
const int MAX_L = 10004;
int a[MAX_L];

int B(int pos);
int C(int pos);

//     A -> 1 | 2 | 3
//     B -> 2B | 1A3AC
//     C -> 2 | 3BC | 12A
//
//     21132123,  B -> 2B -> 21A3AC -> 21A3A12A -> 21132123.

// A generates every combination 1,2,3

//     B -> 2B | 1A3AC
int B(int pos){
    if (pos > a[0]){
        // sirul are lungime mai mare
        return 0;
    }
    if (a[pos] == 2){
        // cazul 2B
        return B(pos + 1);
    }
    if (a[pos] == 1 && a[pos + 2] == 3){
        // sirul are 1A3AC
        return C(pos + 4);
    }
}

//     C -> 2 | 3BC | 12A
int C(int pos){
    if (pos > a[0]){
        // sirul are lungime mai mare
        return 0;
    }
    if (a[pos] == 2){
        return pos;
    }
    if(a[pos] == 3){
        // expand B
        int len = B(pos + 1);
        // expand C
        if (len) return C(len + 1);
    }
    else if (a[pos] == 1 && a[pos + 1] == 2){
        // 12A
        return pos + 2;
    }
    return 0;
}

int main(int argc, char** argv) {
    freopen("perle.in", "r", stdin);
    freopen("perle.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[0]);
        for (int j = 1; j <= a[0]; ++j) {
            scanf("%d", &a[j]);
        }
        if (a[0] == 1){
            // se poate forma din A
            printf("1\n");
        }
        else if (B(1) == a[0] || C(1) == a[0]){
            printf("1\n");
        } else printf("0\n");

    }

    return 0;
}

