#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1005;
char g[MAXN][MAXN];
int h[MAXN], l[MAXN], r[MAXN];
#define REP(i,n) for(int i=0; i<(n); ++i)
int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    int m, n; scanf("%d%d", &m, &n);
    char str[10];
    REP(i,m) REP(j,n) {
        scanf("%s", str);
        if (str[0]=='F') g[i][j] = 1;
        else g[i][j] = 0;
      }
    int ans = 0;
    memset(h, 0, sizeof(h));
    memset(l, 0, sizeof(l));
    REP(i,n) r[i]=n-1;
    REP(i,m) {
      REP(j,n) {++h[j]; if (!g[i][j]) h[j]=0;}
      int k = -1;
      REP(j,n) {
        if (k>=l[j]) l[j]=k+1;
        if (!g[i][j]) k=j;
      }
      k = n;
      for (int j=n-1; j>=0; --j) {
        if (k<=r[j]) r[j]=k-1;
        if (!g[i][j]) k=j;
      }
      REP(j,n) if (!g[i][j]) l[j]=0,r[j]=n-1;
      REP(j,n) ans=max(ans, h[j]*(r[j]-l[j]+1));
    }
    printf("%d\n", ans*3);
  }
  return 0;
}
