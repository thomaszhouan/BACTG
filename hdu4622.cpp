#include <bits/stdc++.h>
using namespace std;

const int MAXLEN = 2005;
const int SIGMA = 26;
char S[MAXLEN];
int ans[MAXLEN][MAXLEN];
struct SAM {
  int len[MAXLEN<<1], fa[MAXLEN<<1];
  int next[MAXLEN<<1][SIGMA];
  int sz, last, tot;
  void init() { // start from 1
    sz = last = 1; tot = 0;
    len[1] = fa[1] = 0;
    memset(next[1], 0, sizeof(next[1]));
  }
  void add(int x) {
    int p = last, np = ++sz; last = np;
    len[np] = len[p]+1;
    memset(next[np], 0, sizeof(next[np]));
    while (p && !next[p][x]) next[p][x]=np, p=fa[p];
    if (!p) fa[np] = 1;
    else {
      int q = next[p][x];
      if (len[q] == len[p]+1) fa[np] = q;
      else {
        int nq = ++sz;
        memcpy(next[nq], next[q], sizeof(next[q]));
        fa[nq] = fa[q], fa[np] = fa[q] = nq;
        len[nq] = len[p]+1;
        while (p && next[p][x]==q) next[p][x]=nq, p=fa[p];
      }
    }
    tot += len[np]-len[fa[np]];
  }
};
SAM sam;
int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    scanf("%s", S);
    int n = strlen(S);
    for (int i=0; i<n; ++i) {
      sam.init();
      for (int j=i; j<n; ++j) sam.add(S[j]-'a'), ans[i+1][j+1] = sam.tot;
    }
    int q; scanf("%d", &q);
    while (q--) {
      int l, r; scanf("%d%d", &l, &r);
      printf("%d\n", ans[l][r]);
    }
  }
  return 0;
}
