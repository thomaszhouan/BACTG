#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 1005;
const int P = 1e9+7;
int n, q;
ll C[MAXN][MAXN];
int lowbit(int x) {return x&-x;}
void add(int i, int j, int v) {
  v %= P; if (v<0) v += P;
  for (int x=i; x<=n; x+=lowbit(x)) for (int y=j; y<=n; y+=lowbit(y))
    C[x][y] += v, C[x][y] %= P;
}
ll sum(int i, int j) {
  ll ans = 0;
  for (int x=i; x; x-=lowbit(x)) for (int y=j; y; y-=lowbit(y))
    ans += C[x][y], ans %= P;
  return ans;
}
char buf[100];
int main(void) {
  scanf("%d%d", &n, &q);
  while (q--) {
    scanf("%s", buf);
    if (buf[0]=='A') {
      int x, y, v; scanf("%d%d%d", &x, &y, &v);
      ++x, ++y; add(x, y, v);
    }
    if (buf[0]=='S') {
      int x1, y1, x2, y2; scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
      ++x2, ++y2;
      ll ans = sum(x2, y2)-sum(x1, y2)-sum(x2, y1)+sum(x1, y1);
      ans %= P; if (ans<0) ans += P;
      printf("%lld\n", ans);
    }
  }
  return 0;
}
