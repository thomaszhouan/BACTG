#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 15;
char a[MAXN][MAXN];
int dx[]={-1, 0, 1, 0};
int dy[]={0, -1, 0, 1};

int main(void) {
  int Z, kase=0; scanf("%d", &Z);
  while (Z--) {
    printf("Case %d:\n", ++kase);
    int n; scanf("%d", &n);
    for (int i=0; i<n; ++i) scanf("%s", a[i]);
    for (int i=0; i<n; ++i) {
      for (int j=0; j<n; ++j) {
        if (a[i][j]!='.') {printf("%c", a[i][j]); continue;}
        bool ok; a[i][j] = 'A';
        do {
          ok=true;
          for (int d=0; d<4; ++d) {
            int x=i+dx[d], y=j+dy[d];
            if (x<0||y<0||x>=n||y>=n) continue;
            if (a[x][y]==a[i][j]) {ok=false; break;}
          }
          if (!ok) ++a[i][j];
        } while (!ok);
        printf("%c", a[i][j]);
      }
      printf("\n");
    }
  }
  return 0;
}
