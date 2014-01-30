/* 
 * File:   munte.cpp
 * Author: Vlad
 *
 * Created on January 30, 2014, 10:59 PM
 */

#include <cstdio>
#include <algorithm>

using namespace std;

/*
 * 
 */
int N, D, K;
int h[51];

/*
 Te afli intr-un anumit punct, la o anumita distanta fata de 
 * origine si la o anumita inaltime. 
 * Din acel punct te poti duce in 3 directii inaintand in sus, 
 * orizontal sau in jos. Cand cauti relatia de recurenta te 
 * gandesti din ce puncte ajungi in punctu curent si ai tot 3 posibilitati. 
 * Iei doua cazuri: dc inaltimea la care esti in momentul 
 * actual este egala cu cea a punctului special in care trebuie ajungi
 * sau nu si vezi ce diferente sunt intre cele doua cazuti.
 * Te mai gandesti cum rezolvi problema daca ai atins sau nu maximul. 
 *  
 * A(i,j,k,t) = numarul de posibilitati sa ajung la distanta i,
 * la inaltimea j, trecand prin primele k puncte speciale;
 * t = 1 sau 0 daca am atins pana aici intaltimea N sau nu.
 * Solutia se va afla in A(D, 1, K, 1).
 */

long a[100][51][51][2];

void solve() {
    int currentInterestP = 1;
    if (K == 0) {
        //dc nu am puncte speciale
        if (N == 1) a[1][1][0][1] = 1; // inaltimea muntelui e chiar 1, marchez ca am ajuns
        else a[1][1][0][0] = 1; // inaltimea muntelui e mai mare ca 1 nu am ajuns la maxim
    } else if (h[currentInterestP] == 1) {
        //dc am ajuns la primul punct special
        if (N == 1) a[1][1][1][1] = 1; // inaltimea muntelui e chiar 1, marchez ca am ajuns
        else a[1][1][1][0] = 1; // marchez ca am ajuns la primul punct special
        currentInterestP++; // urmatorul punct special e 2
    } else {
        // in orice alta situatie exista un singur mod de a ajunge la 
        // distanta 1 si inaltime 1
        a[1][1][0][0] = 1; 
    }
    for (int i = 2; i <= D; ++i) {
        for (int j = 1; j <= min(i, D-i); ++j) {
            printf("j=%d\n", j);
            bool found = false;
            for (int k = 0; k <= currentInterestP; ++k) {
                for (int t = 0; t < 2; ++t) {
                    if (j == h[currentInterestP]) {
                        // sunt la intaltimea urmatorului punct special
                        found = true;
                        
                        // pot veni din stanga lateral
                        a[i][j][k][t] = a[i - 1][j][k - 1][0] +
                                a[i - 1][j][k - 1][1];
                        if (j < N) {
                            // pot veni de sus
                            a[i][j][k][t] += (a[i - 1][j + 1][k - 1][0] +
                                    a[i - 1][j + 1][k - 1][1]);
                        }
                        if (j >= 2) {
                            // pot veni de jos
                            a[i][j][k][t] += (a[i - 1][j - 1][k - 1][0] +
                                    a[i - 1][j - 1][k - 1][1]);
                          
                        }
                    } else {
                        // nu sunt la o inaltime speciala
                        
                        // pot veni din stanga
                        a[i][j][k][t] = (a[i - 1][j][k][0] +
                                a[i - 1][j][k][1]);
                        if (j < N) {
                            // pot veni de sus
                            a[i][j][k][t] += (a[i - 1][j + 1][k][0] +
                                    a[i - 1][j + 1][k][1]);
                        }
                        if (j >= 2) {
                            // pot veni de jos
                            a[i][j][k][t] += (a[i - 1][j - 1][k][0] +
                                    a[i - 1][j - 1][k][1]);
                        }
                    }
                }
            }
            if (found) currentInterestP++;
            printf("%d\n", currentInterestP);
        }

    }

}

int main(int argc, char** argv) {
    freopen("munte.in", "r", stdin);
   // freopen("munte.out", "w", stdout);

    scanf("%d %d %d", &N, &D, &K);
    for (int i = 1; i <= K; ++i) {
        scanf("%d", &h[i]);
    }
    solve();
    printf("%ld\n\n", a[D][1][K][1]);
    for (int i = 1; i <= D; ++i) {
        for (int j = 1; j <= N; ++j) {
            for (int k = 0; k <= K; ++k)
                printf("%d ", a[i][j][k][1]);
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}

