#include <cstdio>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
const int MAXN = 105;
char g[MAXN][MAXN];
int h[MAXN][MAXN], v[MAXN][MAXN];
int x[MAXN], y[MAXN];

int main(void) {
  int n, kase=0;
  while (scanf("%d", &n), n) {
    printf("Case %d: ", ++kase);
    memset(g, 0, sizeof(g));
    memset(h, 0, sizeof(h));
    memset(v, 0, sizeof(v));
    vector<int> tx, ty;
    unordered_map<int, int> mx, my;
    for (int i=0; i<n; ++i) {
      scanf("%d%d", x+i, y+i);
      tx.push_back(x[i]);
      ty.push_back(y[i]);
    }
    sort(tx.begin(), tx.end());
    sort(ty.begin(), ty.end());
    if (tx[0]==tx[n-1]||ty[0]==ty[n-1]) {printf("%d\n", n); continue;}
    for (int i=0; i<n; ++i) mx[tx[i]]=my[ty[i]]=i;
    for (int i=0; i<n; ++i) g[mx[x[i]]][my[y[i]]]=1;
    for (int i=0; i<n; ++i) {
      h[i][0]=g[i][0];
      for (int j=1; j<n; ++j) h[i][j]=h[i][j-1]+g[i][j];
    }
    for (int j=0; j<n; ++j) {
      v[0][j]=g[0][j];
      for (int i=1; i<n; ++i) v[i][j]=v[i-1][j]+g[i][j];
    }
    int ans=0;
    for (int k=0; k<n; ++k) for (int l=k+1; l<n; ++l) {
      int M=v[l-1][0]-v[k][0];
      for (int j=1; j<n; ++j) {
        ans = max(ans, h[k][j]+h[l][j]+v[l-1][j]-v[k][j]+M);
        M = max(M, v[l-1][j]-v[k][j]-h[k][j-1]-h[l][j-1]);
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
