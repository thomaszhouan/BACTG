#include <bits/stdc++.h>
using namespace std;

#define ALL(x) (x).begin(), (x).end()
typedef long long ll;
const int MAXN = 1005;
struct Box {
  int x1, x2, y1, y2, z1, z2;
  Box(int x1, int x2, int y1, int y2, int z1, int z2)
    : x1(x1), x2(x2), y1(y1), y2(y2), z1(z1), z2(z2) {}
};
struct Seg {
  int l, r, y, flag;
  Seg(int l, int r, int y, int flag)
    : l(l), r(r), y(y), flag(flag) {}
  bool operator<(const Seg &rhs) const {
    return make_pair(y, flag)<make_pair(rhs.y, rhs.flag);
  }
};
int num[MAXN<<3], n;
ll len[MAXN<<3][3];
vector<Box> B;
vector<Seg> seg;
vector<int> X;

void maintain(int p, int L, int R) {
  for (int i=0; i<min(3,num[p]); ++i) len[p][i]=X[R]-X[L];
  for (int i=min(3,num[p]); i<3; ++i)
    len[p][i] = R-L>1?len[p<<1][i-num[p]]+len[p<<1|1][i-num[p]]:0;
}
void update(int p, int L, int R, int uL, int uR, int f) {
  if (uR<=L || R<=uL) return;
  if (uL<=L && R<=uR) {
    num[p] += f;
    maintain(p, L, R);
    return;
  }
  int M = (L+R)>>1;
  update(p<<1, L, M, uL, uR, f);
  update(p<<1|1, M, R, uL, uR, f);
  maintain(p, L, R);
}
int main(void) {
  int Z, kase = 0; scanf("%d", &Z);
  while (Z--) {
    printf("Case %d: ", ++kase);
    ll vol = 0;
    scanf("%d", &n); B.clear();
    for (int i=0; i<n; ++i) {
      int x1, x2, y1, y2, z1, z2;
      scanf("%d%d%d%d%d%d", &x1, &y1, &z1, &x2, &y2, &z2);
      B.push_back(Box(x1,x2,y1,y2,z1,z2));
    }
    for (int z=-500; z<=499; ++z) {
      X.clear(), seg.clear();
      for (auto &b : B) {
        if (z<b.z1 || z>=b.z2) continue;
        seg.push_back(Seg(b.x1, b.x2, b.y1, 1));
        seg.push_back(Seg(b.x1, b.x2, b.y2, -1));
        X.push_back(b.x1), X.push_back(b.x2);
      }
      if (X.empty()) continue;
      sort(ALL(X)), sort(ALL(seg));
      X.erase(unique(ALL(X)), X.end());

      // seg-tree
      memset(num, 0, sizeof(num));
      memset(len, 0, sizeof(len));
      int xs, xe;
      xs = lower_bound(ALL(X), seg[0].l)-X.begin();
      xe = lower_bound(ALL(X), seg[0].r)-X.begin();
      update(1, 0, X.size()-1, xs, xe, seg[0].flag);
      for (int i=1; i<seg.size(); ++i) {
        vol += (ll)len[1][2]*(seg[i].y-seg[i-1].y);
        xs = lower_bound(ALL(X), seg[i].l)-X.begin();
        xe = lower_bound(ALL(X), seg[i].r)-X.begin();
        update(1, 0, X.size()-1, xs, xe, seg[i].flag);
      }
    }
    printf("%lld\n", vol);
  }
  return 0;
}
