#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 105;
const int INF = 0x3f3f3f3f;
int a[MAXN][MAXN], dp[MAXN][MAXN];
int K[MAXN][MAXN];

int main(void) {
  int m, n;
  while (scanf("%d%d", &m, &n)==2) {
    for (int i=0; i<m; ++i) for (int j=0; j<n; ++j)
      scanf("%d", &a[i][j]);
    memset(dp, 0x3f, sizeof(dp));
    memset(K, 0x3f, sizeof(K));
    for (int i=0; i<m; ++i) dp[i][n-1]=a[i][n-1];
    for (int j=n-2; j>=0; --j) for (int i=0; i<m; ++i)
      for (int k=-1; k<=1; ++k) {
        int kk=i+k;
        if (kk<0) kk+=m; else if (kk>=m) kk-=m;
        int tmp=dp[kk][j+1]+a[i][j];
        if (tmp>dp[i][j]) continue;
        if (tmp==dp[i][j]) K[i][j]=min(K[i][j], kk);
        else dp[i][j]=tmp, K[i][j]=kk;
      }
    int ans = INF, x;
    for (int i=0; i<m; ++i) if (ans>dp[i][0])
      ans = dp[i][0], x = i;
    printf("%d", x+1);
    for (int j=1; j<n; ++j)
      x=K[x][j-1], printf(" %d", x+1);
    printf("\n%d\n", ans);
  }
  return 0;
}
