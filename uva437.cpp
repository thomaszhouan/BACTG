#include <cstdio>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

struct Foo {
  int x, y, h;
  Foo(int x, int y, int h)
    : x(x), y(y), h(h) {}
  bool operator<(const Foo& f) const {
    return x+y<f.x+f.y;
  }
  bool operator==(const Foo& f) const {
    return x==f.x && y==f.y && h==f.h;
  }
};

namespace std {
  template<> struct hash<Foo> {
    size_t operator()(const Foo& f) const {
      size_t res=17;
      res=res*31+hash<int>()(f.x);
      res=res*31+hash<int>()(f.y);
      res=res*31+hash<int>()(f.h);
      return res;
    }
  };
}

int main(void) {
  int n, kase = 0;
  while (scanf("%d", &n), n) {
    printf("Case %d: maximum height = ", ++kase);
    int x, y, z; vector<Foo> foo;
    for (int i=0; i<n; ++i) {
      scanf("%d%d%d", &x, &y, &z);
      foo.push_back(Foo(x, y, z));
      foo.push_back(Foo(y, z, x));
      foo.push_back(Foo(z, x, y));
    }
    sort(foo.begin(), foo.end());
    unordered_map<Foo, int> dp;
    for (auto f : foo) {
      dp[f] = f.h;
      for (auto g : foo) {
        if (f==g) break;
        if ((g.x<f.x&&g.y<f.y)||(g.y<f.x&&g.x<f.y))
          dp[f] = max(dp[f], dp[g]+f.h);
      }
    }
    int ans = 0;
    for (auto f : foo) ans = max(ans, dp[f]);
    printf("%d\n", ans);
  }
  return 0;
}
