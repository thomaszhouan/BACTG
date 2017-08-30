#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+10;
int C[MAXN<<1], pos[MAXN], sp;
int n, m;
int lowbit(int x) {return x&-x;}
int sum(int x) {
  int res = 0;
  while (x) res+=C[x], x-=lowbit(x);
  return res;
}
void add(int x, int d) {
  while (x<=m+n) C[x]+=d, x+=lowbit(x);
}
int watch(int x) {
  int res = sum(pos[x]);
  add(pos[x], -1);
  pos[x] = ++sp;
  add(pos[x], 1);
  return res;
}
int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    scanf("%d%d", &n, &m);
    sp = n;
    memset(C, 0, sizeof(C));
    for (int i=1; i<=n; ++i) pos[i] = n+1-i, add(pos[i], 1);
    for (int i=0; i<m; ++i) {
      int x; scanf("%d", &x);
      if (i) putchar(' ');
      printf("%d", n-watch(x));
    }
    putchar('\n');
  }
  return 0;
}
