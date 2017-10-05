#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
void Min(ll &a, ll b) {if (a>b) a=b;}
void Max(ll &a, ll b) {if (a<b) a=b;}
const int MAXLEN = 1e5+10;
const int SIGMA = 26;
char S[MAXLEN];
struct SAM {
  int len[MAXLEN<<1], fa[MAXLEN<<1];
  int next[MAXLEN<<1][SIGMA];
  int cnt[MAXLEN<<1], b[MAXLEN<<1];
  ll dp[MAXLEN<<1];
  int sz, last;
  void init() { // start from 1
    sz = last = 1;
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
  }
  void sort() { // topological order for next and fa, from 1
    memset(cnt, 0, sizeof(cnt));
    for (int i=1; i<=sz; ++i) ++cnt[len[i]];
    for (int i=1; i<=sz; ++i) cnt[i] += cnt[i-1];
    for (int i=1; i<=sz; ++i) b[cnt[len[i]]--] = i;
  }
  void solve(int n) {
    memset(dp, 0, sizeof(dp));
    while (n--) {
      scanf("%s", S);
      int q=1, l=0;
      for (char *p=S; *p; ++p) {
        char x = *p-'a';
        while (q>1 && !next[q][x]) q=fa[q], l=len[q];
        if (next[q][x]) q=next[q][x], ++l;
        Max(dp[q], l);
      }
    }
    ll ans = 0;
    for (int i=sz; i>1; --i) {
      Max(dp[fa[b[i]]], dp[b[i]]);
      Min(dp[fa[b[i]]], len[fa[b[i]]]);
    }
    for (int i=1; i<=sz; ++i) {
      ll minlen = dp[i];
      if (fa[i]) Max(minlen, len[fa[i]]);
      ans += len[i]-minlen;
    }
    printf("%lld\n", ans);
  }
};
SAM sam;

int main(void) {
  int Z, kase=0; scanf("%d", &Z);
  while (Z--) {
    printf("Case %d: ", ++kase);
    sam.init();
    int n; scanf("%d", &n);
    scanf("%s", S);
    for (char *p=S; *p; ++p) sam.add(*p-'a');
    sam.sort(); sam.solve(n);
  }
  return 0;
}
