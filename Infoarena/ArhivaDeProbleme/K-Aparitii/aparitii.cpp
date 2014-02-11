/* 
 * File:   aparitii.cpp
 * Author: vpaunescu
 *
 * Created on February 4, 2014, 12:54 PM
 */

#include <cstdio>

using namespace std;

int n, k, a;
int counts[20][10];

int main(int argc, char** argv) {
    freopen("aparitii.in", "r", stdin);
    freopen("aparitii.out", "w", stdout);

    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a);
        int j = 1;
        while (a) {
            int c = a % 10;
            a /= 10;
            counts[j++][c]++;
        }
    }

    for (int i = 19; i; i--) {
        for (int j = 0; j < 10; j++) {
            if (counts[i][j] % k) {
                printf("%d", j);
            }
        }
    }

    printf("\n");

    return 0;
}

