#include <bits/stdc++.h>
using namespace std;

const int maxn = 20;
struct E {
  int u, v;
  E(int u, int v) : u(u), v(v) {}
};
struct TopSort {
  int n;
  vector<E> edge;
  vector<int> G[maxn], ans;
  int deg[maxn]; // in deg

  void init(int n) {
    this->n = n;
    edge.clear();
    for (int i=0; i<n; ++i) G[i].clear();
    memset(deg, 0, sizeof(deg));
  }
  void add_edge(int u, int v) {
    G[u].push_back(edge.size());
    edge.push_back(E(u, v));
    ++deg[v];
  }
  bool sort() {
    ans.clear();
    deque<int> q;
    for (int u=0; u<n; ++u) if (deg[u]==0)
      q.push_back(u);
    while (!q.empty()) {
      int u = q.front(); q.pop_front();
      ans.push_back(u);
      for (int i=0; i<G[u].size(); ++i) {
        E &e = edge[G[u][i]];
        --deg[e.v];
        if (deg[e.v]==0) q.push_back(e.v);
      }
    }
    return ans.size() == n;
  }
} top_sort;

int fa[maxn], ran[maxn];
int find(int u) {return fa[u]<0?u:fa[u]=find(fa[u]);}
bool merge(int u, int v) {
  u = find(u), v = find(v);
  if (u==v) return false;
  if (u>v) swap(u, v);
  fa[v] = u; return true;
}
int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    int n; scanf("%d", &n);
    memset(fa, -1, sizeof(fa));
    char s[400]; scanf("%s", s);
    char *p; p = s;
    int cnt = n+1;
    for (int i=0; i<n; ++i) for (int j=i+1; j<=n; ++j, ++p)
      if (*p=='0') if (merge(i, j)) --cnt;
    top_sort.init(cnt);
    unordered_map<int, int> id;
    for (int i=0; i<=n; ++i) if (find(i)==i) {
      int x = id.size(); id[i] = x;
    }
    p = s;
    for (int i=0; i<n; ++i) for (int j=i+1; j<=n; ++j, ++p) {
      int u = find(i), v = find(j);
      if (*p=='-') top_sort.add_edge(id[u], id[v]);
      if (*p=='+') top_sort.add_edge(id[v], id[u]);
    }
    top_sort.sort();
    for (int i=0; i<top_sort.ans.size(); ++i) {
      for (int j=0; j<=n; ++j) if (id[find(j)]==top_sort.ans[i])
        ran[j] = i;
    }
    for (int i=0; i<n; ++i) {
      if (i) putchar(' ');
      printf("%d", ran[i]-ran[i+1]);
    }
    puts("");
  }
  return 0;
}
