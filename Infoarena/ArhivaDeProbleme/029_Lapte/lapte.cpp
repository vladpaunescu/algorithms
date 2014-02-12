/* 
 * File:   lapte.cpp
 * Author: Vlad
 *
 * Created on February 12, 2014, 10:51 PM
 */

#include <cstdio>


using namespace std;

typedef struct _Bautor {
    int a, b;
} Bautor;

const int INF = 99999;
int n, l, din[102][102], baut[102][102];
Bautor v[102], q[102];

void init(int t) {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= l; j++) {
            din[i][j] = 0;
            baut[i][j] = 0;
        }
    }

    for (int i = 0; i <= l; i++) {
        if (i * v[1].a > t) {
            din[1][i] = -INF;
            continue;
        }
        din[1][i] = (t - i * v[1].a) / v[1].b;
        baut[1][i] = i;
    }
}

// sol[n][l] cati litri de lapte 2 se pot bea optim folosind n oameni,
// consumand l litri de lapte 1, in timpul dat t.
// avem solutie daca si nr de litri de lapte 2 >= l, adica sol[n][l] >= l

bool isValid(int t) {
    init(t);

    for (int i = 2; i <= n; i++) {
        // k is milk 1 volume
        int maxK = t / v[i].a;
        for (int j = 0; j <= l; j++) {
            din[i][j] = -INF;
            for (int milk1Vol = 0; milk1Vol <= maxK && j - milk1Vol >= 0; milk1Vol++) {
                int milk2Vol = (t - milk1Vol * v[i].a) / v[i].b;
                if (din[i][j] < din[i - 1][j - milk1Vol] + milk2Vol) {
                    din[i][j] = din[i - 1][j - milk1Vol] + milk2Vol;
                    baut[i][j] = milk1Vol;
                }
            }
        }
    }
    return din[n][l] >= l;
}

int binarySearch() {
    int st = 1, dr = 100;
    int optimumTime = -1;
    while (st <= dr) {
        int mid = st + (dr - st) / 2;
        if (isValid(mid)) {
            optimumTime = mid;
            dr = mid - 1;
        } else st = mid + 1;
    }
    return optimumTime;
}

int main(int argc, char** argv) {
    freopen("lapte.in", "r", stdin);
    freopen("lapte.out", "w", stdout);
    scanf("%d %d", &n, &l);
    for (int i = 1; i <= n; i++) scanf("%d %d", &v[i].a, &v[i].b);

    int optimumTime = binarySearch();
    printf("%d\n", optimumTime);
    isValid(optimumTime);
    for (int i = n, j = l; i; i--) {
        q[i].a = baut[i][j];
        q[i].b = (optimumTime - q[i].a * v[i].a) / v[i].b;
        j -= baut[i][j];
    }
    for (int i = 1; i <= n; ++i) {
        printf("%d %d\n", q[i].a, q[i].b);
    }


    return 0;
}

