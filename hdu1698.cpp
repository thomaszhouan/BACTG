#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+10;
int setv[MAXN<<2], sumv[MAXN<<2];
int n, q;

void pushdown(int p, int L, int R) {
  if (!setv[p]) return;
  sumv[p] = setv[p]*(R-L+1);
  if (L==R) return;
  setv[2*p] = setv[p];
  setv[2*p+1] = setv[p];
  setv[p] = 0;
}
void build(int p, int L, int R) {
  if (L==R) {sumv[p]=1; return;}
  int M = (L+R)/2;
  build(2*p, L, M);
  build(2*p+1, M+1, R);
  sumv[p] = sumv[2*p]+sumv[2*p+1];
}
void update(int p, int L, int R, int uL, int uR, int v) {
  pushdown(p, L, R);
  if (R<uL || uR<L) return;
  if (uL<=L && R<=uR) {
    setv[p] = v;
    pushdown(p, L, R);
    return;
  }
  int M = (L+R)/2;
  update(2*p, L, M, uL, uR, v);
  update(2*p+1, M+1, R, uL, uR, v);
  sumv[p] = sumv[2*p]+sumv[2*p+1];
}
int query(int p, int L, int R, int qL, int qR) {
  pushdown(p, L, R);
  if (R<qL || qR<L) return 0;
  if (qL<=L && R<=qR) return sumv[p];
  int M = (L+R)/2;
  return query(2*p, L, M, qL, qR)+query(2*p+1, M+1, R, qL, qR);
}
int main(void) {
  int Z, kase = 0; scanf("%d", &Z);
  while (Z--) {
    printf("Case %d: ", ++kase);
    scanf("%d%d", &n, &q);
    memset(setv, 0, sizeof(setv));
    build(1, 1, n);
    for (int i=0; i<q; ++i) {
      int u, v, w; scanf("%d%d%d", &u, &v, &w);
      update(1, 1, n, u, v, w);
    }
    printf("The total value of the hook is %d.\n", query(1, 1, n, 1, n));
  }
  return 0;
}
