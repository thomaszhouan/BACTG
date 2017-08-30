#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 55;
const int INF = 0x3f3f3f3f;
int dp[MAXN][MAXN], K[MAXN][MAXN];
int a[MAXN];

int main(void) {
  int n, L;
  while (scanf("%d", &L), L) {
    scanf("%d", &n);
    a[0]=0, a[n+1]=L;
    for (int i=1; i<=n; ++i) scanf("%d", a+i);
    memset(dp, 0x3f, sizeof(dp));
    for (int i=0; i<=n; ++i) dp[i][i+1]=0;
    for (int i=0; i<=n-1; ++i) dp[i][i+2]=a[i+2]-a[i], K[i][i+2]=i+1;
    for (int k=3; k<=n+1; ++k) for (int i=0; i+k<=n+1; ++i) {
      int j=i+k;
      for (int t=i+1; t<=j-1; ++t) {
        int tmp = a[j]-a[i]+dp[i][t]+dp[t][j];
        if (tmp<dp[i][j]) K[i][j]=t, dp[i][j]=tmp;
      }
    }
    printf("The minimum cutting is %d.\n", dp[0][n+1]);
  }
  return 0;
}
