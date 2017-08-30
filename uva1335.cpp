#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN=1e5+10;
int a[MAXN], b[MAXN], r[MAXN];

int main(void) {
  int n;
  while (scanf("%d", &n), n) {
    for (int i=0; i<n; ++i) scanf("%d", r+i);
    if (n%2==0) {
      int m = 0;
      for (int i=0; i<n; ++i)
        m=max(m, r[i]+r[(i+1)%n]);
      printf("%d\n", m);
    }
    else if (n==1) printf("%d\n", r[0]);
    else {
      int L=0, R=0;
      for (int i=0; i<n; ++i) {
        L=max(L, r[i]+r[(i+1)%n]);
        R=max(R, r[i]+r[(i+1)%n]+r[(i+2)%n]);
      }
      --L;
      while (R-L>1) {
        int M=(L+R+1)>>1;
        a[0]=r[0], b[0]=0;
        for (int i=1; i<n; ++i) {
          if (i&1) {
            a[i]=min(r[0]-a[i-1], r[i]);
            b[i]=r[i]-a[i];
          } else {
            b[i]=min(M-r[0]-b[i-1], r[i]);
            a[i]=r[i]-b[i];
          }
        }
        if (a[n-1]) L=M; else R=M;
      }
      printf("%d\n", R);
    }
  }
  return 0;
}
