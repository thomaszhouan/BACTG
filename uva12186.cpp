#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 1e5+10;
vector<int> e[MAXN], q[MAXN];
int n, T, ans; double r;

void dfs(int u, int f) {
  if (!e[u].size()) {q[f].push_back(1); return;}
  for (auto v : e[u]) dfs(v, u);
  sort(q[u].begin(), q[u].end());
  int k=(int)ceil(r*e[u].size()), s=0;
  for (int i=0; i<k; ++i) s+=q[u][i];
  if (f>=0) q[f].push_back(s); else ans=s;
}

int main(void) {
  while (scanf("%d%d", &n, &T), n) {
    r = T/100.0;
    for (int i=0; i<=n; ++i) e[i].clear(), q[i].clear();
    for (int i=1; i<=n; ++i) {
      int a; scanf("%d", &a);
      e[a].push_back(i);
    }
    dfs(0, -1); printf("%d\n", ans);
  }
  return 0;
}
