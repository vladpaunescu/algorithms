#include <cstdio>

using namespace std;

const int BASE = 10000;

void Atrib0(int H[]) {
    H[0] = 0;
}

void AtribValue(int H[], unsigned long X) {
    H[0] = 0;
    while (X) {
        ++H[0];
        H[H[0]] = X % BASE;
        X /= BASE;
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
    T = H[1] / BASE;
    H[1] = H[1] % BASE;

    i = 1;
    while (T) /* Cat timp exista transport */ {
        H[++i] = T % BASE;
        T /= BASE;
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
        T = A[i] / BASE;
        A[i] %= BASE;
    }
    if (T) A[++A[0]] = T;
}

void Subtract(int A[], int B[])
/* A <- A-B */ {
    int i, T = 0;

    for (i = B[0] + 1; i <= A[0];) B[i++] = 0;
    for (i = 1; i <= A[0]; i++)
        A[i] += (T = (A[i] -= B[i] + T) < 0) ? BASE : 0;
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
        T = H[i] / BASE;
        H[i] = H[i] % BASE;
    }
    while (T) /* Cat timp exista transport */ {
        H[++H[0]] = T % BASE;
        T /= BASE;
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
        T = (C[i] += T) / BASE;
        C[i] %= BASE;
    }
    if (T) C[++C[0]] = T;
}

unsigned long Divide(int A[], unsigned long X)
/* A <- A/X si intoarce A%X */ {
    int i;
    unsigned long R = 0;

    for (i = A[0]; i; i--) {
        A[i] = (R = BASE * R + A[i]) / X;
        R %= X;
    }
    while (!A[A[0]] && A[0] > 1) A[0]--;
    return R;
}

int n, k, s[202][202][200];

int main(int argc, char** argv) {
    freopen("perm.in", "r", stdin);
    freopen("perm.out", "w", stdout);
    scanf("%d %d", &n, &k);

    /*
     * The Stirling numbers s(n,k) satisfy the recurrence relation:
     * s(n,k) = s(n-1, k-1) + (n-1) * s(n-1, k) n >= 1
     * s(0,0) = 1 s(n,0) = s(0,n) = 0, n > 0
     * 
     */

    // s[0][0] = 1;
    AtribValue(s[0][0], 1);
    // s[n][0] = s[0][n] = 0;
    int temp[200];
    Atrib0(s[n][0]); Atrib0(s[0][n]);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            AtribHuge(temp, s[i-1][j]);
            Mult(temp, i - 1);
            AddHuge(s[i][j], s[i-1][j - 1]);
            AddHuge(s[i][j], temp);
            // s[i][j] = s[i - 1][j - 1] + (i - 1) * s[i - 1][j];
        }
    }
    printf("%d", s[n][k][s[n][k][0]]);
    for(int i = s[n][k][0] - 1; i; i--) printf("%04d", s[n][k][i]);

    return 0;
}

