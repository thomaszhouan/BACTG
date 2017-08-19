#include <cstdio>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;

int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    int n; scanf("%d", &n);
    int ans = -INF, m; scanf("%d", &m);
    for (int i=1; i<n; ++i) {
      int tmp; scanf("%d", &tmp);
      ans = max(ans, m-tmp);
      m = max(m, tmp);
    }
    printf("%d\n", ans);
  }
  return 0;
}
