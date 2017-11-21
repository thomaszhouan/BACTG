#include <bits/stdc++.h>
using namespace std;

const int maxn = 1005;
char a[maxn];
char ch[] = {'A', 'C', 'G', 'T'};
int cnt[maxn][4];
int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    int m, n; scanf("%d%d", &m, &n);
    memset(cnt, 0, sizeof(cnt));
    for (int i=0; i<m; ++i) {
      scanf("%s", a);
      for (int j=0; j<n; ++j)
        switch (a[j]) {
          case 'A': ++cnt[j][0]; break;
          case 'C': ++cnt[j][1]; break;
          case 'G': ++cnt[j][2]; break;
          case 'T': ++cnt[j][3]; break;
        }
    }
    int sum = 0;
    for (int i=0; i<n; ++i) {
      int mx = 0, id = -1;
      for (int j=0; j<4; ++j) if (cnt[i][j]>mx)
        mx = cnt[i][j], id = j;
      sum += mx, putchar(ch[id]);
    }
    printf("\n%d\n", m*n-sum);
  }
  return 0;
}
