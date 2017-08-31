#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 1e5+10;
ll sumv[MAXN<<2], a[MAXN];
char one[MAXN<<2];
int n, q;

void build(int p, int L, int R) {
  if (L==R) {
    sumv[p] = a[L];
    one[p] = a[L]==1;
    return;
  }
  int M = (L+R)/2;
  build(2*p, L, M);
  build(2*p+1, M+1, R);
  sumv[p] = sumv[2*p]+sumv[2*p+1];
  one[p] = one[2*p]&&one[2*p+1];
}
void update(int p, int L, int R, int uL, int uR) {
  if (R<uL || uR<L) return;
  if (L==R) {
    a[L] = floor(sqrt(a[L]));
    sumv[p] = a[L];
    one[p] = a[L]==1;
    return;
  }
  if (uL<=L && R<=uR && one[p]) return;
  int M = (L+R)/2;
  update(2*p, L, M, uL, uR);
  update(2*p+1, M+1, R, uL, uR);
  sumv[p] = sumv[2*p]+sumv[2*p+1];
  one[p] = one[2*p]&&one[2*p+1];
}
ll query(int p, int L, int R, int qL, int qR) {
  if (R<qL || qR<L) return 0;
  if (qL<=L && R<=qR) return sumv[p];
  int M = (L+R)/2;
  return query(2*p, L, M, qL, qR)+query(2*p+1, M+1, R, qL, qR);
}
int main(void) {
  int kase = 0;
  while (scanf("%d", &n)==1) {
    printf("Case #%d:\n", ++kase);
    for (int i=1; i<=n; ++i) scanf("%lld", a+i);
    build(1, 1, n);
    scanf("%d", &q);
    for (int i=0; i<q; ++i) {
      int op, L, R; scanf("%d%d%d", &op, &L, &R);
      if (L>R) swap(L, R);
      if (op) printf("%lld\n", query(1, 1, n, L, R));
      else update(1, 1, n, L, R);
    }
    printf("\n");
  }
  return 0;
}
