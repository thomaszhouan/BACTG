#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;
const int MAXN = 205;
vector<int> e[MAXN];
int dp[MAXN][2], f[MAXN][2], n;

void dfs(int u) {
  dp[u][0]=0, f[u][0]=1;
  dp[u][1]=1, f[u][1]=1;
  for (auto v : e[u]) {
    dfs(v);
    dp[u][1]+=dp[v][0], f[u][1]&=f[v][0];
    int k=(dp[v][1]>dp[v][0]?1:0);
    int flag=(dp[v][1]==dp[v][0]?0:f[v][k]);
    dp[u][0]+=dp[v][k], f[u][0]&=flag;
  }
}

int main(void) {
  char str[200];
  while (scanf("%d", &n), n) {
    unordered_map<string, int> m;
    int cnt=0;
    scanf("%s", str); m[string(str)]=cnt++;
    for (int i=0; i<n; ++i) e[i].clear();
    for (int i=0; i<n-1; ++i) {
      string s; int a, b;
      scanf("%s", str); s=str;
      if (m.find(s)==m.end()) m[s]=cnt++;
      a=m[s];
      scanf("%s", str); s=str;
      if (m.find(s)==m.end()) m[s]=cnt++;
      b=m[s];
      e[b].push_back(a);
    }
    dfs(0);
    int k=(dp[0][0]>dp[0][1]?0:1);
    int flag=(dp[0][0]==dp[0][1]?0:f[0][k]);
    printf("%d %s\n", dp[0][k], flag?"Yes":"No");
  }
  return 0;
}
