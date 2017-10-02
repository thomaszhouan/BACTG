#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
int addv[2][(MAXN+10)<<2];
void pushdown(int p, int L, int R) {
  if (L==R) return;
  addv[0][p<<1] += addv[0][p];
  addv[0][p<<1|1] += addv[0][p];
  addv[0][p] = 0;
  addv[1][p<<1] += addv[1][p];
  addv[1][p<<1|1] += addv[1][p];
  addv[1][p] = 0;
}
void update(int p, int L, int R, int uL, int uR, int v0, int v1) {
  pushdown(p, L, R);
  if (uR<L || R<uL) return;
  if (uL<=L && R<=uR) {
    addv[0][p] += v0, addv[1][p] += v1;
    pushdown(p, L, R); return;
  }
  int M = (L+R)>>1;
  update(p<<1, L, M, uL, uR, v0, v1);
  update(p<<1|1, M+1, R, uL, uR, v0, v1);
}
void query(int p, int L, int R, int u, int &v0, int &v1) {
  pushdown(p, L, R);
  if (L==R) {
    v0 = addv[0][p], v1 = addv[1][p];
    return;
  }
  int M = (L+R)>>1;
  if (u<=M) query(p<<1, L, M, u, v0, v1);
  else query(p<<1|1, M+1, R, u, v0, v1);
}
struct Node {
  int fa, l, r, cnt;
  Node(int y)
    : fa(-1), l(y), r(y), cnt(1) {}
};
vector<Node> node;
int find(int u) {
  if (node[u].fa==-1) return u;
  return node[u].fa = find(node[u].fa);
}
void merge(int u, int v) {
  int fu = find(u), fv = find(v);
  if (fu==fv) return;
  if (node[fu].l!=node[fu].r)
    update(1, 0, MAXN, node[fu].l, node[fu].r-1, -1, -node[fu].cnt);
  if (node[fv].l!=node[fv].r)
    update(1, 0, MAXN, node[fv].l, node[fv].r-1, -1, -node[fv].cnt);
  node[fu].fa = fv;
  node[fv].cnt += node[fu].cnt;
  node[fv].l = min(node[fu].l, node[fv].l);
  node[fv].r = max(node[fu].r, node[fv].r);
  if (node[fv].l!=node[fv].r)
    update(1, 0, MAXN, node[fv].l, node[fv].r-1, 1, node[fv].cnt);
}
int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    node.clear();
    memset(addv, 0, sizeof(addv));
    int n; scanf("%d", &n);
    for (int i=0; i<n; ++i) {
      int y; scanf("%*d%d", &y);
      node.push_back(Node(y));
    }
    int m; scanf("%d", &m);
    for (int i=0; i<m; ++i) {
      char op[10]; scanf("%s", op);
      if (op[0]=='r') {
        int u, v; scanf("%d%d", &u, &v);
        merge(u, v);
      }
      else {
        double y; scanf("%lf", &y);
        int v0, v1; query(1, 0, MAXN, floor(y), v0, v1);
        printf("%d %d\n", v0, v1);
      }
    }
  }
  return 0;
}
