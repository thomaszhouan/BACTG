#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

void Max(int &a, int b) {if (a<b) a=b;}
const int MAXLEN = 250000+10;
const int SIGMA = 26;
struct State {
  int len, link, cnt;
  int next[SIGMA];
};
struct SAM {
  State st[MAXLEN<<1];
  int cnt[MAXLEN<<1], b[MAXLEN<<1];
  int sz, last;
  void init() {
    sz = 1, last = 0;
    st[0].len = 0;
    st[0].link = -1;
    st[0].cnt = 0;
    memset(st[0].next, -1, sizeof(st[0].next));
  }
  void add(int x) {
    int cur = sz++, p = last;
    st[cur].len = st[last].len+1, st[cur].cnt = 1;
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
        st[clone].cnt = 0;
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
  void get_cnt() {
    for (int i=sz-1; i; --i) {
      int x = b[i];
      st[st[x].link].cnt += st[x].cnt;
    }
  }
};
SAM sam;

char S[MAXLEN];
int dp[MAXLEN];
int main(void) {
  sam.init();
  scanf("%s", S);
  int n=0;
  for (char *p=S; *p; ++p, ++n) sam.add(*p-'a');
  sam.sort(), sam.get_cnt();
  memset(dp, 0, sizeof(dp));
  for (int i=0; i<sam.sz; ++i) Max(dp[sam.st[i].len], sam.st[i].cnt);
  for (int i=n-1; i; --i) Max(dp[i], dp[i+1]);
  for (int i=1; i<=n; ++i) printf("%d\n", dp[i]);
  return 0;
}
