#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+10;
struct SAT {
  int n;
  vector<int> G[maxn<<1], s;
  bool mark[maxn<<1];

  void init(int n) {
    this->n = n;
    for (int i=0; i<2*n; ++i) G[i].clear();
    memset(mark, 0, sizeof(mark));
  }
  void add_clause(int x, int xv, int y, int yv) {
    x = x<<1|xv, y = y<<1|yv;
    G[x^1].push_back(y), G[y^1].push_back(x);
  }
  bool dfs(int x) {
    if (mark[x^1]) return false;
    if (mark[x]) return true;
    mark[x] = true, s.push_back(x);
    for (int i=0; i<G[x].size(); ++i)
      if (!dfs(G[x][i])) return false;
    return true;
  }
  bool solve() {
    for (int i=0; i<2*n; i+=2) if (!mark[i] && !mark[i+1]) {
      s.clear();
      if (dfs(i)) continue;
      for (auto x : s) mark[x] = false;
      s.clear();
      if (!dfs(i+1)) return false;
    }
    return true;
  }
} sat;

int f[maxn], a[maxn];
int main(void) {
  int n, m;
  while (scanf("%d%d", &n, &m), n) {
    sat.init(n);
    int tot = 0;
    for (int i=0; i<n; ++i) scanf("%d", a+i), tot += a[i];
    for (int i=0; i<n; ++i) f[i] = (n*a[i]>=tot);
    for (int i=0; i<m; ++i) {
      int u, v; scanf("%d%d", &u, &v); --u, --v;
      sat.add_clause(u, 1, v, 1);
      if (f[u]==f[v]) sat.add_clause(u, 0, v, 0);
    }
    if (!sat.solve()) printf("No solution.\n");
    else {
      for (int i=0; i<n; ++i) {
        if (sat.mark[i<<1]) printf("C\n");
        else if (f[i]) printf("A\n");
        else printf("B\n");
      }
    }
  }
  return 0;
}
