#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
struct Node {
  int x, f, cnt;
  ll sum;
  Node(int x=0) : x(x), f(-1), cnt(1), sum(x) {}
};

const int MAXN = 1e5+10;
vector<Node> a;
int id[MAXN], n, m, cnt;

int find(int u) {
  Node &p = a[u];
  if (p.f<0) return u;
  return p.f = find(p.f);
}
void merge(int u, int v) {
  int fu = find(u), fv = find(v);
  if (fu==fv) return;
  a[fu].f = fv;
  a[fv].cnt += a[fu].cnt;
  a[fv].sum += a[fu].sum;
}
void move(int p, int q) {
  int u = id[p], v = id[q];
  int fu = find(u), fv = find(v);
  if (fu==fv) return;
  --a[fu].cnt;
  a[fu].sum -= a[u].x;
  id[p] = cnt++;
  a.push_back(Node(p));
  merge(id[p], id[q]);
}
int main(void) {
  while (scanf("%d%d", &n, &m)==2) {
    a.clear(); cnt = 0;
    for (int i=1; i<=n; ++i) {
      id[i] = cnt++;
      a.push_back(Node(i));
    }
    for (int i=0; i<m; ++i) {
      int op, p, q;
      scanf("%d", &op);
      if (op==1) {
        scanf("%d%d", &p, &q);
        merge(id[p], id[q]);
      }
      if (op==2) {
        scanf("%d%d", &p, &q);
        move(p, q);
      }
      if (op==3) {
        scanf("%d", &p);
        int u = find(id[p]);
        printf("%d %lld\n", a[u].cnt, a[u].sum);
      }
    }
  }
  return 0;
}
