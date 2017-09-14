#include <cstdio>
#include <cstring>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

const int MAXN = 500;
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
};

int main(void) {
  int N, F, D; scanf("%d%d%d", &N, &F, &D);
  Dinic dinic; dinic.init(2*N+F+D+2);
  for (int i=1; i<=N; ++i) {
    int f, d; scanf("%d%d", &f, &d);
    for (int j=0; j<f; ++j) {
      int tmp; scanf("%d", &tmp);
      dinic.add_edge(tmp+2*N, 2*i-1, 1);
    }
    for (int j=0; j<d; ++j) {
      int tmp; scanf("%d", &tmp);
      dinic.add_edge(2*i, tmp+2*N+F, 1);
    }
  }
  for (int i=1; i<=N; ++i) dinic.add_edge(2*i-1, 2*i, 1);
  for (int i=1; i<=F; ++i) dinic.add_edge(0, 2*N+i, 1);
  for (int i=1; i<=D; ++i) dinic.add_edge(2*N+F+i, 2*N+F+D+1, 1);
  printf("%d\n", dinic.maxflow(0, 2*N+F+D+1));
  return 0;
}
