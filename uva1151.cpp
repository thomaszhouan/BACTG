#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
const int MAXN = 1005;
const ll INF = 0x3f3f3f3f3f3f3f3f;
vector<vector<int> > com;
vector<ll> cost;
int f[MAXN];
int find(int u) {return f[u]<0?u:f[u]=find(f[u]);}
bool merge(int u, int v) {
  int fu = find(u), fv = find(v);
  if (fu==fv) return false;
  f[fu] = fv;
  return true;
}

vector<ii> pos;
struct E {
  ll w; int u, v;
  E(ll w, int u, int v) : w(w), u(u), v(v) {}
  bool operator<(const E &e) const {return w<e.w;}
};
vector<E> edge;
int cnt;
ll ans;

int main(void) {
  int Z; scanf("%d", &Z);
  bool is_first = true;
  while (Z--) {
    if (is_first) is_first = false;
    else printf("\n");
    int n, q; scanf("%d%d", &n, &q);
    com.clear(), cost.clear();
    for (int i=0; i<q; ++i) {
      int k, c; scanf("%d%d", &k, &c);
      cost.push_back(c);
      vector<int> foo;
      for (int j=0; j<k; ++j) {
        int tmp; scanf("%d", &tmp);
        foo.push_back(tmp-1);
      }
      com.push_back(foo);
    }
    pos.clear();
    for (int i=0; i<n; ++i) {
      int x, y; scanf("%d%d", &x, &y);
      pos.push_back(make_pair(x, y));
    }

    vector<E> ee;
    for (int i=0; i<n; ++i) for (int j=i+1; j<n; ++j) {
      ll dx = pos[i].first-pos[j].first;
      ll dy = pos[i].second-pos[j].second;
      ee.push_back(E(dx*dx+dy*dy, i, j));
    }
    sort(ee.begin(), ee.end());
    cnt = n, memset(f, -1, sizeof(f));
    edge.clear();
    for (auto &e : ee) {
      if (!merge(e.u, e.v)) continue;
      --cnt;
      edge.push_back(e);
    }

    ans = INF;
    for (int x=0; x<(1<<q); ++x) {
      ll tmp = 0;
      memset(f, -1, sizeof(f));
      cnt = n;
      for (int i=0; i<q; ++i) if (x&(1<<i)) {
        tmp += cost[i];
        for (int j=1; j<com[i].size(); ++j)
          if (merge(com[i][j], com[i][j-1])) --cnt;
      }
      for (auto &e : edge) {
        if (cnt==1) break;
        if (merge(e.u, e.v)) --cnt, tmp+=e.w;
      }
      ans = min(ans, tmp);
    }
    printf("%lld\n", ans);
  }
  return 0;
}
