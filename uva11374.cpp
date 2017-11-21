#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
const int maxn = 600;
const int INF = 0x3f3f3f3f;
struct E {
  int u, v, w, id;
  E(int u, int v, int w, int id) : u(u), v(v), w(w), id(id) {}
};
struct HN {
  int d, u, id;
  HN(int d, int u, int id) : d(d), u(u), id(id) {}
  bool operator<(const HN &rhs) const {return d>rhs.d;}
};
struct Dijkstra {
  int n, d[maxn][2], p[maxn][2];
  vector<E> edge;
  vector<int> G[maxn];
  bool vis[maxn][2];

  void init(int n) {
    this->n = n;
    edge.clear();
    for (int i=0; i<n; ++i) G[i].clear();
  }
  void add_edge(int u, int v, int w, int id) {
    G[u].push_back(edge.size());
    edge.push_back(E(u, v, w, id));
    G[v].push_back(edge.size());
    edge.push_back(E(v, u, w, id));
  }
  void sssp(int s) {
    priority_queue<HN> q;
    memset(d, 0x3f, sizeof(d)), d[s][0] = 0;
    memset(p, -1, sizeof(p));
    memset(vis, 0, sizeof(vis));
    q.push(HN(0, s, 0));
    while (!q.empty()) {
      HN x = q.top(); q.pop();
      int u = x.u, id = x.id; if (vis[u][id]) continue;
      vis[u][id] = true;
      for (int i=0; i<G[u].size(); ++i) {
        E &e = edge[G[u][i]];
        if (x.id==1 && e.id==1) continue;
        int iid = max(x.id, e.id);
        if (x.d+e.w>=d[e.v][iid]) continue;
        d[e.v][iid] = x.d+e.w, p[e.v][iid] = G[u][i];
        q.push(HN(d[e.v][iid], e.v, iid));
      }
    }
  }
  void solve(int s, int t) {
    sssp(s);
    vector<int> v;
    int ans, id, c = -1;
    if (d[t][0]<d[t][1]) ans = d[t][0], id = 0;
    else ans = d[t][1], id = 1;
    v.push_back(t);
    while (t != s) {
      E &e = edge[p[t][id]];
      if (e.id==1) c = e.u, id = 0;
      t = e.u, v.push_back(t);
    }
    for (int i=v.size()-1; i>=0; --i) {
      printf("%d", v[i]);
      if (i) putchar(' ');
    }
    puts("");
    if (c==-1) printf("Ticket Not Used\n");
    else printf("%d\n", c);
    printf("%d\n", ans);
  }
} sssp_;

int main(void) {
  int n, s, e; bool first = true;
  while (~scanf("%d%d%d", &n, &s, &e)) {
    if (!first) puts(""); else first = false;
    sssp_.init(n+10);
    int m; scanf("%d", &m);
    while (m--) {
      int u, v, w; scanf("%d%d%d", &u, &v, &w);
      sssp_.add_edge(u, v, w, 0);
    }
    scanf("%d", &m);
    while (m--) {
      int u, v, w; scanf("%d%d%d", &u, &v, &w);
      sssp_.add_edge(u, v, w, 1);
    }
    sssp_.solve(s, e);
  }
  return 0;
}
