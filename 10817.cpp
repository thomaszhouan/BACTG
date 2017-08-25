#include <bits/stdc++.h>
using namespace std;

const int MAXT = (1<<8)+10;
const int MAXN = 200;
const int INF = 0x3f3f3f3f;
int dp[MAXT][MAXT][MAXN];
int a[MAXN], b[MAXN];

const int MAXLEN = 2048;
char buf[MAXLEN+10];
int s, m, n;

int solve(int S1, int S2, int d) {
  int tar = (1<<s)-1, ans = INF;
  if (n==d) {
    if (S2==tar) ans = 0;
    return dp[S1][S2][d]=ans;
  }
  if (dp[S1][S2][d]>=0) return dp[S1][S2][d];
  if (S2==tar) return dp[S1][S2][d]=0;
  ans = solve(S1, S2, d+1);
  int s1, s2;
  s2 = (S2|(S1&b[d]));
  s1 = (S1|((tar^S1^S2)&b[d]));
  s1 ^= (S1&b[d]);
  ans = min(ans, a[d]+solve(s1, s2, d+1));
  ans = min(ans, INF);
  return dp[S1][S2][d]=ans;
}

char *readint(char *s, int &x) {
  x=0;
  while (*s&&isspace(*s)) ++s;
  while (*s&&isdigit(*s)) x*=10, x+=*s-'0', ++s;
  if (*s) return ++s;
  else return 0;
}

int main(void) {
  while (scanf("%d%d%d%*c", &s, &m, &n), s) {
    int cnt[10]; memset(cnt, 0, sizeof(cnt));
    int ans = 0;
    for (int i=0; i<m; ++i) {
      fgets(buf, MAXLEN, stdin);
      int tmp; char *s = buf;
      s = readint(s, tmp);
      ans += tmp;
      while (s=readint(s, tmp)) ++cnt[tmp-1];
    }
    int S1=0, S2=0;
    for (int i=0; i<s; ++i)
      if (cnt[i]==1) S1 |= 1<<i;
      else if (cnt[i]>1) S2 |= 1<<i;
    for (int i=0; i<n; ++i) {
      fgets(buf, MAXLEN, stdin);
      b[i] = 0;
      int tmp; char *s = buf;
      s = readint(s, a[i]);
      while (s=readint(s, tmp)) b[i] |= 1<<(tmp-1);
    }
    memset(dp, -1, sizeof(dp));
    printf("%d\n", ans+solve(S1, S2, 0));
  }
  return 0;
}
