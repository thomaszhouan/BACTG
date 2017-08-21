#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 10005;
const int INF = 1e5;
vector<int> e[MAXN];
int dp[MAXN][3], n;

void dfs(int u, int f) {
  if (e[u].size()==1&&f>=0) {
    dp[u][0]=1, dp[u][1]=INF, dp[u][2]=0;
    return;
  }
  dp[u][0]=1, dp[u][1]=0, dp[u][2]=0;
  int m=INF;
  for (auto v : e[u]) {
    if (v==f) continue;
    dfs(v, u);
    dp[u][0]+=min(dp[v][0], dp[v][2]);
    dp[u][2]+=dp[v][1];
    m=min(m, dp[v][0]-dp[v][1]);
  }
  dp[u][1]=dp[u][2]+m;
  dp[u][1]=min(INF, dp[u][1]);
  dp[u][2]=min(INF, dp[u][2]);
}

int main(void) {
  while (scanf("%d", &n)==1) {
    int a, b;
    for (int i=0; i<n; ++i) e[i].clear();
    for (int i=0; i<n-1; ++i) {
      scanf("%d%d", &a, &b); --a, --b;
      e[a].push_back(b);
      e[b].push_back(a);
    }
    scanf("%*d");
    if (n==1) {printf("1\n"); continue;}
    dfs(0, -1);
    printf("%d\n", min(dp[0][0], dp[0][1]));
  }
  return 0;
}
