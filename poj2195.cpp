#include <cstdio>
#include <cstring>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

const int MAXN = 1e4+10;
const int INF = 0x3f3f3f3f;
struct E {
  int u, v, cap, flow, cost;
  E(int u, int v, int cap, int flow, int cost)
    : u(u), v(v), cap(cap), flow(flow), cost(cost) {}
};
struct MCMF {
  vector<E> edge;
  vector<int> G[MAXN];
  bool inq[MAXN];
  int a[MAXN], p[MAXN], d[MAXN], n;

  void init(int n) {
    this->n = n;
    edge.clear();
    for (int i=0; i<n; ++i) G[i].clear();
  }
  void add_edge(int u, int v, int cap, int cost) {
    int id = edge.size();
    edge.push_back(E(u, v, cap, 0, cost));
    edge.push_back(E(v, u, 0, 0, -cost));
    G[u].push_back(id), G[v].push_back(id+1);
  }
  bool bellman_ford(int src, int dst, int &flow, int &cost) {
    memset(d, 0x3f, sizeof(d));
    memset(inq, 0, sizeof(inq));
    deque<int> q; q.push_back(src);
    d[src] = 0, a[src] = INF, inq[src] = 1;
    while (!q.empty()) {
      int u = q.front(); q.pop_front();
      inq[u] = 0;
      for (int i=0; i<G[u].size(); ++i) {
        E &e = edge[G[u][i]];
        if (e.flow==e.cap || d[u]+e.cost>=d[e.v]) continue;
        d[e.v] = d[u]+e.cost, p[e.v] = G[u][i];
        a[e.v] = min(a[u], e.cap-e.flow);
        if (!inq[e.v]) q.push_back(e.v), inq[e.v] = 1;
      }
    }
    if (d[dst]==INF) return false;
    flow += a[dst], cost += d[dst]*a[dst];
    for (int u=dst; u!=src; u=edge[p[u]].u)
      edge[p[u]].flow += a[dst], edge[p[u]^1].flow -= a[dst];
    return true;
  }
  int mincost(int src, int dst, int &cost) {
    int flow = 0; cost = 0;
    while (bellman_ford(src, dst, flow, cost));
    return flow;
  }
};

char buf[105];
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};
int main(void) {
  MCMF mcmf;
  int n, m;
  while (scanf("%d%d", &n, &m), n) {
    mcmf.init(n*m+2);
    for (int i=0; i<n; ++i) {
      scanf("%s", buf);
      for (int j=0; j<m; ++j) {
        if (buf[j]=='m') mcmf.add_edge(n*m, i*m+j, 1, 0);
        if (buf[j]=='H') mcmf.add_edge(i*m+j, n*m+1, 1, 0);
      }
    }
    for (int i=0; i<n; ++i) for (int j=0; j<m; ++j)
      for (int d=0; d<4; ++d) {
        int ii = i+dx[d], jj = j+dy[d];
        if (ii<0||jj<0||ii>=n||jj>=m) continue;
        mcmf.add_edge(i*m+j, ii*m+jj, 200, 1);
      }
    int ans = 0; mcmf.mincost(n*m, n*m+1, ans);
    printf("%d\n", ans);
  }
  return 0;
}
