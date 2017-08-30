#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 128+10;
const int MAXM = 11+10;
typedef bitset<MAXN> State;
int n, m;
int a[MAXN];
char buf[MAXM];
unordered_map<State, int> dp;

int solve(const State &s, int k) {
  if (s.count()<=1) return 0;
  if (dp.count(s)) return dp[s];
  dp[s] = INF;
  for (int i=0; i<m; ++i) if (k&(1<<i)) {
    State x, y; int kk = k^(1<<i);
    for (int j=0; j<n; ++j) if (s.test(j)) {
      if (a[j]&(1<<i)) x.set(j);
      else y.set(j);
    }
    dp[s] = min(dp[s], 1+max(solve(x, kk), solve(y, kk)));
  }
  return dp[s];
}

int main(void) {
  while (scanf("%d%d", &m, &n), n) {
    memset(a, 0, sizeof(a));
    for (int i=0; i<n; ++i) {
      scanf("%s", buf);
      for (int j=0; j<m; ++j) if (buf[j]=='1') a[i] |= 1<<j;
    }
    dp.clear();
    State s;
    for (int i=0; i<n; ++i) s.set(i);
    printf("%d\n", solve(s, (1<<m)-1));
  }
  return 0;
}
