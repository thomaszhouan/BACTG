#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int MAXN = 25;
ll g[MAXN][MAXN][MAXN], s[MAXN][MAXN][MAXN];
const ll INF=0x3f3f3f3f3f3f3f3f;
#define REP(i,n) for(int i=1; i<=(n); ++i)
int main(void) {
  int Z; scanf("%d", &Z);
  for (int z=0; z<Z; ++z) {
    if (z) printf("\n");
    int a, b, c; scanf("%d%d%d", &a, &b, &c);
    REP(i,a) REP(j,b) REP(k,c) scanf("%lld", &g[i][j][k]);
    memset(s, 0, sizeof(s));
    REP(i,a) REP(j,b) REP(k,c) s[i][j][k]=s[i][j][k-1]+g[i][j][k];
    REP(i,a) REP(j,b) REP(k,c) s[i][j][k]+=s[i][j-1][k];
    ll ans=-INF;
    REP(x,b) for (int u=x; u<=b; ++u) REP(y,c) for (int v=y; v<=c; ++v) {
      ll m=0, S=0;
      REP(i,a) {
        S+=s[i][u][v]-s[i][u][y-1]-s[i][x-1][v]+s[i][x-1][y-1];
        ans=max(ans, S-m); m=min(m, S);
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}
