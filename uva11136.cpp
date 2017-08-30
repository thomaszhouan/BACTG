#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(void) {
  int n;
  while (scanf("%d", &n), n) {
    multiset<int> a;
    ll ans = 0;
    for (int i=0; i<n; ++i) {
      int k; scanf("%d", &k);
      for (int j=0; j<k; ++j) {
        int x; scanf("%d", &x);
        a.insert(x);
      }
      multiset<int>::iterator it = a.begin();
      ans -= *it; a.erase(it);
      it = a.end(); --it;
      ans += *it; a.erase(it);
    }
    printf("%lld\n", ans);
  }
  return 0;
}
