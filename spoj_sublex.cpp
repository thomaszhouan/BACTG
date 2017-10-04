#include <cstdio>
#include <cstring>
using namespace std;

const int MAXLEN = 300000+10;
const int SIGMA = 26;
typedef long long ll;
struct State {
  int len, link;
  ll cnt;
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
    st[0].cnt = 1;
    memset(st[0].next, -1, sizeof(st[0].next));
  }
  void add(int x) {
    int cur = sz++, p = last;
    st[cur].len = st[last].len+1;
    st[cur].cnt = 1;
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
        st[cur].link = st[q].link = clone;
        st[clone].len = st[p].len+1;
        st[clone].cnt = 1;
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
    sort();
    for (int i=sz-1; i>=0; --i) {
      int p = b[i];
      for (int x=0; x<SIGMA; ++x) if (st[p].next[x]>=0)
        st[p].cnt += st[st[p].next[x]].cnt;
    }
  }
  void solve(ll K) {
    for (int p=0; K; ) {
      for (int x=0; x<SIGMA; ++x) if (st[p].next[x]>=0) {
        int q = st[p].next[x];
        if (st[q].cnt<K) K-=st[q].cnt;
        else {
          --K;
          putchar(x+'a');
          p = q;
          break;
        }
      }
    }
    putchar('\n');
  }
};
SAM sam;

char S[MAXLEN];
int main(void) {
  scanf("%s", S);
  sam.init();
  for (char *p=S; *p; ++p) sam.add(*p-'a');
  sam.get_cnt();
  int q; ll K; scanf("%d", &q);
  while (q--) scanf("%lld", &K), sam.solve(K);
  return 0;
}
