#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e4+10;
int n, C[MAXN];
int lowbit(int x) {return x&-x;}
int sum(int x) {
  int ans = 0;
  while (x) ans+=C[x], x-=lowbit(x);
  return ans;
}
void update(int x, int v) {
  while (x<n) C[x]+=v, x+=lowbit(x);
}

int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    scanf("%d", &n);
    memset(C, 0, sizeof(C));
    for (int i=1; i<=n; ++i) update(i, 1);
    for (int i=0; i<n; ++i) {
      int k; scanf("%d", &k); ++k;
      int L = 1, R = n;
      while (L<R) {
        int M = (L+R)/2;
        if (sum(M)<k) L=M+1; else R=M;
      }
      if (i) putchar(' ');
      printf("%d", R);
      update(R, -1);
    }
    putchar('\n');
  }
  return 0;
}
