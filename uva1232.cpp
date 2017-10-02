#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+10;
int maxv[MAXN<<2], minv[MAXN<<2], setv[MAXN<<2];

int ans;
void push_down(int q, int L, int R) {
  if (setv[q]<0) return;
  maxv[q] = minv[q] = setv[q];
  if (R-L>1)
    setv[q<<1] = setv[q<<1|1] = setv[q];
  setv[q] = -1;
}
void update(int q, int L, int R, int uL, int uR, int h) {
  push_down(q, L, R);
  if (uR<=L || R<=uL) return;
  if (uL<=L && R<=uR) {
    if (h<minv[q]) return;
    if (h>=maxv[q]) {
      setv[q] = h, ans += R-L;
      push_down(q, L, R);
      return;
    }
  }
  int M = (L+R)/2;
  update(q<<1, L, M, uL, uR, h);
  update(q<<1|1, M, R, uL, uR, h);
  minv[q] = min(minv[q<<1], minv[q<<1|1]);
  maxv[q] = max(maxv[q<<1], maxv[q<<1|1]);
}

int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    int n; scanf("%d", &n);
    ans = 0;
    memset(minv, 0, sizeof(minv));
    memset(maxv, 0, sizeof(maxv));
    memset(setv, -1, sizeof(setv));
    for (int i=0; i<n; ++i) {
      int L, R, h; scanf("%d%d%d", &L, &R, &h);
      update(1, 1, 100000, L, R, h);
    }
    printf("%d\n", ans);
  }
  return 0;
}
