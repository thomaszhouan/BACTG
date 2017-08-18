#include <cstdio>
const int MAXN=20;
int a[MAXN][MAXN], b[MAXN][MAXN];
int main(void) {
  int Z, kase=0; scanf("%d", &Z);
  while (Z--) {
    printf("Case %d: ", ++kase);
    int n; scanf("%d", &n);
    for (int i=0; i<n; ++i)
      for (int j=0; j<n; ++j)
        scanf("%d", &a[i][j]);
    int ans = -1;
    for (int x=0; x<(1<<n); ++x) {
      for (int j=0; j<n; ++j)
        b[0][j]=(x>>j)&1;
      for (int i=1; i<n; ++i)
        for (int j=0; j<n; ++j) {
          b[i][j]=0;
          if (i>=2) b[i][j]^=b[i-2][j];
          if (j>0) b[i][j]^=b[i-1][j-1];
          if (j<n-1) b[i][j]^=b[i-1][j+1];
        }
      bool valid=true; int cnt=0;
      for (int i=0; i<n&&valid; ++i)
        for (int j=0; j<n; ++j) {
          if (a[i][j]&&!b[i][j]) {valid=false; break;}
          if (!a[i][j]&&b[i][j]) ++cnt;
        }
      if (valid)
        if (ans<0||ans>cnt) ans=cnt;
    }
    printf("%d\n", ans);
  }
  return 0;
}
