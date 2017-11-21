#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6+10;
char s[2][maxn];
int main(void) {
  while (scanf("%s", s[0])==1) {
    scanf("%s", s[1]);
    char ok = true;
    for (char *p=s[0], *q=s[1]; *p; ++p) {
      while (*q && *q != *p) ++q;
      if (!*q) {ok = false; break;}
      else ++q;
    }
    printf("%s\n", ok?"Yes":"No");
  }
  return 0;
}
