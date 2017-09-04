#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e4+10;
int sumv[MAXN<<2], setv[MAXN<<2];
int n, q;

void build(void) {
  memset(sumv, 0, sizeof(sumv));
  memset(setv, -1, sizeof(setv));
}
void pushdown(int p, int L, int R) {
  if (setv[p]<0) return;
  sumv[p] = (R-L+1)*setv[p];
  if (L<R) setv[2*p] = setv[2*p+1] = setv[p];
  setv[p] = -1;
}
void update(int p, int L, int R, int uL, int uR, int v) {
  pushdown(p, L, R);
  if (R<uL || uR<L) return;
  if (uL<=L && R<=uR) {
    setv[p] = v;
    pushdown(p, L, R);
    return;
  }
  int M = (L+R)>>1;
  update(2*p, L, M, uL, uR, v);
  update(2*p+1, M+1, R, uL, uR, v);
  sumv[p] = sumv[2*p]+sumv[2*p+1];
}
int query(int p, int L, int R, int qL, int qR) {
  pushdown(p, L, R);
  if (R<qL || qR<L) return 0;
  if (qL<=L && R<=qR) return sumv[p];
  int M = (L+R)>>1;
  return query(2*p, L, M, qL, qR)+query(2*p+1, M+1, R, qL, qR);
}
int cnt_empty(int qL, int qR) {return (qR-qL+1)-query(1, 0, n-1, qL, qR);}

int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    scanf("%d%d", &n, &q);
    build();
    while (q--) {
      int op, a, b;
      scanf("%d%d%d", &op, &a, &b);
      if (op==2) {
        printf("%d\n", query(1, 0, n-1, a, b));
        update(1, 0, n-1, a, b, 0);
      }
      else {
        int cnt = cnt_empty(a, n-1);
        if (!cnt) {
          printf("Can not put any one.\n");
          continue;
        }
        b = min(b, cnt);
        int L, R, l, r;
        L = a, R = n-1;
        while (L<R) {
          int M = (L+R)>>1;
          if (cnt_empty(a, M)<b) L = M+1; else R = M;
        }
        r = R;
        L = a, R = n-1;
        while (L<R) {
          int M = (L+R)>>1;
          if (cnt_empty(a, M)) R = M; else L = M+1;
        }
        l = R;
        update(1, 0, n-1, l, r, 1);
        printf("%d %d\n", l, r);
      }
    }
    printf("\n");
  }
  return 0;
}
