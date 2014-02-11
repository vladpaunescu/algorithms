/* 
 * File:   zero.cpp
 * Author: vpaunescu
 *
 * Created on February 11, 2014, 2:20 PM
 */

#include <cstdio>

using namespace std;
int l, b, p, q;

/*
 * am dp[i][j]-cate numere de i cifre au ultimele j cifre 0. 
 * dp[0]=s*(B-1) unde s e suma de pe linia dp[i-1] pentru ca putem adauga 
 * o cira sa sfarsitul oricarui sir de lungime i-1. 
 * dp[j]=dp[i-1][j-1] pentru ca adaugam un 0 la sfarsitul rocarui sir ce are
 *  lungime i-1 si se tarmina in j-1 .
 */


void Atrib0(int H[]) {
    H[0] = 0;
}

void AtribValue(int H[], unsigned long X) {
    H[0] = 0;
    while (X) {
        ++H[0];
        H[H[0]] = X % 10;
        X /= 10;
    }
}

void AtribHuge(int H[], int X[]) {
    int i;
    for (i = 0; i <= X[0]; ++i) {
        H[i] = X[i];
    }
}

int Sgn(int H1[], int H2[]) {
    // Elimina zero-urile semnificative, daca exista.
    while (H1[0] && !H1[H1[0]]) H1[0]--;
    while (H2[0] && !H2[H2[0]]) H2[0]--;

    if (H1[0] < H2[0]) {
        return -1;
    } else if (H1[0] > H2[0]) {
        return +1;
    }

    for (int i = H1[0]; i > 0; --i) {
        if (H1[i] < H2[i]) {
            return -1;
        } else if (H1[i] > H2[i]) {
            return +1;
        }
    }
    return 0;
}

void Add(int H[], unsigned long X)
/* H <- H + X */ {
    int i;
    unsigned long T = 0;

    H[1] = H[1] + X;
    T = H[1] / 10;
    H[1] = H[1] % 10;

    i = 1;
    while (T) /* Cat timp exista transport */ {
        H[++i] = T % 10;
        T /= 10;
    }
}

void AddHuge(int A[], int B[])
/* A <- A+B */ {
    int i, T = 0;

    if (B[0] > A[0]) {
        for (i = A[0] + 1; i <= B[0];) A[i++] = 0;
        A[0] = B[0];
    } else for (i = B[0] + 1; i <= A[0];) B[i++] = 0;
    for (i = 1; i <= A[0]; i++) {
        A[i] += B[i] + T;
        T = A[i] / 10;
        A[i] %= 10;
    }
    if (T) A[++A[0]] = T;
}

void Subtract(int A[], int B[])
/* A <- A-B */ {
    int i, T = 0;

    for (i = B[0] + 1; i <= A[0];) B[i++] = 0;
    for (i = 1; i <= A[0]; i++)
        A[i] += (T = (A[i] -= B[i] + T) < 0) ? 10 : 0;
    /* Adica A[i]=A[i]-(B[i]+T);
       if (A[i]<0) T=1; else T=0;
       if (T) A[i]+=10; */
    while (!A[A[0]]) A[0]--;
}

void Mult(int H[], unsigned long X)
/* H <- H*X */ {
    int i;
    unsigned long T = 0;

    for (i = 1; i <= H[0]; i++) {
        H[i] = H[i] * X + T;
        T = H[i] / 10;
        H[i] = H[i] % 10;
    }
    while (T) /* Cat timp exista transport */ {
        H[++H[0]] = T % 10;
        T /= 10;
    }
}

void MultHuge(int A[], int B[], int C[])
/* C <- A x B */ {
    int i, j, T = 0;

    C[0] = A[0] + B[0] - 1;
    for (i = 1; i <= A[0] + B[0];) C[i++] = 0;
    for (i = 1; i <= A[0]; i++)
        for (j = 1; j <= B[0]; j++)
            C[i + j - 1] += A[i] * B[j];
    for (i = 1; i <= C[0]; i++) {
        T = (C[i] += T) / 10;
        C[i] %= 10;
    }
    if (T) C[++C[0]] = T;
}

unsigned long Divide(int A[], unsigned long X)
/* A <- A/X si intoarce A%X */ {
    int i;
    unsigned long R = 0;

    for (i = A[0]; i; i--) {
        A[i] = (R = 10 * R + A[i]) / X;
        R %= X;
    }
    while (!A[A[0]] && A[0] > 1) A[0]--;
    return R;
}

int dp[21][21][200];

int main(int argc, char** argv) {

    freopen("zero.in", "r", stdin);
    freopen("zero.out", "w", stdout);
    scanf("%d %d %d %d", &l, &b, &p, &q);

    AtribValue(dp[1][0], b - 1);
    int sum[200];
    AtribValue(sum, b - 1);

    for (int i = 2; i <= l; i++) {
        Mult(sum, b - 1);
        AtribHuge(dp[i][0], sum);
        // dp[i][0] = sum * (b - 1);
        AtribHuge(sum, dp[i][0]);
        //sum = dp[i][0];
        for (int j = 1; j <= p; j++) {
            AtribHuge(dp[i][j], dp[i - 1][j - 1]);
            //dp[i][j] = dp[i - 1][j - 1];
            AddHuge(sum, dp[i][j]);
            //sum += dp[i][j];
        }
    }
    //    for (int i = 1; i <= l; i++) {
    //        for (int j = 0; j < i; j++) {
    //            printf("%d ", dp[i][j]);
    //        }
    //        printf("\n");
    //    }

    int rp[200], rq[200];
    Atrib0(rp);
    Atrib0(rq);

    for (int j = 0; j <= p; j++) {
        AddHuge(rp, dp[l][j]);
    }

    AtribValue(dp[1][0], b - 1);
    AtribValue(sum, b - 1);
    for (int i = 2; i <= l; i++) {
        Mult(sum, b - 1);
        AtribHuge(dp[i][0], sum);
        // dp[i][0] = sum * (b - 1);
        AtribHuge(sum, dp[i][0]);
        //sum = dp[i][0];
        for (int j = 1; j <= q - 1; j++) {
            AtribHuge(dp[i][j], dp[i - 1][j - 1]);
            //dp[i][j] = dp[i - 1][j - 1];
            AddHuge(sum, dp[i][j]);
            //sum += dp[i][j];
        }
    }

    for (int j = 0; j <= q - 1; j++) {
        AddHuge(rq, dp[l][j]);
    }

    int totalCount[200];
    AtribValue(totalCount, b - 1);
    for (int i = 2; i <= l; i++) {
        Mult(totalCount, b);
        //totalCount *= b;
    }

    Subtract(totalCount, rq);

    for (int i = rp[0]; i; i--) printf("%d", rp[i]);
    printf("\n");
    for (int i = totalCount[0]; i; i--) printf("%d", totalCount[i]);
    printf("\n");

    return 0;
}

