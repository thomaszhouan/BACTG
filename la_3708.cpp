#include <cstdio>
#include <cmath>
using namespace std;
int main(void) {
  int n, m;
  while (scanf("%d%d", &n, &m)==2) {
    double ans = 0;
    double k;
    for (int i=0; i<n; ++i) {
      k = floor((double)i*(m+n)/n+0.5);
      double tmp = i*(m+n)-k*n;
      ans += fabs(tmp);
    }
    ans = 10000*ans/(n*(m+n));
    printf("%.4f\n", ans);
  }
  return 0;
}
