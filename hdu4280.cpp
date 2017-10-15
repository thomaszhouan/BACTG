#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 1e5+10;
struct E {
  int u, v, cap, flow;
  E(int u, int v, int cap, int flow)
    : u(u), v(v), cap(cap), flow(flow) {}
};
struct ISAP {
  int n, s, t;
  vector<E> edge;
  vector<int> G[MAXN];
  int d[MAXN], p[MAXN], num[MAXN], work[MAXN];
  
  void init(int n) {
    this->n = n;
    edge.clear();
    for (int i=0; i<n; ++i) G[i].clear();
  }
  void add_edge(int u, int v, int cap) {
    int id = edge.size();
    edge.push_back(E(u, v, cap, 0));
    edge.push_back(E(v, u, cap, 0));
    G[u].push_back(id), G[v].push_back(id+1);
  }
  bool bfs(int src, int dst) {
    memset(d, -1, sizeof(d));
    deque<int> q;
    q.push_back(dst), d[dst] = 0;
    while (!q.empty()) {
      int v = q.front(); q.pop_front();
      for (int i=0; i<G[v].size(); ++i) {
        E &e = edge[G[v][i]^1];
        if (d[e.u]>=0 || e.cap==e.flow) continue;
        q.push_back(e.u), d[e.u] = d[v]+1;
      }
    }
    return d[src]>=0;
  }
  int augment() {
    int a = INF;
    for (int x=t; x!=s; x=edge[p[x]].u) {
      E &e = edge[p[x]];
      a = min(a, e.cap-e.flow);
    }
    for (int x=t; x!=s; x=edge[p[x]].u) {
      edge[p[x]].flow += a;
      edge[p[x]^1].flow -= a;
    }
    return a;
  }
  int maxflow(int s, int t) {
    this->s = s, this->t = t;
    int flow = 0; bfs(s, t);
    memset(num, 0, sizeof(num));
    for (int i=0; i<n; ++i) ++num[d[i]];
    int x = s;
    memset(work, 0, sizeof(work));
    while (d[s]<n) {
      if (x==t) flow += augment(), x = s;
      int ok = 0;
      for (int i=work[x]; i<G[x].size(); ++i) {
        E &e = edge[G[x][i]];
        if (e.cap==e.flow || d[x]!=d[e.v]+1) continue;
        ok = 1, p[e.v] = G[x][i], work[x] = i, x = e.v;
        break;
      }
      if (ok) continue;
      int m = n-1;
      for (int i=0; i<G[x].size(); ++i) {
        E &e = edge[G[x][i]];
        if (e.cap > e.flow) m = min(m, d[e.v]);
      }
      if (--num[d[x]]==0) break;
      ++num[d[x]=m+1], work[x] = 0;
      if (x!=s) x = edge[p[x]].u;
    }
    return flow;
  }
} isap;

int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    int n, m; scanf("%d%d", &n, &m);
    isap.init(n);
    int src=0, dst=0, minx, maxx;
    for (int i=0; i<n; ++i) {
      int x; scanf("%d%*d", &x);
      if (i==0) minx = maxx = x;
      else {
        if (minx > x) minx = x, src = i;
        if (maxx < x) maxx = x, dst = i;
      }
    }
    for (int i=0; i<m; ++i) {
      int u, v, w; scanf("%d%d%d", &u, &v, &w);
      --u, --v;
      isap.add_edge(u, v, w);
    }
    printf("%d\n", isap.maxflow(src, dst));
  }
  return 0;
}
