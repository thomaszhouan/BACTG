#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+10;
const int INF = 0x3f3f3f3f;
int minv[MAXN<<2], a[MAXN], n, q;
char buf[50];

void build(int p, int L, int R) {
  if (L==R) {minv[p] = a[L]; return;}
  int M = (L+R)/2;
  build(2*p, L, M);
  build(2*p+1, M+1, R);
  minv[p] = min(minv[2*p], minv[2*p+1]);
}
void update(int p, int L, int R, int x, int v) {
  if (x<L || x>R) return;
  if (L==R) {minv[p] = v; return;}
  int M = (L+R)/2;
  update(2*p, L, M, x, v);
  update(2*p+1, M+1, R, x, v);
  minv[p] = min(minv[2*p], minv[2*p+1]);
}
int query(int p, int L, int R, int qL, int qR) {
  if (qR<L || qL>R) return INF;
  if (qL<=L && R<=qR) return minv[p];
  int M = (L+R)/2;
  return min(query(2*p, L, M, qL, qR), query(2*p+1, M+1, R, qL, qR));
}
void solve() {
  char *p = buf;
  int op = *p=='q'?0:1;
  while (*p++!='(');
  vector<int> x;
  for (;;) {
    int tmp = 0;
    while (isdigit(*p)) tmp*=10, tmp+=*p-'0', ++p;
    x.push_back(tmp);
    if (*p==')') break;
    else ++p;
  }
  if (op==0) printf("%d\n", query(1, 1, n, x[0], x[1]));
  else {
    int m = x.size();
    for (int i=0; i<m; ++i)
      update(1, 1, n, x[i], a[x[(i+1)%m]]);
    int tmp = a[x[0]];
    for (int i=0; i<m-1; ++i)
      a[x[i]] = a[x[i+1]];
    a[x[m-1]] = tmp;
  }
}

int main(void) {
  scanf("%d%d", &n, &q);
  for (int i=1; i<=n; ++i) scanf("%d", a+i);
  build(1, 1, n);
  for (int i=0; i<q; ++i) {
    scanf("%s", buf);
    solve();
  }
  return 0;
}
