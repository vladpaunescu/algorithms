// Andrei Sfrent

#include <cstdio>
#include <cassert>
#include <cstring>
 
using namespace std;
 
struct Big {
  int d[100];
 
  Big(int x) {
    init();
    while(x) {
      d[++d[0]] = x % 10;
      x /= 10;
    }
  }
 
  Big() {
    d[0] = -1;
  }
 
  Big(const Big& other) {
    memcpy(d, other.d, 100 * sizeof(int));
  }
 
  Big& operator =(const Big& other) {
    memcpy(d, other.d, 100 * sizeof(int));
    return *this;
  }
 
  void init() {
    memset(d, 0, 100 * sizeof(int));
  }
 
  bool isUndefined() const {
    return d[0] == -1;
  }
 
  void print() {
    if(d[0] == 0) {
      printf("0");
      return;
    }
 
    for(int i = d[0]; i >= 1; --i) {
      printf("%d", d[i]);
    }
  }
 
  void add(const Big& other) {
    assert(!isUndefined() && !other.isUndefined());
    int i, t = 0;
    for (i = 1; i <= d[0] || i <= other.d[0] || t; i++, t /= 10)
      d[i] = (t += d[i] + other.d[i]) % 10;
    d[0] = i - 1;
  }
 
  void mul(int other) {
    assert(!isUndefined());
    if(other == 0) {
      init();
      return;
    }
 
    int i, t = 0;
    for (i = 1; i <= d[0] || t; i++, t /= 10)
      d[i] = (t += d[i] * other) % 10;
    d[0] = i - 1;
  }
};
 
Big operator +(const Big& a, const Big& b) {
  Big result(0);
  result.add(a);
  result.add(b);
  return result;
}
 
Big operator *(const Big& a, int b) {
  Big result(0);
  result.add(a);
  result.mul(b);
  return result;
}
 
Big operator *(int a, const Big& b) {
  return b * a;
}
 
// typedef long long ll;
typedef Big ll;
 
int L, P, Q, B;
ll mem_fP[21][21];
ll mem_fQ[21][21][2];
 
ll fP(int N, int S) {
  if(S > P) return Big(0);
  if(N == 0) return Big(1);
  if(mem_fP[N][S].isUndefined()) {
    ll next_zero = fP(N - 1, S + 1);
    ll next_nonzero = fP(N - 1, 0);
    mem_fP[N][S] = (B - 1) * next_nonzero + next_zero;
  }
  return mem_fP[N][S];
}
 
ll fQ(int N, int S, int valid) {
  if(S >= Q) valid = 1;
  if(N == 0) return Big(valid);
  if(mem_fQ[N][S][valid].isUndefined()) {
    ll next_zero = fQ(N - 1, S + 1, valid);
    ll next_nonzero = fQ(N - 1, 0, valid);
    mem_fQ[N][S][valid] = (B - 1) * next_nonzero + next_zero;
  }
  return mem_fQ[N][S][valid];
}
 
int main(int argc, char *argv[]) {
  freopen("zero.in", "r", stdin);
  freopen("zero.out", "w", stdout);
 
  scanf("%d%d%d%d", &L, &B, &P, &Q);
  ((B - 1) * fP(L - 1, 0)).print();
  printf("\n");
  ((B - 1) * fQ(L - 1, 0, 0)).print();
  printf("\n");
 
  return 0;
}