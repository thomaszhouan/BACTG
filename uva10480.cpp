#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 100;
const ll INF = 0x3f3f3f3f3f3f3f3f;
struct E {
  int u, v;
  ll cap, flow;
  E(int u, int v, ll cap, ll flow)
    : u(u), v(v), cap(cap), flow(flow) {}
};
struct Dinic {
  int n;
  vector<E> edge;
  vector<int> G[MAXN];
  int d[MAXN], work[MAXN];
  char vis[MAXN];

  void init(int n) {
    this->n = n;
    edge.clear();
    for (int i=0; i<n; ++i) G[i].clear();
  }
  void add_edge(int u, int v, ll cap) {
    int id = edge.size();
    edge.push_back(E(u, v, cap, 0));
    edge.push_back(E(v, u, cap, 0));
    G[u].push_back(id), G[v].push_back(id+1);
  }
  bool bfs(int src, int dst) {
    memset(d, -1, sizeof(d));
    deque<int> q;
    q.push_back(src), d[src] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop_front();
      for (int i=0; i<G[u].size(); ++i) {
        E &e = edge[G[u][i]];
        if (d[e.v]>=0 || e.cap==e.flow) continue;
        q.push_back(e.v), d[e.v] = d[u]+1;
      }
    }
    return d[dst]>=0;
  }
  ll dfs(int u, int dst, ll cap) {
    if (u==dst || !cap) return cap;
    ll flow = 0;
    for (int &i = work[u]; i<G[u].size(); ++i) {
      E &e = edge[G[u][i]];
      if (d[e.v]!=d[u]+1) continue;
      ll f = dfs(e.v, dst, min(e.cap-e.flow, (ll)cap));
      if (!f) continue;
      e.flow += f, edge[G[u][i]^1].flow -= f;
      flow += f, cap -= f;
      if (!cap) break;
    }
    return flow;
  }
  ll maxflow(int src, int dst) {
    ll flow = 0;
    while (bfs(src, dst)) {
      memset(work, 0, sizeof(work));
      flow += dfs(src, dst, INF);
    }
    return flow;
  }
  void dfs1(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    for (int i=0; i<G[u].size(); ++i) {
      E &e = edge[G[u][i]];
      if (e.cap>e.flow) dfs1(e.v);
    }
  }
  void get_ans(int src) {
    memset(vis, 0, sizeof(vis));
    dfs1(src);
    for (int i=0; i<edge.size(); i+=2) {
      E &e = edge[i];
      if (vis[e.u]+vis[e.v]==1)
        printf("%d %d\n", e.u+1, e.v+1);
    }
    printf("\n");
  }
} dinic;

int main(void) {
  int n, m;
  while (scanf("%d%d", &n, &m), n) {
    dinic.init(n);
    for (int i=0; i<m; ++i) {
      int u, v; ll cap; scanf("%d%d%lld", &u, &v, &cap);
      dinic.add_edge(u-1, v-1, cap);
    }
    ll tmp = dinic.maxflow(0, 1);
    dinic.get_ans(0);
  }
  return 0;
}
