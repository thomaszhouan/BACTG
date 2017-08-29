#include <bits/stdc++.h>
using namespace std;

struct P {
  int x, y;
  P(int x, int y) : x(x), y(y) {}
  bool operator<(const P& p) const {
    if (x!=p.x) return x<p.x;
    return y<p.y;
  }
  bool operator==(const P& p) const {
    return x==p.x && y==p.y;
  }
  P operator+(const P& p) const {
    return P(x+p.x, y+p.y);
  }
};
int area(P a, P b, P c) {
  return (a.x*b.y+b.x*c.y+c.x*a.y-
          a.y*b.x-b.y*c.x-c.y*a.x);
}
int sgn(int x) {
  if (x>0) return 1;
  if (x<0) return -1;
  return 0;
}
bool intersect(P p1, P p2, P q1, P q2) {
  if (max(p1.x, p2.x)<min(q1.x, q2.x)) return false;
  if (max(q1.x, q2.x)<min(p1.x, p2.x)) return false;
  if (max(p1.y, p2.y)<min(q1.y, q2.y)) return false;
  if (max(q1.y, q2.y)<min(p1.y, p2.y)) return false;
  return sgn(area(p1, p2, q1))*sgn(area(p1,p2,q2))<=0
      && sgn(area(q1, q2, p1))*sgn(area(q1,q2,p2))<=0;
}
namespace std {
  template<> struct hash<P> {
    size_t operator()(const P &p) const {
      size_t res=17;
      res = res*31+hash<int>()(p.x);
      res = res*31+hash<int>()(p.y);
      return res;
    }
  };
}
int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    int s, r, w, p;
    scanf("%d%d%d%d", &s, &r, &w, &p);
    vector<P> delta;
    for (int x=-r; x<=r; ++x) for (int y=-r; y<=r; ++y)
      if (x*x+y*y<=r*r) delta.push_back(P(x, y));
    unordered_set<P> sensor;
    for (int i=0; i<s; ++i) {
      int x, y; scanf("%d%d", &x, &y);
      sensor.insert(P(x, y));
    }
    vector< pair<P, P> > wall;
    for (int i=0; i<w; ++i) {
      int x1, y1, x2, y2;
      scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
      wall.push_back(make_pair(P(x1, y1), P(x2, y2)));
    }
    for (int i=0; i<p; ++i) {
      vector<P> ans; int x, y;
      scanf("%d%d", &x, &y);
      P u(x, y);
      for (auto d : delta) if (sensor.count(u+d)) {
        P v(u+d); int cnt = 0;
        for (auto seg : wall)
          if (intersect(u, v, seg.first, seg.second)) ++cnt;
        if (r-cnt>=0 && d.x*d.x+d.y*d.y<=(r-cnt)*(r-cnt))
          ans.push_back(v);
      }
      sort(ans.begin(), ans.end());
      printf("%d", (int)ans.size());
      for (auto v : ans)
        printf(" (%d,%d)", v.x, v.y);
      printf("\n");
    }
  }
  return 0;
}
