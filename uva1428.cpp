#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXR = 1e5+10;
const int MAXN = 2e4+10;
int a[MAXN], n;
ll c[MAXR], u[MAXN], v[MAXN];
int lowbit(int x) {return x&-x;}
ll sum(int x) {
  ll res = 0;
  while (x>0) res += c[x], x-=lowbit(x);
  return res;
}
void add(int x, ll d) {
  while (x<=MAXR) c[x]+=d, x+=lowbit(x);
}
int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    scanf("%d", &n);
    for (int i=0; i<n; ++i) scanf("%d", a+i);

    memset(c, 0, sizeof(c));
    for (int i=0; i<n; ++i)
      u[i] = sum(a[i]), add(a[i], 1);
    memset(c, 0, sizeof(c));
    for (int i=n-1; i>=0; --i)
      v[i] = sum(a[i]), add(a[i], 1);

    ll ans = 0;
    for (int i=0; i<n; ++i) {
      ans += u[i]*(n-i-1-v[i]);
      ans += v[i]*(i-u[i]);
    }
    printf("%lld\n", ans);
  }
  return 0;
}
