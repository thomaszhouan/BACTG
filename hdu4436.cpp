#include <bits/stdc++.h>
using namespace std;

const int MAXLEN = 1e5+10;
const int SIGMA = 11;
struct SAM {
  int len[MAXLEN<<1], fa[MAXLEN<<1];
  int next[MAXLEN<<1][SIGMA];
  int cnt[MAXLEN<<1], b[MAXLEN<<1];
  int dp[MAXLEN<<1];
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
  int get_ans() {
    int ans = 0; sort();
    memset(cnt, 0, sizeof(cnt));
    memset(dp, 0, sizeof(dp));
    cnt[1] = 1;
    for (int i=1; i<=sz; ++i) {
      int x = b[i]; ans += dp[x], ans %= 2012;
      for (int ch=(x==1?1:0); ch<10; ++ch) if (next[x][ch]) {
        int y = next[x][ch];
        cnt[y] += cnt[x], cnt[y] %= 2012;
        dp[y] += 10*dp[x]+ch*cnt[x], dp[y] %= 2012;
      }
    }
    return ans;
  }
};
SAM sam;
char S[MAXLEN];
int main(void) {
  int n;
  for (;;) {
    if (scanf("%d", &n)!=1) break;
    sam.init();
    while (n--) {
      scanf("%s", S);
      for (char *p=S; *p; ++p) sam.add(*p-'0');
      sam.add(10);
    }
    printf("%d\n", sam.get_ans());
  }
  return 0;
}
