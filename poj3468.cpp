#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;
const int MAXN = 1e5+10;
ll sumv[MAXN<<2], addv[MAXN<<2];
int a[MAXN], n, q;

void pushdown(int p, int L, int R) {
  sumv[p] += (R-L+1)*addv[p];
  if (L<R) {
    addv[2*p] += addv[p];
    addv[2*p+1] += addv[p];
  }
  addv[p] = 0;
}
void build(int p, int L, int R) {
  if (L==R) {sumv[p]=a[L]; return;}
  int M = (L+R)/2;
  build(2*p, L, M);
  build(2*p+1, M+1, R);
  sumv[p] = sumv[2*p]+sumv[2*p+1];
}
void update(int p, int L, int R, int uL, int uR, int v) {
  pushdown(p, L, R);
  if (uR<L || R<uL) return;
  if (uL<=L && R<=uR) {
    addv[p] += v;
    pushdown(p, L, R);
    return;
  }
  int M = (L+R)/2;
  update(2*p, L, M, uL, uR, v);
  update(2*p+1, M+1, R, uL, uR, v);
  sumv[p] = sumv[2*p]+sumv[2*p+1];
}
ll query(int p, int L, int R, int qL, int qR) {
  pushdown(p, L, R);
  if (qR<L || R<qL) return 0;
  if (qL<=L && R<=qR) return sumv[p];
  int M = (L+R)/2;
  return query(2*p, L, M, qL, qR)+query(2*p+1, M+1, R, qL, qR);
}

int main(void) {
  while (scanf("%d%d", &n, &q)==2) {
    for (int i=1; i<=n; ++i) scanf("%d", a+i);
    memset(addv, 0, sizeof(addv));
    build(1, 1, n);
    char buf[10]; int u, v, w;
    for (int i=0; i<q; ++i) {
      scanf("%s", buf);
      if (buf[0]=='C') {
        scanf("%d%d%d", &u, &v, &w);
        update(1, 1, n, u, v, w);
      }
      if (buf[0]=='Q') {
        scanf("%d%d", &u, &v);
        printf("%lld\n", query(1, 1, n, u, v));
      }
    }
  }
  return 0;
}
