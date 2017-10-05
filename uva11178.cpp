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

int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    Point A[3], B[3];
    for (int i=0; i<3; ++i) {
      double x, y; scanf("%lf%lf", &x, &y);
      A[i] = Point(x, y);
    }
    for (int i=0; i<3; ++i) {
      Line L(A[(i+1)%3], A[(i+2)%3]-A[(i+1)%3]);
      double a1 = angle(A[(i+2)%3]-A[(i+1)%3], A[i]-A[(i+1)%3]);
      double a2 = angle(A[(i+1)%3]-A[(i+2)%3], A[i]-A[(i+2)%3]);
      Line L1(A[(i+1)%3], L.v.rotate(a1/3));
      Line L2(A[(i+2)%3], L.v.rotate(-a2/3));
      B[i] = L1.intersect(L2);
    }
    for (int i=0; i<3; ++i) {
      if (i) putchar(' ');
      printf("%.8f %.8f", B[i].x, B[i].y);
    }
    putchar('\n');
  }
  return 0;
}
