/* 
 * File:   sobo.cpp
 * Author: Vlad
 *
 * Created on February 8, 2014, 5:48 PM
 */

#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>

using namespace std;

int n, l, cost[1002];
int harti[16];
vector<int> ratsOne[1002];
vector<int> ratsZero[10002];
int a[35000];

/*
 * Problema se rezolva prin programare dinamica. 
 * Se retine in Ai = costul minim in cazul cel mai defavorabil pentru
 * a recunoaste sobolanul inteligent din multimea de sobolani
 * cu numerele de ordine pozitiile bitilor de 1 in reprezentarea
 * binara a lui i. Astfel, A va avea valori pentru i intre 0 si 2N-1.
 * Raspunsul va fi A2N-1. Este evident ca graful format de aceste stari este
 * aciclic deoarece fiecare raspuns imparte o multime in doua multimi mai mici.
 * Astfel pentru a calcula un Ai vom lua fiecare raspuns care imparte in doua
 * multimi nevide multimea curenta, vom vedea in care multime costul este
 * mai mare (cazul cel mai defavorabil) , adaugam pretul raspunsului si
 * actualizam in Ai daca valoarea aceasta este mai mica decat cea curenta 
 * (sa nu uitam ca vrem cost minim in cazul cel mai defavorabil). 
 * Cea mai simpla metoda de a implementa acest mecanism este cu memoizare.
 * Complexitatea finala O(2N * L * N). Se poate optimiza la O(2N * L) 
 * folosind operatii pe biti.
 */

int compute(int idx, int count, int taken) {
    if (count == 1) {
        a[idx] = 0;
        return a[idx];
    }
    if (a[idx] != -1) {
        return a[idx];
    }

    int leftIdx, rightIdx, leftCount, rightCount;
    int minSum = INT_MAX;
    for (int i = 1; i <= l; i++) {

        if (!(taken & 1 << (i - 1))) {
            taken = taken | 1 << (i - 1);
            if (taken != (1 << l) - 1) {
                leftIdx = 0, rightIdx = 0, leftCount = 0, rightCount = 0;
                for (int el : ratsOne[i]) {
                    if (1 << (el - 1) & idx) {
                        leftIdx |= 1 << (el - 1);
                        leftCount++;
                    }
                }

                for (int el : ratsZero[i]) {
                    if (1 << (el - 1) & idx) {
                        rightIdx |= 1 << (el - 1);
                        rightCount++;
                    }
                }
                int r1 = -10000;
                if (leftIdx)
                    r1 = compute(leftIdx, leftCount, taken);
                if (rightIdx) {
                    int r2 = compute(rightIdx, rightCount, taken);
                    if (r2 > r1) {
                        r1 = r2;
                    }
                }

                r1 += cost[i];
                if (r1 < minSum) {
                    minSum = r1;
                    a[idx] = minSum;
                }


            } else if (minSum > cost[i]) {
                minSum = cost[i];
                a[idx] = minSum;
                return minSum;
            }

            taken = taken & (~(1 << (i - 1)));
        }
    }
    return a[idx];
}

void convert(char *bits, int idx) {
    int i = 0;
    int pow = 1 << (l - 1);
    while (bits[i]) {
        if (bits[i] == '1') {
            harti[idx] += pow;
            ratsOne[i + 1].push_back(idx);
        } else {
            ratsZero[i + 1].push_back(idx);
        }
        pow >>= 1;
        i++;
    }
}

int main(int argc, char** argv) {
    freopen("sobo.in", "r", stdin);
    freopen("sobo.out", "w", stdout);
    scanf("%d %d\n\r", &n, &l);
    char bits[l + 3];
    for (int i = 1; i <= n; i++) {
        gets(bits);
        convert(bits, i);
    }

    for (int i = 1; i <= l; i++) {
        scanf("%d", cost + i);
    }

    //    for (int i = 1; i <= n; i++) {
    //        printf("%d\n", harti[i]);
    //    }
    //
    //    for (int i = 1; i <= n; i++) {
    //        for (vector<int>::iterator it = ratsOne[i].begin(); it != ratsOne[i].end();
    //                ++it) {
    //            printf("%d ", *it);
    //        }
    //        printf("\n");
    //    }
    memset(a, -1, sizeof (a));
    for(int i = 1; i <= (1 << n) - 1; i++){
         compute(i, n, 0);
    }
    printf("%d\n", a[(1 << n) - 1]);

    return 0;
}

