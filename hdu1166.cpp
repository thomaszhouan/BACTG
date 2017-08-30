#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e4+10;
int sumv[MAXN<<2], a[MAXN], n;

void build(int p, int L, int R) {
  if (L==R) {sumv[p] = a[L]; return;}
  int M = (L+R)/2;
  build(2*p, L, M);
  build(2*p+1, M+1, R);
  sumv[p] = sumv[2*p]+sumv[2*p+1];
}
void update(int p, int L, int R, int x, int v) {
  if (x<L || x>R) return;
  if (L==R) {sumv[p]+=v; return;}
  int M = (L+R)/2;
  update(2*p, L, M, x, v);
  update(2*p+1, M+1, R, x, v);
  sumv[p] = sumv[2*p]+sumv[2*p+1];
}
int query(int p, int L, int R, int qL, int qR) {
  if (qR<L || qL>R) return 0;
  if (qL<=L && R<=qR) return sumv[p];
  int M = (L+R)/2;
  return query(2*p, L, M, qL, qR)+query(2*p+1, M+1, R, qL, qR);
}
int main(void) {
  int Z, kase = 0; scanf("%d", &Z);
  while (Z--) {
    printf("Case %d:\n", ++kase);
    scanf("%d", &n);
    for (int i=1; i<=n; ++i) scanf("%d", a+i);
    build(1, 1, n);
    char buf[20];
    for (;;) {
      scanf("%s", buf);
      if (buf[0]=='E') break;
      int u, v; scanf("%d%d", &u, &v);
      if (buf[0]=='Q') printf("%d\n", query(1, 1, n, u, v));
      if (buf[0]=='A') update(1, 1, n, u, v);
      if (buf[0]=='S') update(1, 1, n, u, -v);
    }
  }
  return 0;
}
