#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+10;
int f[MAXN];
int find(int u) {return f[u]<0?u:f[u]=find(f[u]);}
bool merge(int u, int v) {
  int fu = find(u), fv = find(v);
  if (fu==fv) return false;
  f[fu] = fv; return true;
}
int main(void) {
  int ans = 0;
  memset(f, -1, sizeof(f));
  int a, b;
  while (scanf("%d", &a)==1) {
    if (a==-1) {
      printf("%d\n", ans);
      memset(f, -1, sizeof(f));
      ans = 0;
      continue;
    }
    scanf("%d", &b);
    if (!merge(a, b)) ++ans;
  }
  return 0;
}
