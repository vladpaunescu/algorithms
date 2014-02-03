#include <fstream>

using namespace std;

const int BASE = 100;

void mul(int A[], int B) {
    int i, t = 0;
    for (i = 1; i <= A[0] || t; i++, t /= BASE)
        A[i] = (t += A[i] * B) % BASE;
    A[0] = i - 1;
}

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

void Add(int A[], int B[])
/* A <- A+B */
{ int i,T=0;
 
  if (B[0]>A[0])
    { for (i=A[0]+1;i<=B[0];) A[i++]=0;
      A[0]=B[0];
    }
    else for (i=B[0]+1;i<=A[0];) B[i++]=0;
  for (i=1;i<=A[0];i++)
    { A[i]+=B[i]+T;
      T=A[i]/10;
      A[i]%=10;
    }
  if (T) A[++A[0]]=T;
}

void Subtract(int A[], int B[])
/* A <- A-B */
{ int i, T=0;
 
  for (i=B[0]+1;i<=A[0];) B[i++]=0;
  for (i=1;i<=A[0];i++)
    A[i]+= (T=(A[i]-=B[i]+T)<0) ? 10 : 0;
    /* Adica A[i]=A[i]-(B[i]+T);
       if (A[i]<0) T=1; else T=0;
       if (T) A[i]+=10; */
  while (!A[A[0]]) A[0]--;
}

void Mult(int H[], unsigned long X)
/* H <- H*X */
{ int i;
  unsigned long T=0;
 
  for (i=1;i<=H[0];i++)
    { H[i]=H[i]*X+T;
      T=H[i]/10;
      H[i]=H[i]%10;
    }
  while (T) /* Cat timp exista transport */
    { H[++H[0]]=T%10;
      T/=10;
    }
}

void MultHuge(int A[], int B[], int C[])
/* C <- A x B */
{ int i,j,T=0;
 
  C[0]=A[0]+B[0]-1;
  for (i=1;i<=A[0]+B[0];) C[i++]=0;
  for (i=1;i<=A[0];i++)
    for (j=1;j<=B[0];j++)
      C[i+j-1]+=A[i]*B[j];
  for (i=1;i<=C[0];i++)
    { T=(C[i]+=T)/10;
      C[i]%=10;
    }
  if (T) C[++C[0]]=T;
}

int sol[15000];

int main() {
    sol[0] = sol[1] = 1;

    for (int i = 1; i < 100; i++) {
        mul(sol, 2);
        printf("%d", sol[sol[0]]);
        for (int j = sol[0] - 1; j; j--) printf("%02d", sol[j]);
        printf("\n");
    }
    return 0;
}