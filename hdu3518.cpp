#include <bits/stdc++.h>
using namespace std;

const int MAXLEN = 1005;
const int SIGMA = 26;
void Min(int &a, int b) {if (a>b) a=b;}
void Max(int &a, int b) {if (a<b) a=b;}
struct SAM {
  int len[MAXLEN<<1], fa[MAXLEN<<1];
  int next[MAXLEN<<1][SIGMA];
  int cnt[MAXLEN<<1], b[MAXLEN<<1];
  int L[MAXLEN<<1], R[MAXLEN<<1];
  int minlen[MAXLEN<<1];
  int sz, last;
  void init() { // start from 1
    sz = last = 1;
    len[1] = fa[1] = 0, L[1] = R[1] = 0;
    memset(next[1], 0, sizeof(next[1]));
    memset(minlen, 0, sizeof(minlen));
  }
  void add(int x, int n) {
    int p = last, np = ++sz; last = np;
    len[np] = len[p]+1, L[np] = R[np] = n;
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
        len[nq] = len[p]+1, L[nq] = L[q], R[nq] = R[q];
        while (p && next[p][x]==q) next[p][x]=nq, p=fa[p];
      }
    }
  }
  void sort() { // topological order for next and fa, from 1
    memset(cnt, 0, sizeof(cnt));
    for (int i=1; i<=sz; ++i) ++cnt[len[i]];
    for (int i=1; i<=sz; ++i) cnt[i] += cnt[i-1];
    for (int i=1; i<=sz; ++i) b[cnt[len[i]]--] = i;
  }
  void solve() {
    for (int i=sz; i>1; --i) {
      int x = b[i];
      Max(R[fa[x]], R[x]);
      minlen[x] = 1+len[fa[x]];
    }
    int ans = 0;
    for (int i=2; i<=sz; ++i) {
      int M = min(len[i], R[i]-L[i]);
      ans += max(0, M-minlen[i]+1);
    }
    printf("%d\n", ans);
  }
};
SAM sam;
char S[MAXLEN];
int main(void) {
  for (;;) {
    scanf("%s", S);
    if (S[0]=='#') break;
    sam.init();
    for (int i=0; S[i]; ++i) sam.add(S[i]-'a', i);
    sam.sort(), sam.solve();
  }
  return 0;
}
