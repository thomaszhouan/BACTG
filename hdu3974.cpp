#include <bits/stdc++.h>
using namespace std;

struct Range {
  int l, r;
  Range(int l=-1, int r=-1): l(l), r(r) {}
};
const int MAXN = 5e4+10;
int task[MAXN<<2], cnt, n, q;
Range range[MAXN];
vector<int> e[MAXN];
char foo[MAXN];

void pushdown(int p, int L, int R) {
  if (L==R || task[p]<0) return;
  task[2*p] = task[p];
  task[2*p+1] = task[p];
  task[p] = -1;
}
void update(int p, int L, int R, const Range &u, int v) {
  pushdown(p, L, R);
  if (R<u.l || u.r<L) return;
  if (u.l<=L && R<=u.r) {
    task[p] = v;
    pushdown(p, L, R);
    return;
  }
  int M = (L+R)/2;
  update(2*p, L, M, u, v);
  update(2*p+1, M+1, R, u, v);
}
int query(int p, int L, int R, int x) {
  pushdown(p, L, R);
  if (L==R) return task[p];
  int M = (L+R)/2;
  if (x<=M) return query(2*p, L, M, x);
  else return query(2*p+1, M+1, R, x);
}
void dfs(int x) {
  range[x].l = ++cnt;
  for (auto y : e[x]) dfs(y);
  range[x].r = cnt;
}

int main(void) {
  int Z, kase = 0; scanf("%d", &Z);
  while (Z--) {
    printf("Case #%d:\n", ++kase);
    scanf("%d", &n);
    memset(foo, 1, sizeof(foo));
    for (int i=1; i<=n; ++i) e[i].clear();
    for (int i=0; i<n-1; ++i) {
      int u, v; scanf("%d%d", &u, &v);
      e[v].push_back(u), foo[u] = 0;
    }
    int root;
    for (int i=1; i<=n; ++i)
      if (foo[i]) {root = i; break;}
    cnt = 0;
    dfs(root);
    scanf("%d", &q);
    memset(task, -1, sizeof(task));
    while (q--) {
      char op[10]; scanf("%s", op);
      if (op[0]=='C') {
        int x; scanf("%d", &x);
        printf("%d\n", query(1, 1, n, range[x].l));
      }
      if (op[0]=='T') {
        int x, v; scanf("%d%d", &x, &v);
        update(1, 1, n, range[x], v);
      }
    }
  }
  return 0;
}
