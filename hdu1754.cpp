#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5+10;
const int INF = 0x3f3f3f3f;
int maxv[MAXN<<2], a[MAXN], n, m;

void build(int p, int L, int R) {
  if (L==R) {maxv[p] = a[L]; return;}
  int M = (L+R)/2;
  build(2*p, L, M);
  build(2*p+1, M+1, R);
  maxv[p] = max(maxv[2*p], maxv[2*p+1]);
}
void update(int p, int L, int R, int x, int v) {
  if (x<L || x>R) return;
  if (L==R) {maxv[p] = v; return;}
  int M = (L+R)/2;
  update(2*p, L, M, x, v);
  update(2*p+1, M+1, R, x, v);
  maxv[p] = max(maxv[2*p], maxv[2*p+1]);
}
int query(int p, int L, int R, int qL, int qR) {
  if (qR<L || R<qL) return -INF;
  if (qL<=L && R<=qR) return maxv[p];
  int M = (L+R)/2;
  return max(query(2*p, L, M, qL, qR), query(2*p+1, M+1, R, qL, qR));
}
int main(void) {
  while (scanf("%d%d", &n, &m)==2) {
    for (int i=1; i<=n; ++i) scanf("%d", a+i);
    build(1, 1, n);
    char buf[10]; int u, v;
    for (int i=0; i<m; ++i) {
      scanf("%s %d %d", buf, &u, &v);
      if (buf[0]=='Q') printf("%d\n", query(1, 1, n, u, v));
      if (buf[0]=='U') update(1, 1, n, u, v);
    }
  }
  return 0;
}
