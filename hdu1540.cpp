#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
const int MAXN = 5e4+10;
const ii null(-1, -1);
ii setv[MAXN<<2][2];
int des[MAXN], sp;
char good[MAXN];

void pushdown(int p, int L, int R) {
  if (setv[p]==null || L==R) return;
}
void build(int p, int L, int R) {
}
