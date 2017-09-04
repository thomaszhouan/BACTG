#include <bits/stdc++.h>
using namespace std;

const int P = 10007;
const int MAXN = 1e5+10;
int sumv[MAXN<<2][3], setv[MAXN<<2], mulv[MAXN<<2], addv[MAXN<<2];
int n, q;

int mul(int x, int y) {return x*y%P;}
int add(int x, int y) {return (x+y)%P;}
void build(int p, int L, int R) {
  for (int i=0; i<3; ++i) sumv[p][i] = 0;
  setv[p] = -1, mulv[p] = 1, addv[p] = 0;
  if (L==R) return;
  int M = (L+R)>>1;
  build(2*p, L, M);
  build(2*p+1, M+1, R);
}
void pushdown(int p, int L, int R) {
  if (setv[p]>=0) {
    sumv[p][0] = mul(R-L+1, setv[p]);
    sumv[p][1] = mul(sumv[p][0], setv[p]);
    sumv[p][2] = mul(sumv[p][1], setv[p]);
  }
  int m = 1;
  for (int i=0; i<3; ++i) {
    m = mul(m, mulv[p]);
    sumv[p][i] = mul(sumv[p][i], m);
  }
  sumv[p][2] = add(sumv[p][2], mul(3*addv[p]%P, sumv[p][1]));
  sumv[p][2] = add(sumv[p][2], mul(3*mul(addv[p], addv[p])%P, sumv[p][0]));
  sumv[p][1] = add(sumv[p][1], mul(2*addv[p]%P, sumv[p][0]));
  m = R-L+1;
  for (int i=0; i<3; ++i) {
    m = mul(m, addv[p]);
    sumv[p][i] = add(sumv[p][i], m);
  }
  if (L<R) {
    if (setv[p]>=0) {
      setv[2*p] = setv[2*p+1] = setv[p];
      mulv[2*p] = mulv[2*p+1] = 1;
      addv[2*p] = addv[2*p+1] = 0;
    }
    mulv[2*p] = mul(mulv[2*p], mulv[p]);
    mulv[2*p+1] = mul(mulv[2*p+1], mulv[p]);
    addv[2*p] = mul(addv[2*p], mulv[p]);
    addv[2*p+1] = mul(addv[2*p+1], mulv[p]);
    addv[2*p] = add(addv[2*p], addv[p]);
    addv[2*p+1] = add(addv[2*p+1], addv[p]);
  }
  setv[p] = -1, mulv[p] = 1, addv[p] = 0;
}
void update(int p, int L, int R, int uL, int uR, int c, int op) {
  pushdown(p, L, R);
  if (R<uL || uR<L) return;
  if (uL<=L && R<=uR) {
    switch (op) {
      case 1: addv[p] = c; break;
      case 2: mulv[p] = c; break;
      case 3: setv[p] = c; break;
    }
    pushdown(p, L, R);
    return;
  }
  int M = (L+R)>>1;
  update(2*p, L, M, uL, uR, c, op);
  update(2*p+1, M+1, R, uL, uR, c, op);
  for (int i=0; i<3; ++i) sumv[p][i] = add(sumv[2*p][i], sumv[2*p+1][i]);
}
int query(int p, int L, int R, int qL, int qR, int c) {
  pushdown(p, L, R);
  if (R<qL || qR<L) return 0;
  if (qL<=L && R<=qR) return sumv[p][c];
  int M = (L+R)>>1;
  return add(query(2*p, L, M, qL, qR, c), query(2*p+1, M+1, R, qL, qR, c));
}

int main(void) {
  while (scanf("%d%d", &n, &q), n) {
    build(1, 1, n);
    while (q--) {
      int op, x, y, c;
      scanf("%d%d%d%d", &op, &x, &y, &c);
      if (op==4) printf("%d\n", query(1, 1, n, x, y, c-1));
      else update(1, 1, n, x, y, c, op);
    }
  }
  return 0;
}
