#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6+10;
int M, N, S[MAXN];
struct KMP {
  int P[MAXN];
  int f[MAXN];

  void compile(void) {
    f[0] = f[1] = 0;
    for (int i=1; i<M; ++i) {
      int q = f[i];
      while (q && P[q]!=P[i]) q = f[q];
      f[i+1] = P[q]==P[i]?q+1:0;
    }
  }
  int match(int *S) {
    int q = 0;
    for (int i=0; i<N; ++i) {
      while (q && P[q]!=S[i]) q = f[q];
      if (P[q]==S[i]) ++q;
      if (q==M) return i-M+2;
    }
    return -1;
  }
};
KMP kmp;

int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    scanf("%d%d", &N, &M);
    for (int i=0; i<N; ++i) scanf("%d", S+i);
    for (int i=0; i<M; ++i) scanf("%d", kmp.P+i);
    kmp.compile();
    printf("%d\n", kmp.match(S));
  }
  return 0;
}
