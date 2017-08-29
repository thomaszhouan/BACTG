#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;
typedef pair<int, int> ii;
int g[MAXN][MAXN];
char vis[MAXN][MAXN], done[MAXN][MAXN];
int cnt, m, n, d, ans;
bool valid;

struct Node {
  int x, y, v;
  Node(int x, int y, int v) : x(x), y(y), v(v) {}
  bool operator<(const Node &p) const {return v<p.v;}
};
vector<ii> a;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
void dfs(int x, int y, int v) {
  if (g[x][y]<=v-d) return;
  if (vis[x][y]) {
    if (done[x][y]) valid = false;
    return;
  }
  vis[x][y] = 1;
  a.push_back(make_pair(x, y));
  if (g[x][y]==v) ++cnt;
  for (int dir=0; dir<4; ++dir) {
    int xx = x+dx[dir], yy = y+dy[dir];
    if (xx<0||yy<0||xx>=m||y>=n) continue;
    dfs(xx, yy, v);
  }
}
int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    scanf("%d%d%d", &m, &n, &d);
    priority_queue<Node> q;
    for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) {
      scanf("%d", &g[i][j]);
      q.push(Node(i, j, g[i][j]));
    }
    memset(vis, 0, sizeof(vis));
    memset(done, 0, sizeof(done));
    ans = 0;
    while (!q.empty()) {
      Node p(q.top()); q.pop();
      if (done[p.x][p.y]) continue;
      cnt = 0, valid = true, a.clear();
      dfs(p.x, p.y, p.v);
      for (auto u : a) done[u.first][u.second] = 1;
      if (valid) ans += cnt;
    }
    printf("%d\n", ans);
  }
  return 0;
}
