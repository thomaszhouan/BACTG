#include <cstdio>
const int MAXN = 1e5+10;
int a[MAXN];

int main(void) {
  int n, S;
  while (scanf("%d%d", &n, &S)==2) {
    for (int i=0; i<n; ++i) scanf("%d", a+i);
    int l=0, r=0, s=0;
    int ans = 0;
    for (;;) {
      while (s<S&&r<n) s+=a[r++];
      if (s<S) break;
      while (s>=S&&l<r) s-=a[l++];
      int tmp = r-l+1;
      if (!ans||ans>tmp) ans = tmp;
    }
    printf("%d\n", ans);
  }
  return 0;
}
