#include <cstdio>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
const int MAXN = 30;
int a[MAXN];
char has[26];

int get(char *x) {
  memset(has, 0, sizeof(has));
  while (*x) has[*x-'A']=1, ++x;
  int ret=0;
  for (int i=0; i<26; ++i) ret |= has[i], ret <<= 1;
  return ret;
}

int main(void) {
  int n; char str[30];
  while (scanf("%d", &n)==1) {
    for (int i=0; i<n; ++i)
      scanf("%s", str), a[i]=get(str);
    unordered_map<int, vector<int> > used;
    int m=n/2;
    for (int x=0; x<(1<<m); ++x) {
      int tmp=x, r=0;
      vector<int> f;
      for (int i=0; i<m; ++i) {
        if (tmp&1) r^=a[i], f.push_back(i);
        tmp>>=1;
      }
      auto it=used.find(r);
      if (it==used.end()) used[r]=f;
      else if (it->second.size()<f.size()) used[r]=f;
    }
    m=n-m;
    vector<int> ans;
    for (int x=0; x<(1<<m); ++x) {
      int tmp=x, r=0;
      vector<int> f;
      for (int i=0; i<m; ++i) {
        if (tmp&1) r^=a[i+n/2], f.push_back(i+n/2);
        tmp>>=1;
      }
      auto it=used.find(r);
      if (it==used.end()) continue;
      if (it->second.size()+f.size()<=ans.size()) continue;
      ans = it->second;
      for (auto y : f) ans.push_back(y);
    }
    printf("%d\n", (int)ans.size());
    for (int i=0; i<ans.size(); ++i)
      if (i) printf(" %d", ans[i]+1); else printf("%d", ans[i]+1);
    printf("\n");
  }
  return 0;
}
