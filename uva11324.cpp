#include <bits/stdc++.h>
using namespace std;

const int maxn = 2000;
struct E {
  int u, v;
  E(int u, int v) : u(u), v(v) {}
};
struct SCC {
  int n, scc_cnt, dfs_clock;
  vector<E> edge, edge_scc;
  vector<int> G[maxn], G_scc[maxn], s;
  int pre[maxn], lowlink[maxn], sccno[maxn];
  int val[maxn], dp[maxn], idx[maxn], deg[maxn];

  void init(int n) {
    this->n = n, scc_cnt = dfs_clock = 0;
    edge.clear(), s.clear();
    for (int i=0; i<n; ++i) G[i].clear();
    memset(pre, 0, sizeof(pre));
    memset(sccno, -1, sizeof(sccno));
  }
  void add_edge(int u, int v) {
    G[u].push_back(edge.size());
    edge.push_back(E(u, v));
  }
  void dfs(int u) {
    pre[u] = lowlink[u] = ++dfs_clock;
    s.push_back(u);
    for (int i=0; i<G[u].size(); ++i) {
      int v = edge[G[u][i]].v;
      if (!pre[v]) {
        dfs(v), lowlink[u] = min(lowlink[u], lowlink[v]);
      } else if (sccno[v]<0) {
        lowlink[u] = min(lowlink[u], pre[v]);
      }
    }
    if (lowlink[u]==pre[u]) {
      for (;;) {
        int x = s.back(); s.pop_back();
        sccno[x] = scc_cnt;
        if (x==u) break;
      }
      ++scc_cnt;
    }
  }
  void find_scc() {
    for (int i=0; i<n; ++i) if (!pre[i]) dfs(i);
  }
  void build_scc() {
    find_scc();
    edge_scc.clear();
    for (int i=0; i<scc_cnt; ++i) G_scc[i].clear();
    for (E &e : edge) {
      int u = sccno[e.u], v = sccno[e.v];
      if (u==v) continue;
      G_scc[u].push_back(edge_scc.size());
      edge_scc.push_back(E(u, v));
      ++deg[v];
    }
    memset(val, 0, sizeof(val));
    for (int i=0; i<n; ++i) ++val[sccno[i]];
  }
  void sort() {
    deque<int> q;
    for (int i=0; i<scc_cnt; ++i) if (!deg[i]) q.push_back(i);
    int curr = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop_front();
      idx[curr++] = u;
      for (int i=0; i<G_scc[u].size(); ++i) {
        int v = edge_scc[G_scc[u][i]].v;
        --deg[v]; if (!deg[v]) q.push_back(v);
      }
    }
  }
  void solve() {
    build_scc(), sort();
    memset(dp, 0, sizeof(dp)); int ans = 0;
    for (int i=scc_cnt-1; i>=0; --i) {
      dp[idx[i]] = val[idx[i]];
      for (int j=0; j<G_scc[idx[i]].size(); ++j) {
        int v = edge_scc[G_scc[idx[i]][j]].v;
        dp[idx[i]] = max(dp[idx[i]], val[idx[i]]+dp[v]);
      }
      ans = max(ans, dp[idx[i]]);
    }
    printf("%d\n", ans);
  }
} scc_;

int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    int n, m; scanf("%d%d", &n, &m);
    scc_.init(n);
    for (int i=0; i<m; ++i) {
      int u, v; scanf("%d%d", &u, &v);
      --u, --v; scc_.add_edge(u, v);
    }
    scc_.solve();
  }
  return 0;
}
