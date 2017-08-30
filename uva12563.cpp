#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXT = 1e4+10;
const int MAXN = 55;
struct Foo {
  int a, b;
  Foo(int a=0, int b=0) : a(a), b(b) {}
  bool operator<(const Foo &f) const {
    return a<f.a||(a==f.a&&b<f.b);
  }
  Foo operator+(const Foo &f) const {
    return Foo(a+f.a, b+f.b);
  }
};
Foo dp[MAXT];
int x[MAXN];

int main(void) {
  int Z, kase=0; scanf("%d", &Z);
  while (Z--) {
    printf("Case %d: ", ++kase);
    int n, T; scanf("%d%d", &n, &T);
    dp[0]=Foo(0, 0);
    for (int t=1; t<=T; ++t) dp[t]=Foo(1, 678);
    for (int i=0; i<n; ++i) scanf("%d", x+i);
    for (int i=0; i<n; ++i) for (int t=T; t>=0; --t)
      if (t>=x[i]) dp[t] = max(dp[t], dp[t-x[i]]+Foo(1, x[i]));
    Foo ans(0, 0);
    for (int t=0; t<=T; ++t) ans = max(ans, dp[t]);
    printf("%d %d\n", ans.a, ans.b);
  }
  return 0;
}
