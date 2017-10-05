#include <bits/stdc++.h>
using namespace std;
// comparison
const double eps = 1e-10;
int dcmp(double x) {if (abs(x)<eps) return 0; return x<0?-1:1;}

// Point + Vector
struct Point {
  double x, y;
  Point(double x=0, double y=0): x(x), y(y) {}
  Point operator+(const Point &rhs) const {return Point(x+rhs.x, y+rhs.y);}
  Point operator-(const Point &rhs) const {return Point(x-rhs.x, y-rhs.y);}
  Point operator*(double a) const {return Point(a*x, a*y);}
  bool operator<(const Point &rhs) const {return x<rhs.x || (x==rhs.x && y<rhs.y);}
  bool operator==(const Point &rhs) const {return dcmp(x-rhs.x)==0 && dcmp(y-rhs.y)==0;}
  double theta(void) const {return atan2(y, x);}
  double norm(void) const {return sqrt(x*x+y*y);}
  Point rotate(double a) const {
    return Point(x*cos(a)-y*sin(a), x*sin(a)+y*cos(a));
  }
  Point normal(void) const {double L=norm(); return Point(-y/L, x/L);}
};
double dot(const Point &a, const Point &b) {return a.x*b.x+a.y*b.y;}
double angle(const Point &a, const Point &b) {return acos(dot(a, b)/(a.norm()*b.norm()));}
double cross(const Point &a, const Point &b) {return a.x*b.y-a.y*b.x;}
double area2(const Point &a, const Point &b, const Point &c) {return cross(b-a, c-a);}
// Line, p = p0+vt
struct Line {
  Point p0, v;
  Line() : p0(0,0), v(1,0) {}
  Line(const Point &p0, const Point &v) : p0(p0), v(v) {}
  // check cross(v, rhs.v)!=0
  Point intersect(const Line &rhs) const {
    Point u = p0-rhs.p0;
    double t = cross(rhs.v, u)/cross(v, rhs.v);
    return p0+v*t;
  }
  double distance(const Point &p) const {return abs(cross(p-p0, v))/v.norm();}
  Point projection(const Point &p) const {return p0+v*(dot(v, p-p0)/dot(v, v));}
};
// Segment
struct Segment {
  Point a, b;
  Segment() : a(), b(1, 0) {}
  Segment(const Point &a, const Point &b) : a(a), b(b) {}
  double distance(const Point &p) const {
    if (a==b) return (p-a).norm();
    Point v1 = b-a, v2 = p-a, v3 = p-b;
    if (dcmp(dot(v1, v2))<0) return v2.norm();
    else if (dcmp(dot(v1, v3))>0) return v3.norm();
    else return abs(cross(v1, v2))/v1.norm();
  }
  bool intersect_interior(const Segment &rhs) const {
    double c1 = cross(rhs.a-a, b-a), c2 = cross(rhs.b-a, b-a);
    double c3 = cross(a-rhs.a, rhs.b-rhs.a), c4 = cross(b-rhs.a, rhs.b-rhs.a);
    return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
  }
  // endpoint exclusive
  bool contain(const Point &p) const {
    return dcmp(cross(p-a, p-b))==0 && dcmp(dot(p-a, p-b))<0;
  }
};

int main(void) {
  int n, kase=0;
  while (scanf("%d", &n), n) {
    --n;
    printf("Case %d: ", ++kase);
    vector<Point> a;
    for (int i=0; i<=n; ++i) {
      double x, y; scanf("%lf%lf", &x, &y);
      a.push_back(Point(x, y));
    }
    vector<Segment> seg;
    vector<Line> line;
    for (int i=0; i<n; ++i) {
      seg.push_back(Segment(a[i], a[i+1]));
      line.push_back(Line(a[i], a[i+1]-a[i]));
    }
    for (int i=0; i<n; ++i) for (int j=i+1; j<n; ++j)
      if (seg[i].intersect_interior(seg[j]))
        a.push_back(line[i].intersect(line[j]));
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    int V = a.size(), E = n;
    for (int i=0; i<V; ++i) for (int j=0; j<n; ++j)
      if (seg[j].contain(a[i])) ++E;
    printf("There are %d pieces.\n", 2+E-V);
  }
  return 0;
}
