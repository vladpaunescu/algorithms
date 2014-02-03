/* 
 * File:   tort.cpp
 * Author: Vlad
 *
 * Created on February 2, 2014, 8:46 PM
 */

#include <fstream>

using namespace std;

unsigned long a, b;

int result1[15000], result2[15000], result3[15000],
        result4[15000], result5[15000],
m[100], n[100], m1[100], n1[100], m2[100], n2[100];

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

int main(int argc, char** argv) {
    ifstream f("tort.in");
    ofstream g("tort.out");
    f >> a >> b;

    //    result = (a + 1) * (a + 2) / 2 * (b + 1);
    //    result += (b + 1) * (b + 2) / 2 * (a + 1);
    //
    //    result -= (a + 1) * (b + 1);

    AtribValue(m, a);
    AtribValue(n, b);
    AtribValue(m1, a + 1);
    AtribValue(m2, a + 2);
    AtribValue(n1, b + 1);
    AtribValue(n2, b + 2);

    MultHuge(m1, m2, result1);
    Divide(result1, 2);
    MultHuge(result1, n1, result3);

    MultHuge(n1, n2, result2);
    Divide(result2, 2);
    MultHuge(result2, m1, result4);

    AddHuge(result3, result4);
    MultHuge(m1, n1, result5);

    Subtract(result3, result5);

    for (int i = result3[0]; i; i--) g << result3[i];
    g << '\n'; g.close();

    return 0;
}

