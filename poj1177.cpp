#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define ALL(x) (x).begin(), (x).end()

const int MAXN = 5005;
const int INF = 0x3f3f3f3f;
struct Seg {
  int l, r, h, flag;
  Seg(int l, int r, int h, int flag)
    : l(l), r(r), h(h), flag(flag) {}
  bool operator<(const Seg &rhs) const {
    if (h!=rhs.h) return h<rhs.h;
    return flag > rhs.flag;
  }
};
int len[MAXN<<3], cnt[MAXN<<3], num[MAXN<<3], n;
int left[MAXN<<3], right[MAXN<<3];
vector<int> X;
vector<Seg> seg;

int abs(int x) {return x<0?-x:x;}
void maintain(int p, int L, int R) {
  if (num[p]) {
    len[p] = X[R+1]-X[L], cnt[p] = 1;
    left[p] = right[p] = 1;
  }
  else if (L<R) {
    len[p] = len[p<<1]+len[p<<1|1];
    cnt[p] = cnt[p<<1]+cnt[p<<1|1]-(right[p<<1]&left[p<<1|1]);
    left[p] = left[p<<1], right[p] = right[p<<1|1];
  }
  else len[p] = cnt[p] = left[p] = right[p] = 0;
}
void update(int p, int L, int R, int uL, int uR, int f) {
  if (R<uL || uR<L) return;
  if (uL<=L && R<=uR) {
    num[p] += f;
    maintain(p, L, R);
    return;
  }
  int M = (L+R)>>1;
  update(p<<1, L, M, uL, uR, f);
  update(p<<1|1, M+1, R, uL, uR, f);
  maintain(p, L, R);
}
int main(void) {
  scanf("%d", &n);
  for (int i=0; i<n; ++i) {
    int l, r, d, u; scanf("%d%d%d%d", &l, &d, &r, &u);
    X.push_back(l), X.push_back(r);
    seg.push_back(Seg(l, r, d, 1));
    seg.push_back(Seg(l, r, u, -1));
  }
  sort(ALL(X)), sort(ALL(seg));
  X.erase(unique(ALL(X)), X.end());
  int ans = 0, last_h = -INF, last_len = 0;
  for (int i=0; i<seg.size(); ++i) {
    Seg &s = seg[i];
    ans += (s.h-last_h)*cnt[1]*2, last_h = s.h;
    int xs = lower_bound(ALL(X), s.l)-X.begin();
    int xe = lower_bound(ALL(X), s.r)-X.begin();
    update(1, 0, X.size()-1, xs, xe-1, s.flag);
    ans += abs(last_len-len[1]), last_len = len[1];
  }
  printf("%d\n", ans);
  return 0;
}
