#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+10;
char buf[MAXN];
int main(void) {
  while (scanf("%s", buf)==1) {
    deque<char> a, b;
    int state = 1;
    for (char *p=buf; *p; ++p) {
      if (*p=='['||*p==']') {
        while (!b.empty()) {
          char ch = b.back(); b.pop_back();
          a.push_front(ch);
        }
        state = *p=='['?0:1;
      }
      else if (state) a.push_back(*p);
      else b.push_back(*p);
    }
    for (auto ch : b) putchar(ch);
    for (auto ch : a) putchar(ch);
    putchar('\n');
  }
  return 0;
}
