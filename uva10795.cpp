#include <cstdio>
typedef long long ll;

ll f(int n, int x, int *a) {
  if (!n) return 0;
  if (x==a[n-1]) return f(n-1, x, a);
  else return (1LL<<(n-1))+f(n-1, 6-x-a[n-1], a);
}

const int MAXN = 65;
int a[MAXN], b[MAXN];
int main(void) {
  int n, kase=0;
  while (scanf("%d", &n), n) {
    for (int i=0; i<n; ++i) scanf("%d", a+i);
    for (int i=0; i<n; ++i) scanf("%d", b+i);
    int m = n;
    while (m && a[m-1]==b[m-1]) --m;
    ll ans;
    if (!m) ans=0;
    else ans=1+f(m-1, 6-a[m-1]-b[m-1], a)+f(m-1, 6-a[m-1]-b[m-1], b);
    printf("Case %d: %lld\n", ++kase, ans);
  }
  return 0;
}
