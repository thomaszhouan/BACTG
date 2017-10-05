#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;
const int MAXLEN = 1e5+10;
const int SIGMA = 52;
inline int get_ch(char ch) {return ch>'Z'?ch-'a'+26:ch-'A';}
struct SAM {
  int len[MAXLEN<<1], fa[MAXLEN<<1];
  int next[MAXLEN<<1][SIGMA];
  int cnt[MAXLEN<<1], b[MAXLEN<<1];
  int minlen[MAXLEN<<1];
  ll dp[2][MAXLEN<<1], endpos[MAXLEN<<1];
  int sz, last;
  void init() { // start from 1
    sz = last = 1;
    len[1] = fa[1] = 0;
    memset(next[1], 0, sizeof(next[1]));
    memset(dp, 0, sizeof(dp));
    memset(minlen, 0, sizeof(minlen));
    memset(endpos, 0, sizeof(endpos));
  }
  void add(int x) {
    int p = last, np = ++sz; last = np;
    len[np] = len[p]+1; endpos[np] = 1;
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
  void solve(char *p, int K) {
    sort();
    for (int i=2; i<=sz; ++i) minlen[i] = len[fa[i]]+1;
    for (int i=sz; i>1; --i) {int x=b[i]; endpos[fa[x]]+=endpos[x];}
    int v=1, l=0;
    for (; *p; ++p) {
      int x = get_ch(*p);
      while (v>1 && !next[v][x]) v=fa[v], l=len[v];
      if (next[v][x]) v=next[v][x], ++l;
      if (l>=K) ++dp[0][v], dp[1][v] += l-max(K, minlen[v])+1;
    }
    for (int i=sz; i>1; --i) {
      int x=b[i]; dp[0][fa[x]]+=dp[0][x];
      dp[1][fa[x]] += dp[0][x]*max(0, len[fa[x]]-max(K, minlen[fa[x]])+1);
    }
    ll ans = 0;
    for (int i=2; i<=sz; ++i)
      ans += endpos[i]*dp[1][i];
    printf("%lld\n", ans);
  }
};
SAM sam;
char A[MAXLEN], B[MAXLEN];
int main(void) {
  int K;
  while (scanf("%d", &K), K) {
    scanf("%s%s", A, B);
    sam.init();
    for (char *p=A; *p; ++p) sam.add(get_ch(*p));
    sam.solve(B, K);
  }
  return 0;
}
