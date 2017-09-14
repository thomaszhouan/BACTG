#include <cstdio>
#include <cstring>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

#ifdef LOCAL
#define LOG(...) fprintf(stderr, __VA_ARGS__)
#else
#define LOG(...)
#endif

const int MAXN = 200;
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
struct Node {
  int a[4], q;
  Node(int q=0) : q(q) {memset(a, 0, sizeof(a));}
};
int n, p;
Node node[MAXN];

int main(void) {
  scanf("%d%d", &p, &n);
  for (int i=1; i<=n; ++i) {
    int q, tmp; scanf("%d", &q);
    node[i] = Node(q);
    for (int j=0; j<p; ++j) {
      scanf("%d", &tmp);
      if (tmp==0) node[i].a[0] |= 1<<j;
      if (tmp==1) node[i].a[1] |= 1<<j;
    }
    for (int j=0; j<p; ++j) {
      scanf("%d", &tmp);
      if (tmp==0) node[i].a[2] |= 1<<j;
      if (tmp==1) node[i].a[3] |= 1<<j;
    }
  }
  Dinic dinic; dinic.init(2*n+2);
  for (int i=1; i<=n; ++i) {
    if (node[i].a[1]==0) {dinic.add_edge(0, i<<1, INF);LOG("src->%d\n", i);}
    if (node[i].a[3]==(1<<p)-1) {dinic.add_edge(i<<1|1, 1, INF);LOG("%d->dst\n", i);}
    dinic.add_edge(i<<1, i<<1|1, node[i].q);
    for (int j=1; j<=n; ++j) {
      if (i==j) continue;
      if ((node[j].a[0]&node[i].a[2])==node[j].a[0] &&
          (node[j].a[1]&node[i].a[3])==node[j].a[1])
        {dinic.add_edge(i<<1|1, j<<1, INF);LOG("%d->%d\n", i, j);}
    }
  }
  printf("%d ", dinic.maxflow(0, 1));
  vector<int> id;
  for (int i=1; i<=n; ++i) for (int j=0; j<dinic.G[i<<1|1].size(); ++j) {
    int x = dinic.G[i<<1|1][j]; E &e = dinic.edge[x];
    if (e.flow>0 && e.v!=1) id.push_back(x);
  }
  printf("%d\n", (int)id.size());
  for (int i=0; i<id.size(); ++i) {
    E &e = dinic.edge[id[i]];
    printf("%d %d %d\n", (e.u-1)>>1, e.v>>1, e.flow);
  }
  return 0;
}
