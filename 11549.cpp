#include <cstdio>
#include <unordered_set>
using namespace std;
typedef long long ll;
int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    int n, k; scanf("%d%d", &n, &k);
    unordered_set<int> a;
    a.insert(k);
    ll X = 1; for (int i=0; i<n; ++i) X *= 10;
    int ans = k;
    for (;;) {
      ll x = (ll)k*k;
      while (x>=X) x/=10;
      if (a.find(x)!=a.end()) break;
      ans = max(ans, k=x); a.insert(k);
    }
    printf("%d\n", ans);
  }
  return 0;
}
