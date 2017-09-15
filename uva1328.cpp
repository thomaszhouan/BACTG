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
  void solve(void) {
    for (int i=1; i<=len; ++i) if (f[i] && i%(i-f[i])==0)
      printf("%d %d\n", i, i/(i-f[i]));
  }
};
KMP kmp;

int main(void) {
  int n, kase = 0;
  while (scanf("%d", &n), n) {
    printf("Test case #%d\n", ++kase);
    scanf("%s", kmp.P);
    kmp.compile(); kmp.solve();
    puts("");
  }
  return 0;
}
