#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int SIGMA = 26;
const int MAXLEN = 250000+10;
struct State {
  int len, link;
  int next[SIGMA];
};
struct SAM {
  State st[MAXLEN<<1];
  int sz, last;
  void init() {
    sz = 1, last = 0;
    st[0].len = 0;
    st[0].link = -1;
    memset(st[0].next, -1, sizeof(st[0].next));
  }
  void add(int x) {
    int cur = sz++, p = last;
    st[cur].len = st[last].len+1;
    memset(st[cur].next, -1, sizeof(st[cur].next));
    for (; p!=-1 && st[p].next[x]<0; p=st[p].link)
      st[p].next[x] = cur;
    if (p==-1) st[cur].link = 0;
    else {
      int q = st[p].next[x];
      if (st[q].len == st[p].len+1) st[cur].link = q;
      else {
        int clone = sz++;
        memcpy(st[clone].next, st[q].next, sizeof(st[q].next));
        st[clone].link = st[q].link;
        st[clone].len = st[p].len+1;
        st[cur].link = st[q].link = clone;
        for (; p!=-1 && st[p].next[x]==q; p=st[p].link)
          st[p].next[x] = clone;
      }
    }
    last = cur;
  }
};
SAM sam;
char S[MAXLEN], T[MAXLEN];
int main(void) {
  scanf("%s%s", S, T);
  sam.init();
  for (char *p=S; *p; ++p) sam.add(*p-'a');
  int maxl=0, l=0, v=0;
  for (char *p=T; *p; ++p) {
    while (v && sam.st[v].next[*p-'a']<0)
      v = sam.st[v].link, l = sam.st[v].len;
    if (sam.st[v].next[*p-'a']>=0)
      v = sam.st[v].next[*p-'a'], ++l;
    maxl = max(maxl, l);
  }
  printf("%d\n", maxl);
  return 0;
}
