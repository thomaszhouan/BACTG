#include <bits/stdc++.h>
using namespace std;
struct E {
  int w, u, v;
  E(int w, int u, int v) : w(w), u(u), v(v) {}
  bool operator<(const E &e) const {return w<e.w;}
};
const int INF = 0x3f3f3f3f;
const int MAXN = 105;
vector<E> edge;
int fa[MAXN], ans;

int find(int u) {return fa[u]<0?u:fa[u]=find(fa[u]);}

int main(void) {
  int n, m;
  while (scanf("%d%d", &n, &m), n) {
    edge.clear();
    for (int i=0; i<m; ++i) {
      int u, v, w; scanf("%d%d%d", &u, &v, &w);
      edge.push_back(E(w, u-1, v-1));
    }
    sort(edge.begin(), edge.end());
    ans = INF;
    for (int i=0; i<m; ++i) {
      int cnt = n;
      memset(fa, -1, sizeof(fa));
      int j;
      for (j=i; j<m; ++j) {
        auto &e = edge[j];
        int fu = find(e.u), fv = find(e.v);
        if (fu==fv) continue;
        --cnt, fa[fu] = fv;
        if (cnt==1) break;
      }
      if (cnt==1) ans = min(ans, edge[j].w-edge[i].w);
    }
    printf("%d\n", ans==INF?-1:ans);
  }
  return 0;
}
