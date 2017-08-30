#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+10;
const int INF = 0x3f3f3f3f;
int tab[MAXN][25];
int a[MAXN], s[MAXN], N;
int v[MAXN], n, q;

void build(void) {
  for (int i=0; i<N; ++i) tab[i][0] = a[i];
  for (int k=1; (1<<k)<=N; ++k)
    for (int i=0; i+(1<<k)-1<N; ++i)
      tab[i][k] = max(tab[i][k-1], tab[i+(1<<(k-1))][k-1]);
}
int query(int l, int r) {
  if (l>r) return 0;
  int k = 0;
  while ((1<<(k+1))<=r-l+1) ++k;
  return max(tab[l][k], tab[r-(1<<k)+1][k]);
}

int main(void) {
  while (scanf("%d%d", &n, &q)==2) {
    for (int i=0; i<n; ++i) scanf("%d", v+i);
    N = 0;
    int curr = -INF;
    for (int i=0; i<n; ++i) {
      if (v[i]==curr) ++a[N-1];
      else {
        curr = v[i];
        a[N++] = 1;
      }
    }
    s[0] = a[0];
    for (int i=1; i<N; ++i) s[i] = s[i-1]+a[i];
    build();
    for (int i=0; i<q; ++i) {
      int x, y; scanf("%d%d", &x, &y);
      int l = lower_bound(s, s+N, x)-s;
      int r = lower_bound(s, s+N, y)-s;
      int ans = query(l+1, r-1);
      if (l<r) {
        ans = max(ans, y-s[r-1]);
        ans = max(ans, s[l]-x+1);
      } else ans = max(ans, y-x+1);
      printf("%d\n", ans);
    }
  }
  return 0;
}
