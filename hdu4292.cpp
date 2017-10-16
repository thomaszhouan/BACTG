#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int INF = 0x3f3f3f3f;
struct E {
  int u, v, cap, flow;
  E(int u, int v, int cap, int flow)
    : u(u), v(v), cap(cap), flow(flow) {}
};
struct Dinic {
  int n;
  vector<E> edge;
  vector<int> G[MAXN];
  int d[MAXN], work[MAXN];

  void init(int n) {
    this->n = n;
    edge.clear();
    for (int i=0; i<n; ++i) G[i].clear();
  }
  void add_edge(int u, int v, int cap) {
    int id = edge.size();
    edge.push_back(E(u, v, cap, 0));
    edge.push_back(E(v, u, 0, 0));
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
  int dfs(int u, int dst, int cap) {
    if (u==dst || !cap) return cap;
    int flow = 0;
    for (int &i = work[u]; i<G[u].size(); ++i) {
      E &e = edge[G[u][i]];
      if (d[e.v]!=d[u]+1) continue;
      int f = dfs(e.v, dst, min(e.cap-e.flow, cap));
      if (!f) continue;
      e.flow += f, edge[G[u][i]^1].flow -= f;
      flow += f, cap -= f;
      if (!cap) break;
    }
    return flow;
  }
  int maxflow(int src, int dst) {
    int flow = 0;
    while (bfs(src, dst)) {
      memset(work, 0, sizeof(work));
      flow += dfs(src, dst, INF);
    }
    return flow;
  }
} dinic;

char buf[300];
int main(void) {
  int n, f, d;
  while (~scanf("%d%d%d", &n, &f, &d)) {
    dinic.init(2*n+f+d+2);
    for (int i=0; i<f; ++i) {
      int cap; scanf("%d", &cap);
      dinic.add_edge(2*n+f+d, 2*n+i, cap);
    }
    for (int i=0; i<d; ++i) {
      int cap; scanf("%d", &cap);
      dinic.add_edge(2*n+f+i, 2*n+f+d+1, cap);
    }
    for (int i=0; i<n; ++i) {
      scanf("%s", buf);
      for (int j=0; j<f; ++j) if (buf[j]=='Y')
        dinic.add_edge(2*n+j, i, 1);
    }
    for (int i=0; i<n; ++i) {
      scanf("%s", buf);
      for (int j=0; j<d; ++j) if (buf[j]=='Y')
        dinic.add_edge(n+i, 2*n+f+j, 1);
    }
    for (int i=0; i<n; ++i) dinic.add_edge(i, n+i, 1);
    printf("%d\n", dinic.maxflow(2*n+f+d, 2*n+f+d+1));
  }
  return 0;
};
