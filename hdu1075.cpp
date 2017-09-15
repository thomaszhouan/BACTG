#include <bits/stdc++.h>
using namespace std;

const int MAXLEN = 4000;
char buf[MAXLEN];

int main(void) {
  unordered_map<string, string> m;
  scanf("%*s");
  for (;;) {
    scanf("%s", buf);
    if (!strcmp(buf, "END")) break;
    string s1(buf);
    scanf("%s", buf); string s2(buf);
    m[s2] = s1;
  }
  scanf("%*s%*c");
  for (;;) {
    fgets(buf, MAXLEN, stdin);
    if (!strcmp(buf, "END\n")) break;
    string word;
    for (char *s=buf; *s; ++s) {
      if (isalpha(*s)) word += *s;
      else {
        if (m.count(word)) printf("%s", m[word].c_str());
        else printf("%s", word.c_str());
        word = "";
        putchar(*s);
      }
    }
  }
  return 0;
}
