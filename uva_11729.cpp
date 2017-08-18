#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> ii;
const int MAXN=1005;

int main(void) {
  int n, kase=0;
  while (scanf("%d", &n), n) {
    printf("Case %d: ", ++kase);
    vector<ii> x;
    for (int i=0; i<n; ++i) {
      int b, j; scanf("%d%d", &b, &j);
      x.push_back(make_pair(-j, b));
    }
    sort(x.begin(), x.end());
    int ans = 0, s = 0;
    for (int i=0; i<n; ++i)
      s += x[i].second, ans = max(ans, s-x[i].first);
    printf("%d\n", ans);
  }
  return 0;
}
