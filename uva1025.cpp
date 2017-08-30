#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 55;
const int MAXT = 300;
const int INF = 0x3f3f3f3f;
char a[MAXT][MAXN], b[MAXT][MAXN];
int dp[MAXT][MAXN], dt[MAXN];
int sa[MAXN], sb[MAXN];

int main(void) {
  int n, kase = 0;
  while (scanf("%d", &n), n) {
    printf("Case Number %d: ", ++kase);
    int T, m1, m2; scanf("%d", &T);
    for (int i=0; i<n-1; ++i) scanf("%d", dt+i);
    scanf("%d", &m1);
    for (int i=0; i<m1; ++i) scanf("%d", sa+i);
    scanf("%d", &m2);
    for (int i=0; i<m2; ++i) scanf("%d", sb+i);
    memset(dp, 0x3f, sizeof(dp));
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    for (int i=0; i<m1; ++i) {
      int t=sa[i]; a[t][0]=1;
      for (int j=0; j<n-1; ++j) {
        t+=dt[j]; if (t>T) break;
        a[t][j+1]=1;
      }
    }
    for (int i=0; i<m2; ++i) {
      int t=sb[i]; b[t][n-1]=1;
      for (int j=n-2; j>=0; --j) {
        t+=dt[j]; if (t>T) break;
        b[t][j]=1;
      }
    }
    dp[0][0]=0;
    for (int t=1; t<=T; ++t) {
      for (int i=0; i<n; ++i) {
        dp[t][i]=min(dp[t][i], 1+dp[t-1][i]);
        if (a[t][i] && i>0)
          dp[t][i]=min(dp[t][i], dp[t-dt[i-1]][i-1]);
        if (b[t][i] && i<n-1)
          dp[t][i]=min(dp[t][i], dp[t-dt[i]][i+1]);
      }
    }
    if (dp[T][n-1]==INF) printf("impossible\n");
    else printf("%d\n", dp[T][n-1]);
  }
  return 0;
}
