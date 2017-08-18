#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 2e4+10;
int a[MAXN], b[MAXN];

int main(void) {
  int n, m;
  while (scanf("%d%d", &n, &m)==2) {
    if (!n && !m) break;
    for (int i=0; i<n; ++i) scanf("%d", a+i);
    for (int i=0; i<m; ++i) scanf("%d", b+i);
    sort(a, a+n); sort(b, b+m);
    int k = 0, cost = 0;
    bool fail = false;
    for (int i=0; i<n; ++i) {
      while (k<m && b[k]<a[i]) ++k;
      if (k==m) {fail = true; break;}
      cost += b[k]; ++k;
    }
    if (fail) printf("Loowater is doomed!\n");
    else printf("%d\n", cost);
  }
  return 0;
}
