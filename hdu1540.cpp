#include <bits/stdc++.h>
using namespace std;

struct Range {
  int l, r;
  Range(int l=-1, int r=-1) : l(l), r(r) {}
  bool operator==(const Range &rhs) const {
    return l==rhs.l && r==rhs.r;
  }
};
const int MAXN = 5e4+10;
const Range null(-1, -1);
Range range[MAXN<<2];
int des[MAXN], sp, n, q;
char good[MAXN];

void pushdown(int p, int L, int R) {
  if (L==R || range[p]==null) return;
  int M = (L+R)/2;
  range[2*p] = range[p];
  range[2*p+1] = range[p];
  range[p] = null;
}
void build(int p, int L, int R) {
  range[p] = Range(1, n);
  if (L==R) return;
  int M = (L+R)/2;
  build(2*p, L, M);
  build(2*p+1, M+1, R);
}
void update(int p, int L, int R, const Range &u) {
  pushdown(p, L, R);
  if (R<u.l || u.r<L) return;
  if (u.l<=L && R<=u.r) {
    range[p] = u;
    pushdown(p, L, R);
    return;
  }
  int M = (L+R)/2;
  update(2*p, L, M, u);
  update(2*p+1, M+1, R, u);
}
Range query(int p, int L, int R, int x) {
  pushdown(p, L, R);
  if (L==R) return range[p];
  int M = (L+R)/2;
  if (x<=M) return query(2*p, L, M, x);
  else return query(2*p+1, M+1, R, x);
}

int main(void) {
  while (scanf("%d%d", &n, &q)==2) {
    build(1, 1, n);
    sp = 0;
    memset(good, 1, sizeof(good));
    while (q--) {
      char op[5]; int x;
      scanf("%s", op);
      if (op[0]=='D') {
        scanf("%d", &x);
        des[sp++] = x;
        if (!good[x]) continue;
        Range u = query(1, 1, n, x);
        if (u.l<x) update(1, 1, n, Range(u.l, x-1));
        if (u.r>x) update(1, 1, n, Range(x+1, u.r));
        update(1, 1, n, Range(x, x));
        good[x] = 0;
      }
      if (op[0]=='Q') {
        scanf("%d", &x);
        if (!good[x]) printf("0\n");
        else {
          Range u = query(1, 1, n, x);
          printf("%d\n", u.r-u.l+1);
        }
      }
      if (op[0]=='R') {
        for (;;) {
          if (!sp) break;
          x = des[--sp];
          if (good[x]) continue;
          Range u(x, x);
          if (x>1 && good[x-1]) {
            Range v = query(1, 1, n, x-1);
            u.l = v.l;
          }
          if (x<n && good[x+1]) {
            Range v = query(1, 1, n, x+1);
            u.r = v.r;
          }
          update(1, 1, n, u);
          good[x] = 1;
          break;
        }
      }
    }
  }
  return 0;
}
