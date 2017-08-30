#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 105;
int dp[MAXN][MAXN], K[MAXN][MAXN];
char s[MAXN];

void print(int l, int r) {
  if (l>r) return;
  if (l==r) {
    switch (s[l]) {
      case '(': case ')': printf("()"); return;
      case '[': case ']': printf("[]"); return;
    }
  }
  if (K[l][r]<0) putchar(s[l]), print(l+1, r-1), putchar(s[r]);
  else print(l, K[l][r]), print(K[l][r]+1, r);
}

int main(void) {
  int Z; scanf("%d%*c%*c", &Z);
  bool flag = true;
  while (Z--) {
    char *t = s, ch; int n=0;
    while ((ch=getchar())!='\n') *t++=ch, ++n;
    getchar(); *t=0;
    if (flag) flag=false; else printf("\n");
    if (!n) {printf("\n"); continue;}
    memset(dp, 0x3f, sizeof(dp));
    for (int i=0; i<n; ++i) dp[i][i]=1;
    for (int k=1; k<n; ++k) for (int i=0; i+k<n; ++i) {
      int j=i+k;
      for (int t=i; t<j; ++t) {
        int tmp=dp[i][t]+dp[t+1][j];
        if (tmp<dp[i][j]) dp[i][j]=tmp, K[i][j]=t;
      }
      if ((s[i]=='('&&s[j]==')')||(s[i]=='['&&s[j]==']')) {
        int tmp=(j==i+1)?0:dp[i+1][j-1];
        if (tmp<dp[i][j]) dp[i][j]=tmp, K[i][j]=-1;
      }
    }
    print(0, n-1); printf("\n");
  }
  return 0;
}
