#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 1e5;
struct E {
  int u, v;
  E(int u, int v) : u(u), v(v) {}
};
struct BCC {
  int n, dfs_clock, bcc_cnt, cc_cnt;
  vector<E> edge, s;
  vector<int> G[maxn], bcc[maxn], cc[maxn];
  int pre[maxn], low[maxn];
  int vcut[maxn], bccno[maxn], ccno[maxn];

  void init(int n) {
    this->n = n, dfs_clock = bcc_cnt = cc_cnt = 0;
    edge.clear(), s.clear();
    for (int i=0; i<n; ++i) G[i].clear();
    memset(pre, 0, sizeof(pre));
    memset(vcut, 0, sizeof(vcut));
    memset(ccno, -1, sizeof(ccno));
    memset(bccno, -1, sizeof(bccno));
  }
  void add_edge(int u, int v) {
    int id = edge.size();
    edge.push_back(E(u, v));
    edge.push_back(E(v, u));
    G[u].push_back(id), G[v].push_back(id+1);
  }
  void dfs(int u, int fa) {
    low[u] = pre[u] = ++dfs_clock;
    ccno[u] = cc_cnt-1, cc[cc_cnt-1].push_back(u);
    int child = 0;
    for (int i=0; i<G[u].size(); ++i) {
      E e = edge[G[u][i]]; int v = e.v;
      if (!pre[v]) {
        s.push_back(e), ++child, dfs(v, u);
        low[u] = min(low[u], low[v]);
        if (low[v] >= pre[u]) {
          vcut[u] = true; int id = bcc_cnt;
          bcc[bcc_cnt++].clear();
          for (;;) {
            E x = s.back(); s.pop_back();
            if (bccno[x.u]!=id) bcc[id].push_back(x.u), bccno[x.u]=id;
            if (bccno[x.v]!=id) bcc[id].push_back(x.v), bccno[x.v]=id;
            if (x.u==u && x.v==v) break;
          }
        }
      } else if (pre[v]<pre[u] && v!=fa) {
        s.push_back(e), low[u] = min(low[u], pre[v]);
      }
    }
    if (fa<0 && child==1) vcut[u] = false;
  }
  void find_bcc() {
    for (int i=0; i<n; ++i) if (!pre[i]) {
      cc[cc_cnt++].clear(), dfs(i, -1);
    }
  }
  void solve() {
    find_bcc();
    ll ans = 1;
    int cnt = 0;
    for (int i=0; i<cc_cnt; ++i) {
      unordered_set<int> id;
      for (auto u : cc[i]) id.insert(bccno[u]);
      if (id.size()==1) {
        ll x = bcc[*id.begin()].size();
        ans *= x*(x-1)/2;
        cnt += 2;
      } else {
        for (auto t : id) {
          ll x = bcc[t].size();
          ll y = 0;
          for (auto u : bcc[t]) if (vcut[u]) ++y;
          if (y==1) ans *= x-y, cnt += 1;
        }
      }
    }
    printf("%d %lld\n", cnt, ans);
  }
} bcc_;

int main(void) {
  int m, kase=0;
  while (scanf("%d", &m), m) {
    printf("Case %d: ", ++kase);
    vector<E> foo;
    int n = 0;
    for (int i=0; i<m; ++i) {
      int u, v; scanf("%d%d", &u, &v);
      n = max(n, u), n = max(n, v);
      foo.push_back(E(u-1, v-1));
    }
    bcc_.init(n);
    for (int i=0; i<m; ++i) bcc_.add_edge(foo[i].u, foo[i].v);
    bcc_.solve();
  }
  return 0;
}
