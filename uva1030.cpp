#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=15;
int n, ans;
int m[6][MAXN][MAXN];
int c[MAXN][MAXN][MAXN];
#define REP(i, n) for (i=0; i<(n); ++i)
void get(int t, int i, int j, int k, int &x, int &y, int &z) {
  switch (t) {
    case 0: x=i, y=j, z=k; return;
    case 1: x=i, y=k, z=n-1-j; return;
    case 2: x=i, y=n-1-j, z=n-1-k; return;
    case 3: x=i, y=n-1-k, z=j; return;
    case 4: x=k, y=j, z=n-1-i; return;
    case 5: x=n-1-k, y=j, z=i; return;
  }
}

int main(void) {
  int i, j, k, l;
  int x, y, z;
  char str[MAXN];
  while (scanf("%d", &n), n) {
    memset(c, 0, sizeof(c));

    REP(i, n) REP(j, 6) {
      scanf("%s", str);
      REP(k, n) m[j][i][k] = str[k];
    }

    REP(k, 6) REP(i, n) REP(j, n) if (m[k][i][j]=='.')
      REP(l, n) { get(k,i,j,l,x,y,z); c[x][y][z]=-1; }

    for (;;) {
L:
      REP(k, 6) REP(i, n) REP(j, n) if (m[k][i][j]!='.')
        REP(l, n) {
          get(k,i,j,l,x,y,z);
          if (c[x][y][z]==-1) continue;
          if (c[x][y][z]==0) {c[x][y][z]=m[k][i][j];break;}
          else if(c[x][y][z]!=m[k][i][j]) {
            c[x][y][z]=-1; goto L;
          } else break;
        }
      break;
    }

    ans = 0;
    REP(i, n) REP(j, n) REP(k, n) if (c[i][j][k]>=0) ++ans;
    printf("Maximum weight: %d gram(s)\n", ans);
  }
  return 0;
}
