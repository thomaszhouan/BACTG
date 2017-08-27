#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e4+10;
int f[MAXN], d[MAXN];
int find(int u) {
  if (f[u]<0) return u;
  int v = f[u];
  f[u]=find(f[u]);
  d[u]+=d[v];
  return f[u];
}
void merge(int u, int v) {
  f[u] = v, d[u] = abs(u-v)%1000;
}
int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    int n; scanf("%d", &n);
    memset(d, 0, sizeof(d));
    memset(f, -1, sizeof(f));
    char buf[20];
    for (;;) {
      scanf("%s", buf);
      int u, v;
      if (buf[0]=='I') {
        scanf("%d%d", &u, &v);
        merge(u, v);
      }
      if (buf[0]=='E') {
        scanf("%d", &u);
        find(u);
        printf("%d\n", d[u]);
      }
      if (buf[0]=='O') break;
    }
  }
  return 0;
}
