#include <cstdio>

int main(void) {
  int n;
  while (scanf("%d", &n)==1) {
    int cnt=0;
    while (n) n>>=1, ++cnt;
    printf("%d\n", cnt);
  }
  return 0;
}
