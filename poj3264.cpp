#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 5e4+10;
int tab[MAXN][20][2], a[MAXN];
int n, q;

void build(void) {
  for (int i=1; i<=n; ++i) tab[i][0][0]=tab[i][0][1]=a[i];
  for (int k=1; (1<<k)<=n; ++k)
    for (int i=1; i+(1<<k)-1<=n; ++i) {
      tab[i][k][0] = min(tab[i][k-1][0], tab[i+(1<<(k-1))][k-1][0]);
      tab[i][k][1] = max(tab[i][k-1][1], tab[i+(1<<(k-1))][k-1][1]);
    }
}
int query(int L, int R) {
  int k = 0;
  while ((1<<(k+1))<=R-L+1) ++k;
  int m = min(tab[L][k][0], tab[R-(1<<k)+1][k][0]);
  int M = max(tab[L][k][1], tab[R-(1<<k)+1][k][1]);
  return M-m;
}
int main(void) {
  scanf("%d%d", &n, &q);
  for (int i=1; i<=n; ++i) scanf("%d", a+i);
  build();
  for (int i=0; i<q; ++i) {
    int L, R; scanf("%d%d", &L, &R);
    printf("%d\n", query(L, R));
  }
}
