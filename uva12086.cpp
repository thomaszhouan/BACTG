#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5+10;
int A[MAXN], C[MAXN], n;
int lowbit(int x) {return x&-x;}
int sum(int x) {
  int res = 0;
  while (x) res += C[x], x-=lowbit(x);
  return res;
}
void add(int x, int d) {
  while (x<=n) C[x] += d, x += lowbit(x);
}
void set_val(int x, int v) {
  add(x, v-A[x]), A[x] = v;
}

int main(void) {
  int kase = 0;
  while (scanf("%d", &n), n) {
    if (kase) printf("\n");
    printf("Case %d:\n", ++kase);
    memset(C, 0, sizeof(C));
    memset(A, 0, sizeof(A));
    int tmp;
    for (int i=1; i<=n; ++i) scanf("%d", &tmp), set_val(i, tmp);
    char op[10];
    for (;;) {
      scanf("%s", op);
      int u, v;
      if (op[0]=='E') break;
      scanf("%d%d", &u, &v);
      if (op[0]=='S') set_val(u, v);
      if (op[0]=='M') printf("%d\n", sum(v)-sum(u-1));
    }
  }
  return 0;
}
