#include <cstdio>
#include <cstring>
#include <vector>
#include <deque>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

typedef pair<int, int> ii;
const int MAXN = 1000;
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

map<string, int> id;
int ID(const string &s) {
  if (id.count(s)) return id[s];
  int tmp = id.size()+1;
  return id[s]=tmp;
}

char buf[200], buf1[200];
int plug[200];
vector<ii> ada;

int main(void) {
  int N, M, K;
  scanf("%d", &N);
  for (int i=1; i<=N; ++i) {
    scanf("%s", buf); string s(buf);
    ID(s);
  }
  scanf("%d", &M);
  for (int i=1; i<=M; ++i) {
    scanf("%*s%s", buf); string s(buf);
    plug[i] = ID(s);
  }
  scanf("%d", &K);
  for (int i=1; i<=K; ++i) {
    scanf("%s%s", buf, buf1); string s(buf), s1(buf1);
    ada.push_back(make_pair(ID(s), ID(s1)));
  }
  int T = id.size();
  Dinic dinic; dinic.init(2+M+2*T);
  for (int i=1; i<=M; ++i) {
    dinic.add_edge(0, i, 1);
    dinic.add_edge(i, M+T+plug[i], 1);
  }
  for (int i=1; i<=N; ++i) {
    dinic.add_edge(M+i, M+T+i, 1);
    dinic.add_edge(M+T+i, M+2*T+1, 1);
  }
  for (int i=0; i<ada.size(); ++i)
    dinic.add_edge(M+T+ada[i].first, M+T+ada[i].second, 500);
  printf("%d\n", M-dinic.maxflow(0, M+2*T+1));
  return 0;
}
