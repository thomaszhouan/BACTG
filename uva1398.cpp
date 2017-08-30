#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int, int> ii;
int w, h, n;
const int INF = 0x3f3f3f3f;

void get(int x, int y, int a, int b, int &s, int &e) {
  if (!a) if (x<=0||x>=w) {s=-1; return;}
  if (!b) if (y<=0||y>=h) {s=-1; return;}
  s = -INF; e = INF;
  int ss, ee;
  if (a) {
    ss = -(x*2520)/a, ee = (w-x)*2520/a; if (ss>ee) swap(ss, ee);
    s = max(ss, s), e = min(ee, e);
  }
  if (b) {
    ss = -(y*2520)/b, ee = (h-y)*2520/b; if (ss>ee) swap(ss, ee);
    s = max(ss, s), e = min(ee, e);
  }
  s = max(s, 0);
  if (s>=e) {s=-1; return;}
}

int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    scanf("%d%d%d", &w, &h, &n);
    vector<ii> u;
    for (int i=0; i<n; ++i) {
      int x, y, a, b, s, e;
      scanf("%d%d%d%d", &x, &y, &a, &b);
      get(x, y, a, b, s, e);
      if (s<0) continue;
      u.push_back(make_pair(s, 1));
      u.push_back(make_pair(e, -1));
    }
    sort(u.begin(), u.end());
    int cnt = 0, ans = 0;
    for (int i=0; i<u.size(); ++i)
      cnt += u[i].second, ans = max(ans, cnt);
    printf("%d\n", ans);
  }
  return 0;
}
