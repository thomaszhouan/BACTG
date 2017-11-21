#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e4;
struct E {
  int u, v;
  E(int u, int v) : u(u), v(v) {}
};
struct SCC {
  int n, scc_cnt;
  vector<E> edge;
  vector<int> G[maxn], GT[maxn], s;
  int vis[maxn], sccno[maxn];
  int deg[maxn][2];

  void init(int n) {
    this->n = n, scc_cnt = 0;
    edge.clear(), s.clear();
    for (int i=0; i<n; ++i) G[i].clear(), GT[i].clear();
    memset(vis, 0, sizeof(vis));
    memset(sccno, -1, sizeof(sccno));
  }
  void add_edge(int u, int v) {
    int id = edge.size();
    edge.push_back(E(u, v));
    G[u].push_back(id), GT[v].push_back(id);
  }
  void dfs1(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    for (int i=0; i<G[u].size(); ++i) dfs1(edge[G[u][i]].v);
    s.push_back(u);
  }
  void dfs2(int v) {
    if (sccno[v]>=0) return;
    sccno[v] = scc_cnt-1;
    for (int i=0; i<GT[v].size(); ++i) dfs2(edge[GT[v][i]].u);
  }
  void find_scc() {
    for (int i=0; i<n; ++i) dfs1(i);
    for (int i=n-1; i>=0; --i) if (sccno[s[i]]<0)
      ++scc_cnt, dfs2(s[i]);
  }
  void solve() {
    find_scc();
    memset(deg, 0, sizeof(deg));
    for (E &e : edge) {
      int u = sccno[e.u], v = sccno[e.v];
      if (u!=v) ++deg[u][0], ++deg[v][1];
    }
    if (scc_cnt == 1) printf("0\n");
    else {
      int cnt0 = 0, cnt1 = 0;
      for (int i=0; i<scc_cnt; ++i) {
        if (deg[i][1]==0) ++cnt0;
        if (deg[i][0]==0) ++cnt1;
      }
      printf("%d\n", max(cnt1, cnt0));
    }
  }
} scc_;

int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    int n, m; scanf("%d%d", &n, &m);
    scc_.init(n);
    for (int i=0; i<m; ++i) {
      int u, v; scanf("%d%d", &u, &v);
      scc_.add_edge(u-1, v-1);
    }
    scc_.solve();
  }
  return 0;
}
