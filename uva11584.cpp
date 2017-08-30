#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> ii;
const int MAXN = 1005;
const int INF = 0x3f3f3f3f;
char s[MAXN];
int dp[MAXN];

int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    scanf("%s", s);
    int n=strlen(s);
    vector<ii> a;
    for (int c=0; c<n; ++c) {
      int l=c, r=c;
      while (l>=0&&r<n&&s[l]==s[r]) {
        a.push_back(make_pair(l, r));
        --l, ++r;
      }
    }
    for (int c=0; c<n-1; ++c) {
      int l=c, r=c+1;
      while (l>=0&&r<n&&s[l]==s[r]) {
        a.push_back(make_pair(l, r));
        --l, ++r;
      }
    }
    sort(a.begin(), a.end());
    memset(dp, 0x3f, sizeof(dp));
    int k = 0;
    while (k<a.size()&&a[k].first==0)
      dp[a[k++].second]=1;
    for (int i=0; i<n; ++i) {
      while (k<a.size()&&a[k].first==i+1) {
        int j=a[k++].second;
        dp[j]=min(dp[j], 1+dp[i]);
      }
    }
    printf("%d\n", dp[n-1]);
  }
  return 0;
}
