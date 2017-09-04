#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+10;
int n, q;
struct SegTree {
  int lenv[MAXN<<2], pre[MAXN<<2], suf[MAXN<<2], setv[MAXN<<2];
  void build(int p, int L, int R) {
    lenv[p] = pre[p] = suf[p] = R-L+1;
    setv[p] = -1;
    if (L==R) return;
    int M = (L+R)>>1;
    build(2*p, L, M);
    build(2*p+1, M+1, R);
  }
  void pushdown(int p, int L, int R) {
    if (setv[p]<0) return;
    if (setv[p]) lenv[p] = pre[p] = suf[p] = 0;
    else lenv[p] = pre[p] = suf[p] = R-L+1;
    if (L<R) setv[2*p] = setv[2*p+1] = setv[p];
    setv[p] = -1;
  }
  void update(int p, int L, int R, int uL, int uR, int v) {
    pushdown(p, L, R);
    if (R<uL || uR<L) return;
    if (uL<=L && R<=uR) {
      setv[p] = v; pushdown(p, L, R);
      return;
    }
    int M = (L+R)>>1;
    update(2*p, L, M, uL, uR, v);
    update(2*p+1, M+1, R, uL, uR, v);
    pre[p] = pre[2*p]==M-L+1?pre[2*p]+pre[2*p+1]:pre[2*p];
    suf[p] = suf[2*p+1]==R-M?suf[2*p]+suf[2*p+1]:suf[2*p+1];
    lenv[p] = max(lenv[2*p], lenv[2*p+1]);
    lenv[p] = max(lenv[p], suf[2*p]+pre[2*p+1]);
  }
  // 0: lenv, 1: pre, 2: suf
  int query(int p, int L, int R, int qL, int qR, int op) {
    pushdown(p, L, R);
    if (R<qL || qR<L) return 0;
    if (qL<=L && R<=qR) {
      switch (op) {
        case 0: return lenv[p];
        case 1: return pre[p];
        case 2: return suf[p];
      }
    }
    int M = (L+R)>>1, tmp;
    switch (op) {
      case 0:
        tmp = max(query(2*p, L, M, qL, qR, 0), query(2*p+1, M+1, R, qL, qR, 0));
        tmp = max(tmp, query(2*p, L, M, qL, qR, 2)+query(2*p+1, M+1, R, qL, qR, 1));
        return tmp;
      case 1:
        tmp = query(2*p, L, M, qL, qR, 1);
        if (tmp==M-L+1) tmp += query(2*p+1, M+1, R, qL, qR, 1);
        return tmp;
      case 2:
        tmp = query(2*p+1, M+1, R, qL, qR, 2);
        if (tmp==R-M) tmp += query(2*p, L, M, qL, qR, 2);
        return tmp;
    }
    return 0;
  }
  int find(int a) {
    if (query(1, 1, n, 1, n, 0)<a) return -1;
    int L, R, e;
    L=1, R=n;
    while (L<R) {
      int M = (L+R)>>1;
      if (query(1, 1, n, 1, M, 0)<a) L=M+1; else R=M;
    }
    return R-a+1;
  }
};
SegTree seg1, seg2;

int main(void) {
  int Z, kase = 0; scanf("%d", &Z);
  while (Z--) {
    printf("Case %d:\n", ++kase);
    scanf("%d%d", &n, &q);
    seg1.build(1, 1, n), seg2.build(1, 1, n);
    while (q--) {
      int a, b; char op[20];
      scanf("%s", op);
      if (op[0]=='S') {
        scanf("%d%d", &a, &b);
        seg1.update(1, 1, n, a, b, 0);
        seg2.update(1, 1, n, a, b, 0);
        printf("I am the hope of chinese chengxuyuan!!\n");
      }
      if (op[0]=='D') {
        scanf("%d", &a);
        int L = seg1.find(a);
        if (L<0) printf("fly with yourself\n");
        else {
          printf("%d,let's fly\n", L);
          seg1.update(1, 1, n, L, L+a-1, 1);
        }
      }
      if (op[0]=='N') {
        scanf("%d", &a);
        int L = seg1.find(a);
        if (L<0) L = seg2.find(a);
        if (L<0) printf("wait for me\n");
        else {
          printf("%d,don't put my gezi\n", L);
          seg1.update(1, 1, n, L, L+a-1, 2);
          seg2.update(1, 1, n, L, L+a-1, 2);
        }
      }
    }
  }
  return 0;
}
