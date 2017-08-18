#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> ii;
const int MAXN = 10005;

int R[MAXN];
int main(void) {
  int Z, kase = 0; scanf("%d", &Z);
  while (Z--) {
    printf("Case #%d:\n", ++kase);
    vector<ii> state;
    vector<ii> p;
    int L, T, n; scanf("%d%d%d", &L, &T, &n);
    char str[10]; int tmp;
    for (int i=0; i<n; ++i) {
      scanf("%d%s", &tmp, str);
      if (str[0]=='L') p.push_back(make_pair(tmp, -1));
      else p.push_back(make_pair(tmp, 1));
      state.push_back(make_pair(tmp, i));
    }
    sort(state.begin(), state.end());
    for (int i=0; i<n; ++i) R[state[i].second]=i;
    for (int i=0; i<n; ++i) p[i].first += p[i].second*T;
    sort(p.begin(), p.end());
    for (int i=0; i<n; ++i) {
      int r = R[i];
      int pos = p[r].first;
      if (pos<0||pos>L) {printf("Fell off\n"); continue;}
      bool flag = false;
      if (r>0 && p[r-1].first==pos) flag = true;
      if (r<n-1 && p[r+1].first==pos) flag = true;
      printf("%d ", pos);
      if (flag) printf("Turning\n");
      else printf("%s\n", p[r].second>0?"R":"L");
    }
    printf("\n");
  }
  return 0;
}
