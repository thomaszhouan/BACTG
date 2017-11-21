#include <bits/stdc++.h>
using namespace std;

const int maxn = 1005;
struct E {
  int u, v;
  E(int u, int v) : u(u), v(v) {}
};
struct BCC {
  int n, dfs_clock, bcc_cnt;
  vector<E> edge, s;
  vector<int> G[maxn], bcc[maxn];
  int pre[maxn], low[maxn];
  int vcut[maxn], bccno[maxn];
  int valid[maxn], color[maxn];

  void init(int n) {
    this->n = n, dfs_clock = bcc_cnt = 0;
    edge.clear(), s.clear();
    for (int i=0; i<n; ++i) G[i].clear();
    memset(pre, 0, sizeof(pre));
    memset(vcut, 0, sizeof(vcut));
    memset(bccno, -1, sizeof(bccno));
  }
  void add_edge(int u, int v) {
    int id = edge.size();
    edge.push_back(E(u, v));
    edge.push_back(E(v, u));
    G[u].push_back(id), G[v].push_back(id+1);
  }
  void dfs(int u, int fa) {
    low[u] = pre[u] = ++dfs_clock;
    int child = 0;
    for (int i=0; i<G[u].size(); ++i) {
      E e = edge[G[u][i]]; int v = e.v;
      if (!pre[v]) {
        s.push_back(e), ++child, dfs(v, u);
        low[u] = min(low[u], low[v]);
        if (low[v] >= pre[u]) {
          vcut[u] = true; int id = bcc_cnt;
          bcc[bcc_cnt++].clear();
          for (;;) {
            E x = s.back(); s.pop_back();
            if (bccno[x.u]!=id) bcc[id].push_back(x.u), bccno[x.u]=id;
            if (bccno[x.v]!=id) bcc[id].push_back(x.v), bccno[x.v]=id;
            if (x.u==u && x.v==v) break;
          }
        }
      } else if (pre[v]<pre[u] && v!=fa)
        s.push_back(e), low[u] = min(low[u], pre[v]);
    }
    if (fa<0 && child==1) vcut[u] = false;
  }
  void find_bcc() {
    for (int i=0; i<n; ++i) if (!pre[i]) dfs(i, -1);
  }
  int get_ans() {
    memset(valid, 0, sizeof(valid));
    for (int i=0; i<bcc_cnt; ++i) {
      unordered_set<int> sub;
      for (auto u : bcc[i]) sub.insert(u), color[u] = -1;
      if (!bipartite(bcc[i][0], 0, sub))
        for (auto u : bcc[i]) valid[u] = 1;
    }
    int ans = 0;
    for (int i=0; i<n; ++i) if (!valid[i]) ++ans;
    return ans;
  }
  bool bipartite(int u, int c, const unordered_set<int> sub) {
    color[u] = c;
    for (int i=0; i<G[u].size(); ++i) {
      int v = edge[G[u][i]].v;
      if (!sub.count(v)) continue;
      if (color[v]==color[u]) return false;
      if (color[v]<0 && !bipartite(v, 1-c, sub))
        return false;
    }
    return true;
  }
} bcc_;

int g[maxn][maxn];

int main(void) {
  int n, m;
  while (scanf("%d%d", &n, &m), n) {
    memset(g, 0, sizeof(g));
    for (int i=0; i<m; ++i) {
      int u, v; scanf("%d%d", &u, &v);
      --u, --v; g[u][v]=g[v][u]=1;
    }
    bcc_.init(n);
    for (int i=0; i<n; ++i) for (int j=i+1; j<n; ++j)
      if (!g[i][j]) bcc_.add_edge(i, j);
    bcc_.find_bcc();
    printf("%d\n", bcc_.get_ans());
  }
  return 0;
}
