#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MAXN = 1e6+10;

ll a[MAXN], b[MAXN];
int main(void) {
  int n;
  while (scanf("%d", &n)==1) {
    ll tot = 0;
    for (int i=0; i<n; ++i) {
      scanf("%lld", a+i);
      tot += a[i];
    }
    tot /= n;
    b[0] = 0;
    for (int i=1; i<n; ++i)
      b[i] = b[i-1]+tot-a[i];
    sort(b, b+n);
    ll x = b[n/2], ans = 0, tmp;
    for (int i=0; i<n; ++i) {
      tmp = x-b[i]; if (tmp<0) tmp=-tmp;
      ans += tmp;
    }
    printf("%lld\n", ans);
  }
  return 0;
}
