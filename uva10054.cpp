#include <bits/stdc++.h>
using namespace std;

const int maxn = 55;
struct Eulerian {
  int e[maxn][maxn], E;
  int wk[maxn], deg[maxn];
  vector<int> ans;

  void init() {
    memset(e, 0, sizeof(e));
    memset(deg, 0, sizeof(deg));
    E = 0;
  }
  void add_edge(int u, int v) {
    ++e[u][v], ++e[v][u], ++E;
    ++deg[u], ++deg[v];
  }
  bool get_cycle() {
    for (int u=0; u<maxn; ++u) if (deg[u]&1) return false;
    memset(wk, 0, sizeof(wk));
    ans.clear();
    int u0 = 0;
    while (deg[u0]==0) ++u0;
    vector<int> s; s.push_back(u0);
    while (!s.empty()) {
      int u = s.back();
      if (deg[u]==0) {
        s.pop_back(), ans.push_back(u);
      } else {
        while (e[u][wk[u]]==0) ++wk[u];
        int v = wk[u];
        --E, --deg[u], --deg[v];
        --e[u][v], --e[v][u];
        s.push_back(v);
      }
    }
    return E==0;
  }
} eulerian;

int main(void) {
  int Z, kase=0; scanf("%d", &Z);
  while (Z--) {
    if (kase) puts("");
    printf("Case #%d\n", ++kase);
    eulerian.init();
    int m; scanf("%d", &m);
    for (int i=0; i<m; ++i) {
      int u, v; scanf("%d%d", &u, &v);
      eulerian.add_edge(u-1, v-1);
    }
    int ok = eulerian.get_cycle();
    if (!ok) printf("some beads may be lost\n");
    else {
      for (int i=0; i<m; ++i) {
        printf("%d %d\n", eulerian.ans[i]+1, eulerian.ans[(i+1)%m]+1);
      }
    }
  }
  return 0;
}
