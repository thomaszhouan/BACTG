#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 4e4+10;
int pL[MAXN], pR[MAXN];
int setv[MAXN<<2], n, N;
int id[MAXN];
char see[MAXN];
vector<int> g;

void pushdown(int p, int L, int R) {
  if (L==R || !setv[p]) return;
  setv[2*p]=setv[p];
  setv[2*p+1]=setv[p];
  setv[p]=0;
}
void update(int p, int L, int R, int uL, int uR, int v) {
  if (R<uL || uR<L) return;
  if (uL<=L && R<=uR) {
    setv[p] = v;
    return;
  }
  pushdown(p, L, R);
  int M = (L+R)/2;
  update(2*p, L, M, uL, uR, v);
  update(2*p+1, M+1, R, uL, uR, v);
}
void query(int p, int L, int R) {
  if (L==R) {id[L] = setv[p]; return;}
  pushdown(p, L, R);
  int M = (L+R)/2;
  query(2*p, L, M);
  query(2*p+1, M+1, R);
}
int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    g.clear();
    scanf("%d", &n);
    for (int i=1; i<=n; ++i) {
      int u, v; scanf("%d%d", &u, &v);
      pL[i] = u, pR[i] = v;
      g.push_back(u), g.push_back(v);
      g.push_back(u-1), g.push_back(v+1);
    }
    sort(g.begin(), g.end());
    vector<int>::iterator it = unique(g.begin(), g.end());
    g.resize(it-g.begin());
    N = g.size()-1;
    memset(setv, 0, sizeof(setv));
    for (int i=1; i<=n; ++i) {
      pL[i] = lower_bound(g.begin(), g.end(), pL[i])-g.begin();
      pR[i] = lower_bound(g.begin(), g.end(), pR[i])-g.begin();
      update(1, 0, N, pL[i], pR[i], i);
    }
    memset(see, 0, sizeof(see));
    int ans = 0; see[0] = 1;
    query(1, 0, N);
    for (int i=0; i<=N; ++i) {
      int x = id[i];
      if (see[x]) continue;
      see[x]=1, ++ans;
    }
    printf("%d\n", ans);
  }
  return 0;
}
