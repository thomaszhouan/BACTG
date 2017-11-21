#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  Point(int x, int y) : x(x), y(y) {}
};
const int maxn = 1005;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
int g[maxn][maxn];
int f[maxn][maxn], dis[maxn][maxn];
char buf[maxn];
int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    int R, C; scanf("%d%d", &R, &C);
    deque<Point> qf, q;
    memset(f, -1, sizeof(f));
    memset(dis, -1, sizeof(dis));
    for (int i=0; i<R; ++i) {
      scanf("%s", buf);
      for (int j=0; j<C; ++j) {
        switch (buf[j]) {
          case '#': g[i][j]=-1; break;
          case '.': g[i][j]=0; break;
          case 'F':
            g[i][j]=1, f[i][j]=0;
            qf.push_back(Point(i, j));
            break;
          case 'J':
            g[i][j]=2, dis[i][j]=0;
            q.push_back(Point(i, j));
            break;
        }
      }
    }
    while (!qf.empty()) {
      Point p = qf.front(); qf.pop_front();
      for (int d=0; d<4; ++d) {
        int xx = p.x+dx[d];
        int yy = p.y+dy[d];
        if (xx<0||yy<0||xx>=R||yy>=C) continue;
        if (g[xx][yy]==-1 || f[xx][yy]>=0) continue;
        f[xx][yy] = f[p.x][p.y]+1;
        qf.push_back(Point(xx, yy));
      }
    }
    bool found = false;
    while (!q.empty() && !found) {
      Point p = q.front(); q.pop_front();
      for (int d=0; d<4; ++d) {
        int xx = p.x+dx[d];
        int yy = p.y+dy[d]; 
        if (xx<0||yy<0||xx>=R||yy>=C) {
          printf("%d\n", dis[p.x][p.y]+1);
          found = true; break;
        }
        if (g[xx][yy]==-1 || dis[xx][yy]>=0) continue;
        if (f[xx][yy] <= dis[p.x][p.y]+1 && f[xx][yy]>=0) continue;
        dis[xx][yy] = dis[p.x][p.y]+1;
        q.push_back(Point(xx, yy));
      }
    }
    if (!found) printf("IMPOSSIBLE\n");
  }
  return 0;
}
