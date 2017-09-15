#include <cstdio>
#include <cstring>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

const int MAXN = 210;
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

#define REP(i, n) for (int i=0; i<(n); ++i)
int need[60][200], have[60][200];
int main(void) {
  MCMF mcmf;
  int N, M, K;
  while (scanf("%d%d%d", &N, &M, &K), N) {
    REP(i,N) REP(j,K) scanf("%d", &need[i][j]);
    REP(i,M) REP(j,K) scanf("%d", &have[i][j]);
    bool flag = true; int ans = 0;
    REP(k,K) {
      mcmf.init(2+N+M);
      REP(i, M) mcmf.add_edge(N+M, i, have[i][k], 0);
      REP(i, N) mcmf.add_edge(i+M, N+M+1, need[i][k], 0);
      REP(i, N) REP(j, M) {
        int w; scanf("%d", &w);
        mcmf.add_edge(j, i+M, have[j][k], w);
      }
      if (!flag) continue;
      int flow, cost; flow = mcmf.mincost(N+M, N+M+1, cost);
      int sum = 0; REP(i, N) sum += need[i][k];
      if (flow<sum) flag = false; else ans += cost;
    }
    printf("%d\n", flag?ans:-1);
  }
  return 0;
}
