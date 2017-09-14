#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6+10;
const int INF = 0x3f3f3f3f;
int sumv[MAXN<<2], minv[MAXN<<2], maxv[MAXN<<2];
int setv[MAXN<<2], addv[MAXN<<2];
int row, n, q;

void pushdown(int r, int p, int L, int R) {
  if (setv[r*(n<<2)+p]!=-1) {
    sumv[r*(n<<2)+p] = (R-L+1)*setv[r*(n<<2)+p];
    minv[r*(n<<2)+p] = maxv[r*(n<<2)+p] = setv[r*(n<<2)+p];
  }
  sumv[r*(n<<2)+p] += (R-L+1)*addv[r*(n<<2)+p];
  minv[r*(n<<2)+p] += addv[r*(n<<2)+p];
  maxv[r*(n<<2)+p] += addv[r*(n<<2)+p];
  if (L<R) {
    if (setv[r*(n<<2)+p]>=0) {
      setv[r*(n<<2)+(p<<1)] = setv[r*(n<<2)+(p<<1|1)] = setv[r*(n<<2)+p];
      addv[r*(n<<2)+(p<<1)] = addv[r*(n<<2)+(p<<1|1)] = 0;
    }
    addv[r*(n<<2)+(p<<1)] += addv[r*(n<<2)+p];
    addv[r*(n<<2)+(p<<1|1)] += addv[r*(n<<2)+p];
  }
  setv[r*(n<<2)+p] = -1, addv[r*(n<<2)+p] = 0;
}
void update(int r, int p, int L, int R, int uL, int uR, int v, int op) {
  pushdown(r, p, L, R);
  if (R<uL || uR<L) return;
  if (uL<=L && R<=uR) {
    if (op==1) addv[r*(n<<2)+p] = v;
    if (op==2) setv[r*(n<<2)+p] = v;
    pushdown(r, p, L, R);
    return;
  }
  int M = (L+R)>>1;
  update(r, p<<1, L, M, uL, uR, v, op);
  update(r, p<<1|1, M+1, R, uL, uR, v, op);
  sumv[r*(n<<2)+p] = sumv[r*(n<<2)+(p<<1)]+sumv[r*(n<<2)+(p<<1|1)];
  minv[r*(n<<2)+p] = min(minv[r*(n<<2)+(p<<1)], minv[r*(n<<2)+(p<<1|1)]);
  maxv[r*(n<<2)+p] = max(maxv[r*(n<<2)+(p<<1)], maxv[r*(n<<2)+(p<<1|1)]);
}
int ans_sum, ans_min, ans_max;
void query(int r, int p, int L, int R, int qL, int qR) {
  pushdown(r, p, L, R);
  if (R<qL || qR<L) return;
  if (qL<=L && R<=qR) {
    ans_sum += sumv[r*(n<<2)+p];
    ans_min = min(ans_min, minv[r*(n<<2)+p]);
    ans_max = max(ans_max, maxv[r*(n<<2)+p]);
    return;
  }
  int M = (L+R)>>1;
  query(r, p<<1, L, M, qL, qR);
  query(r, p<<1|1, M+1, R, qL, qR);
}
void query(int r, int qL, int qR) {
  ans_sum = 0, ans_min = INF, ans_max = -INF;
  query(r, 1, 1, n, qL, qR);
}
void build(void) {
  for (int r=0; r<row; ++r)
    update(r, 1, 1, n, 1, n, 0, 2);
}

int main(void) {
  while (scanf("%d%d%d", &row, &n, &q)==3) {
    int op, sumval, minval, maxval;
    int L, R, r1, r2, v;
    build();
    while (q--) {
      scanf("%d", &op);
      if (op==3) {
        scanf("%d%d%d%d", &r1, &L, &r2, &R);
        sumval = 0, minval = INF, maxval = -INF;
        for (int r=r1-1; r<r2; ++r) {
          query(r, L, R);
          sumval += ans_sum;
          minval = min(minval, ans_min);
          maxval = max(maxval, ans_max);
        }
        printf("%d %d %d\n", sumval, minval, maxval);
      }
      else {
        scanf("%d%d%d%d%d", &r1, &L, &r2, &R, &v);
        for (int r=r1-1; r<r2; ++r)
          update(r, 1, 1, n, L, R, v, op);
      }
    }
  }
  return 0;
}
