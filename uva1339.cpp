#include <bits/stdc++.h>
using namespace std;

int cnt[2][26];
char s[2][2000];
int main() {
  while (scanf("%s", s[0])==1) {
    scanf("%s", s[1]);
    memset(cnt, 0, sizeof(cnt));
    for (int i=0; i<2; ++i) {
      for (char *p=s[i]; *p; ++p)
        ++cnt[i][*p-'A'];
      sort(cnt[i], cnt[i]+26);
    }
    bool ok = true;
    for (int i=0; i<26; ++i) if (cnt[0][i]!=cnt[1][i]) {
      ok = false; break;
    }
    printf("%s\n", ok?"YES":"NO");
  }
  return 0;
}
