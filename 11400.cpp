#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 1005;
struct Foo {
  int v, k, c, l;
  Foo(int v, int k, int c, int l)
    : v(v), k(k), c(c), l(l) {}
  bool operator<(const Foo &f) const {return v<f.v;}
};
int dp[MAXN];

int main(void) {
  int n;
  while (scanf("%d", &n), n) {
    vector<Foo> f;
    for (int i=0; i<n; ++i) {
      int v, k, c, l; scanf("%d%d%d%d", &v, &k, &c, &l);
      f.push_back(Foo(v, k, c, l));
    }
    sort(f.begin(), f.end());
    dp[0] = f[0].k+f[0].c*f[0].l;
    for (int i=1; i<n; ++i) {
      int s=f[i].l, tmp=dp[i-1]+s*f[i].c, cur=tmp;
      for (int j=i-1; j>=0; --j) {
        s+=f[j].l;
        tmp=(j?dp[j-1]:0)+s*f[i].c; cur=min(cur, tmp);
      }
      dp[i]=f[i].k+cur;
    }
    printf("%d\n", dp[n-1]);
  }
  return 0;
}
