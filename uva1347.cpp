#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 1005;
typedef pair<int, int> ii;
double dis(const ii &p1, const ii &p2) {
  int dx=p1.first-p2.first;
  int dy=p1.second-p2.second;
  return sqrt(dx*dx+dy*dy);
}
double dp[2][MAXN][MAXN];
vector<ii> p;
int main(void) {
  int n;
  while (scanf("%d", &n)==1) {
    p.clear(); int x, y;
    for (int i=0; i<n; ++i) {
      scanf("%d%d", &x, &y);
      p.push_back(make_pair(x, y));
    }
    memset(dp, 0, sizeof(dp));
    for (int i=0; i<n-1; ++i)
      for (int j=0; j<n-1; ++j) {
        if (i==j&&i) continue;
        int k=max(i, j)+1;
        double tmp = dp[0][i][j]+dis(p[i], p[k]);
        if (dp[0][k][j]==0||dp[0][k][j]>tmp) dp[0][k][j]=tmp;
        tmp = dp[0][i][j]+dis(p[j], p[k]);
        if (dp[0][i][k]==0||dp[0][i][k]>tmp) dp[0][i][k]=tmp;
      }
    for (int i=n-1; i>0; --i)
      for (int j=n-1; j>0; --j) {
        if (i==j&&i<n-1) continue;
        int k=min(i, j)-1;
        double tmp = dp[1][i][j]+dis(p[i], p[k]);
        if (dp[1][k][j]==0||dp[1][k][j]>tmp) dp[1][k][j]=tmp;
        tmp = dp[1][i][j]+dis(p[j], p[k]);
        if (dp[1][i][k]==0||dp[1][i][k]>tmp) dp[1][i][k]=tmp;
      }
    double ans = 0;
    for (int i=0; i<n-1; ++i) {
      double tmp = dp[0][i][i+1]+dp[1][i][i+1];
      if (ans==0||ans>tmp) ans = tmp;
    }
    printf("%.2f\n", ans);
  }
  return 0;
}
