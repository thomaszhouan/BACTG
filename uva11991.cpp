#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
namespace std {
  template<> struct hash<ii> {
    size_t operator()(const ii &x) const {
      size_t res = 17;
      res = res*31+hash<int>()(x.first);
      res = res*31+hash<int>()(x.second);
      return res;
    }
  };
}
unordered_map<ii, int> ans;
unordered_map<int, int> cnt;
int main(void) {
  int n, m;
  while (scanf("%d%d", &n, &m)==2) {
    ans.clear();
    cnt.clear();
    for (int i=1; i<=n; ++i) {
      int x; scanf("%d", &x);
      if (!cnt.count(x)) cnt[x] = 0;
      ++cnt[x];
      ans[make_pair(cnt[x], x)] = i;
    }
    for (int i=0; i<m; ++i) {
      int k, v; scanf("%d%d", &k, &v);
      if (!ans.count(make_pair(k, v))) printf("0\n");
      else printf("%d\n", ans[make_pair(k, v)]);
    }
  }
  return 0;
}
