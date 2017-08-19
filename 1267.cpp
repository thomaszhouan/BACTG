#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 1005;
int n, r, k;
vector<int> e[MAXN], dep[MAXN];
int fa[MAXN];
char c[MAXN];

void dfs(int u, int f, int d) {
  fa[u] = f;
  if (e[u].size()==1 && d>k) dep[d].push_back(u);
  for (int i=0; i<e[u].size(); ++i) {
    int v = e[u][i];
    if (v==f) continue;
    dfs(v, u, d+1);
  }
}

void dfs2(int u, int d) {
  if (d>k) return;
  c[u] = 1;
  for (int i=0; i<e[u].size(); ++i)
    dfs2(e[u][i], d+1);
}

int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    scanf("%d%d%d", &n, &r, &k); --r;
    for (int i=0; i<n; ++i) {e[i].clear(); dep[i].clear();}
    for (int i=0; i<n-1; ++i) {
      int a, b; scanf("%d%d", &a, &b); --a, --b;
      e[a].push_back(b); e[b].push_back(a);
    }
    dfs(r, -1, 0);
    int ans = 0;
    memset(c, 0, sizeof(c));
    for (int d=n-1; d>k; --d) {
      for (int i=0; i<dep[d].size(); ++i) {
        int u = dep[d][i], v = u;
        if (c[u]) continue;
        for (int j=0; j<k; ++j) v = fa[v];
        ++ans, dfs2(v, 0);
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
