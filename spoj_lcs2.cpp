#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int SIGMA = 26;
const int MAXLEN = 1e5+100;
void Min(int &a, int b) {if (a>b) a=b;}
void Max(int &a, int b) {if (a<b) a=b;}
struct State {
  int len, link;
  int next[SIGMA];
};
struct SAM {
  State st[MAXLEN<<1];
  int cnt[MAXLEN<<1], b[MAXLEN<<1];
  int dp[MAXLEN<<1], num[MAXLEN<<1];
  int sz, last;
  void init() {
    sz = 1, last = 0;
    st[0].len = 0;
    st[0].link = -1;
    memset(st[0].next, -1, sizeof(st[0].next));
    memset(dp, 0x3f, sizeof(dp));
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
  void sort() {
    memset(cnt, 0, sizeof(cnt));
    for (int i=0; i<sz; ++i) ++cnt[st[i].len];
    for (int i=1; i<sz; ++i) cnt[i] += cnt[i-1];
    for (int i=0; i<sz; ++i) b[--cnt[st[i].len]] = i;
  }
  void update() {
    for (int i=sz-1; i>=0; --i) {
      int x = b[i];
      Min(num[x], st[x].len);
      Min(dp[x], num[x]);
      if (st[x].link>=0) Max(num[st[x].link], num[x]);
    }
  }
};
SAM sam;

char S[MAXLEN];
int main(void) {
  sam.init();
  scanf("%s", S);
  for (char *p=S; *p; ++p) sam.add(*p-'a');
  sam.sort();
  while (scanf("%s", S)==1) {
    int l=0, v=0;
    for (int i=0; i<sam.sz; ++i) sam.num[i] = 0;
    for (char *p=S; *p; ++p) {
      char ch = *p-'a';
      while (v && sam.st[v].next[ch]<0)
        v = sam.st[v].link, l = sam.st[v].len;
      if (sam.st[v].next[ch]>=0)
        v = sam.st[v].next[ch], ++l;
      Max(sam.num[v], l);
    }
    sam.update();
  }
  int ans = 0;
  for (int i=0; i<sam.sz; ++i) Max(ans, sam.dp[i]);
  printf("%d\n", ans);
  return 0;
}
