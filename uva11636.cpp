#include <bits/stdc++.h>
using namespace std;

int main(void) {
  int n, kase = 0;
  while (scanf("%d", &n), n>0) {
    int ans = 0;
    for (;;) {
      if (n > (1<<ans)) ++ans;
      else break;
    }
    printf("Case %d: %d\n", ++kase, ans);
  }
  return 0;
}
