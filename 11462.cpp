#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 110;
int cnt[MAXN];
int main(void) {
  int n; 
  while (scanf("%d", &n), n) {
    int tmp;
    memset(cnt, 0, sizeof(cnt));
    for (int i=0; i<n; ++i)
      scanf("%d", &tmp), ++cnt[tmp];
    bool flag = true;
    for (int i=1; i<=100; ++i)
      for (int j=0; j<cnt[i]; ++j)
        if (flag) {flag=false; printf("%d", i);}
        else printf(" %d", i);
    printf("\n");
  }
  return 0;
}
