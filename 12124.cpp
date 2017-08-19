#include <cstdio>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXQ=1e9+10;
typedef pair<int, int> ii;

int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    int n, B; scanf("%d%d", &n, &B);
    char str[100]; int cnt=0;
    unordered_map<string, int> m;
    vector< vector<ii> > a;
    int p, q;
    for (int i=0; i<n; ++i) {
      scanf("%s%*s%d%d", str, &p, &q);
      string s(str);
      if (m.find(s)==m.end())
        m[s]=cnt++, a.push_back(vector<ii>());
      int k=m[s]; a[k].push_back(make_pair(p, q));
    }
    for (int k=0; k<cnt; ++k)
      sort(a[k].begin(), a[k].end());
    int L=0, R=MAXQ, M;
    while (R-L>1) {
      M=(L+R)/2;
      int b=0; bool ok=true;
      for (int k=0; k<cnt; ++k) {
        int j=0;
        while (j<a[k].size() && a[k][j].second<M) ++j;
        if (j==a[k].size()) {ok=false; break;}
        b += a[k][j].first;
        if (b>B) {ok=false; break;}
      }
      if (ok) L=M; else R=M;
    }
    printf("%d\n", L);
  }
  return 0;
}
