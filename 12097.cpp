#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAXN = 1e4+10;
const double PI = 2*acos(0);
double s[MAXN];

int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    int n, f; scanf("%d%d", &n, &f);
    double R = 0, L=0;
    for (int i=0; i<n; ++i) scanf("%lf", s+i), R=max(R, s[i]);
    R = PI*R*R;
    for (int i=0; i<n; ++i) s[i]=PI*s[i]*s[i];
    while (R-L>1e-5) {
      double M=(R+L)/2; int cnt=0;
      for (int i=0; i<n; ++i) cnt += floor(s[i]/M);
      if (cnt>=f+1) L=M; else R=M;
    }
    printf("%f\n", L);
  }
  return 0;
}
