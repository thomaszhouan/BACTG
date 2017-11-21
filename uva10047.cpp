#include <bits/stdc++.h>
using namespace std;

struct State {
  int x, y, d, c;
  State(int x, int y, int d, int c)
    : x(x), y(y), d(d), c(c) {}
};
const int maxn = 30;
int dis[maxn][maxn][4][5];
char g[maxn][maxn];
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

int main(void) {
  int R, C, kase=0;
  while (scanf("%d%d", &R, &C), R) {
    if (kase) puts("");
    printf("Case #%d\n", ++kase);
    memset(dis, -1, sizeof(dis));
    deque<State> q;
    int tx, ty;
    for (int i=0; i<R; ++i) {
      scanf("%s", g[i]);
      for (int j=0; j<C; ++j) {
        if (g[i][j]=='S') {
          g[i][j] = '.';
          q.push_back(State(i, j, 0, 0));
          dis[i][j][0][0] = 0;
        }
        if (g[i][j]=='T') {
          g[i][j]='.';
          tx = i, ty = j;
        }
      }
    }
    bool ok = false;
    while (!q.empty()) {
      State s = q.front(); q.pop_front();
      int cd = dis[s.x][s.y][s.d][s.c];
      if (s.x==tx && s.y==ty && s.c==0) {
        ok = true;
        printf("minimum time = %d sec\n", cd);
        break;
      }
      int dd;
      dd = (s.d+1)%4;
      if (dis[s.x][s.y][dd][s.c]<0) {
        dis[s.x][s.y][dd][s.c] = cd+1;
        q.push_back(State(s.x, s.y, dd, s.c));
      }
      dd = (s.d+3)%4;
      if (dis[s.x][s.y][dd][s.c]<0) {
        dis[s.x][s.y][dd][s.c] = cd+1;
        q.push_back(State(s.x, s.y, dd, s.c));
      }
      int xx = s.x+dx[s.d];
      int yy = s.y+dy[s.d];
      if (xx<0 || yy<0 || xx>=R || yy>=C) continue;
      if (g[xx][yy]=='#' || dis[xx][yy][s.d][(s.c+1)%5]>=0) continue;
      dis[xx][yy][s.d][(s.c+1)%5] = cd+1;
      q.push_back(State(xx, yy, s.d, (s.c+1)%5));
    }
    if (!ok) printf("destination not reachable\n");
  }
  return 0;
}
