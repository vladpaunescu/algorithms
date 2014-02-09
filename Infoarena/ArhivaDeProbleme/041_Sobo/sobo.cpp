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
// ce harti de sobolani raman in calcul daca raspundem cu 1 la bitul i
int ratsOne[1002];
int ratsZero[1002];
int a[35000];
int total;

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

inline bool powerOfTwo(int x) {
    return !(x == 0) && !(x & (x - 1));
}

int compute(int idx, int taken) {
    if (a[idx] != -1) {
        return a[idx];
    }

    int leftIdx, rightIdx;
    int minSum = INT_MAX;
    for (int i = 1; i <= l; i++) {
        int s = 1 << (i - 1);
        if (!(taken & s)) {
            taken |= s;
            int result = cost[i];
            if (taken != total) {
                leftIdx = ratsOne[i] & idx;
                rightIdx = ratsZero[i] & idx;

                int r1, r2;
                if (leftIdx && !powerOfTwo(leftIdx)) {
                    if (a[leftIdx] != -1) {
                        r1 = a[leftIdx];
                    } else {
                        r1 = compute(leftIdx, taken);
                    }
                } else {
                    a[leftIdx] = 0;
                    r1 = 0;
                }

                if (rightIdx && !powerOfTwo(rightIdx)) {
                    if (a[rightIdx] != -1) {
                        r2 = a[rightIdx];
                    } else {
                        r2 = compute(rightIdx, taken);
                    }
                } else {
                    a[rightIdx] = 0;
                    r2 = 0;
                }
                if (r2 > r1) r1 = r2;

                result += r1;
            }
            if (minSum > result) {
                minSum = result;
                a[idx] = minSum;
            }
            taken &= (~(1 << (i - 1)));
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
            ratsOne[i + 1] |= (1 << (idx - 1));
        } else {
            ratsZero[i + 1] |= (1 << (idx - 1));
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

    memset(a, -1, sizeof (a));
    total = (1 << l) - 1;
    for (int i = 1; i <= (1 << n) - 1; i++) {
        compute(i, 0);
    }
    printf("%d\n", a[(1 << n) - 1]);

    return 0;
}

