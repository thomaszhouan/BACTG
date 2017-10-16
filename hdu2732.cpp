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

char buf[MAXN];
int n, m, d, cnt;
int main(void) {
  int Z, kase=0; scanf("%d", &Z);
  while (Z--) {
    printf("Case #%d: ", ++kase);
    scanf("%d%d", &n, &d);
    for (int i=0; i<n; ++i) {
      scanf("%s", buf);
      if (i==0) m = strlen(buf), dinic.init(2*n*m+2);
      for (int j=0; j<m; ++j) {
        int tmp = buf[j]-'0';
        dinic.add_edge(i*m+j, i*m+j+m*n, tmp);
      }
    }
    cnt = 0;
    for (int i=0; i<n; ++i) {
      scanf("%s", buf);
      for (int j=0; j<m; ++j) if (buf[j]=='L')
        dinic.add_edge(2*n*m, i*m+j, 1), ++cnt;
    }
    for (int x=0; x<n; ++x) for (int y=0; y<m; ++y)
      for (int dx=-d; dx<=d; ++dx) for (int dy=-d; dy<=d; ++dy) {
        if (dx*dx+dy*dy>d*d) continue;
        int xx = x+dx, yy = y+dy;
        if (xx<0 || yy<0 || xx>=n || yy>=m) continue;
        dinic.add_edge(n*m+x*m+y, xx*m+yy, INF);
      }
    for (int x=0; x<n; ++x) for (int y=0; y<m; ++y)
      if (x<d || y<d || n-x<=d || m-y<=d)
        dinic.add_edge(n*m+x*m+y, 2*n*m+1, INF);
    int ans = cnt - dinic.maxflow(2*n*m, 2*n*m+1);
    if (ans==0) printf("no lizard was left behind.\n");
    if (ans==1) printf("1 lizard was left behind.\n");
    if (ans>1) printf("%d lizards were left behind.\n", ans);
  }
  return 0;
}
