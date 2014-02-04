/* 
 * File:   aparitii.cpp
 * Author: vpaunescu
 *
 * Created on February 4, 2014, 12:54 PM
 */

#include <cstdio>
#include <assert.h>

using namespace std;

int n, k, a;
int counts[20][9];

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
        int c = 0;
        for (int j = 0; j < 10; j++) {
            if (counts[i][j] % k) {
                c++;
                printf("%d", j);
            }
        }
            assert(c < 2);
    }

    printf("\n");

    return 0;
}

