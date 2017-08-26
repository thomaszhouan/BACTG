#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXS = 8;
const int INF = 0x3f3f3f3f;
int dp[1<<MAXS][1<<MAXS][MAXN];
int cost[MAXN], can[MAXN];
int n, m, s, ans;

int solve(int S1, int S2, int d) {
  if (d==n) return S2==(1<<s)-1?0:INF;
  int &ans = dp[S1][S2][d];
  if (ans>=0) return ans;
  ans = solve(S1, S2, d+1);
  int S0 = ((1<<s)-1)^S1^S2;
  int x0 = can[d]&S0, x1 = can[d]&S1;
  int s1 = (S1^x1)|x0, s2 = S2|x1;
  ans = min(ans, cost[d]+solve(s1, s2, d+1));
  return ans;
}

int main(void) {
  while (scanf("%d%d%d%*c", &s, &m, &n), s) {
    string str;
    int cnt[MAXS], tmp; memset(cnt, 0, sizeof(cnt));
    ans = 0;
    for (int i=0; i<m; ++i) {
      getline(cin, str);
      stringstream ss(str);
      ss >> tmp; ans += tmp;
      while (ss>>tmp) ++cnt[tmp-1];
    }
    int S1=0, S2=0;
    for (int i=0; i<s; ++i)
      if (cnt[i]==1) S1|=1<<i;
      else if (cnt[i]>1) S2|=1<<i;
    for (int i=0; i<n; ++i) {
      getline(cin, str);
      stringstream ss(str);
      ss >> cost[i]; can[i] = 0;
      while (ss >> tmp) can[i] |= 1<<(tmp-1);
    }
    memset(dp, -1, sizeof(dp));
    printf("%d\n", ans+solve(S1, S2, 0));
  }
  return 0;
}
