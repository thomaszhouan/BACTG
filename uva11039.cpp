#include <bits/stdc++.h>
using namespace std;

const int inf = 0x3f3f3f3f;
int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    vector<int> a[2];
    int n; scanf("%d", &n);
    a[0].push_back(0), a[1].push_back(0);
    for (int i=0; i<n; ++i) {
      int tmp; scanf("%d", &tmp);
      if (tmp>0) a[0].push_back(tmp);
      else a[1].push_back(-tmp);
    }
    sort(a[0].begin(), a[0].end());
    sort(a[1].begin(), a[1].end());
    int ans = 0;
    int k[2];
    for (int id=0; id<2; ++id) {
      int i = id, tmp = 0;
      int cur = inf;
      k[0] = a[0].size()-1, k[1] = a[1].size()-1;
      for (;;) {
        while (a[i][k[i]]>=cur) --k[i];
        if (a[i][k[i]]) {
          ++tmp, cur = a[i][k[i]--];
          i = i^1;
        } else break;
      }
      ans = max(ans, tmp);
    }
    printf("%d\n", ans);
  }
  return 0;
}
