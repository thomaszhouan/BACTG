#include <bits/stdc++.h>
using namespace std;

const int maxn = 2005;
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

int t[maxn][2], n;
int Abs(int x) {return x>0?x:-x;}
bool check(int d) {
  sat.init(n);
  for (int i=0; i<n; ++i) for (int j=i+1; j<n; ++j)
    for (int u=0; u<2; ++u) for (int v=0; v<2; ++v)
      if (Abs(t[i][u]-t[j][v])<d) {
        sat.add_clause(i, 1-u, j, 1-v);
      }
  return sat.solve();
}
int main(void) {
  while (~scanf("%d", &n)) {
    for (int i=0; i<n; ++i)
      scanf("%d%d", &t[i][0], &t[i][1]);
    int L=0, R=2e7+10;
    while (R-L>1) {
      int M = (L+R)>>1;
      if (check(M)) L=M; else R=M;
    }
    printf("%d\n", L);
  }
  return 0;
}
