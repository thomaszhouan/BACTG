#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6+10;
struct KMP {
  char P[MAXN];
  int f[MAXN], len;

  void compile(void) {
    f[0] = f[1] = 0; len = 1;
    for (int i=1; P[i]; ++i) {
      int q = f[i]; ++len;
      while (q && P[q]!=P[i]) q = f[q];
      f[i+1] = P[q]==P[i]?q+1:0;
    }
  }
  int match(char *S) {
    int q = 0, match_cnt = 0;
    for (int i=0; S[i]; ++i) {
      while (q && P[q]!=S[i]) q = f[q];
      if (P[q]==S[i]) ++q;
      if (q==len) ++match_cnt, q = f[q];
    }
    return match_cnt;
  }
};
KMP kmp;
char S[MAXN];

int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    scanf("%s", kmp.P); kmp.compile();
    scanf("%s", S); printf("%d\n", kmp.match(S));
  }
  return 0;
}
