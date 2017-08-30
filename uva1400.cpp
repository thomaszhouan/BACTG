#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
const int MAXN = 5e5+10;
int tab[MAXN][20][2], n, m;
ii tab1[MAXN][20];
ll a, s[MAXN];
ll sum(ii item) {return s[item.second]-s[item.first];}

ii better(ii item1, ii item2) {
  ll s1 = sum(item1), s2 = sum(item2);
  if (s1>s2) return item1;
  if (s1<s2) return item2;
  return min(item1, item2);
}
void build(void) {
  for (int i=0; i<=n; ++i)
    tab[i][0][0] = tab[i][0][1] = i;
  for (int k=1; (1<<k)<=n+1; ++k)
    for (int i=0; i+(1<<k)-1<=n; ++i) {
      int s1, s2;
      s1 = tab[i][k-1][0], s2 = tab[i+(1<<(k-1))][k-1][0];
      tab[i][k][0] = s[s1]<=s[s2]?s1:s2;
      s1 = tab[i][k-1][1], s2 = tab[i+(1<<(k-1))][k-1][1];
      tab[i][k][1] = s[s1]>=s[s2]?s1:s2;
    }
  for (int i=0; i+1<=n; ++i) tab1[i][1] = make_pair(i, i+1);
  for (int k=2; (1<<k)<=n+1; ++k)
    for (int i=0; i+(1<<k)-1<=n; ++i) {
      ii item1 = tab1[i][k-1], item2 = tab1[i+(1<<(k-1))][k-1];
      ii item3 = make_pair(tab[i][k-1][0], tab[i+(1<<(k-1))][k-1][1]);
      tab1[i][k] = better(item1, better(item2, item3));
    }
}
int query(int L, int R, int flag) { // 0: min 1: max
  int k = 0;
  while ((1<<(k+1))<=R-L+1) ++k;
  int ans1 = tab[L][k][flag], ans2 = tab[R-(1<<k)+1][k][flag];
  if (flag==0) return s[ans1]<=s[ans2]?ans1:ans2;
  else return s[ans1]>=s[ans2]?ans1:ans2;
}
ii query1(int L, int R) {
  int k=0;
  while ((1<<(k+1))<=R-L+1) ++k;
  ii item1 = tab1[L][k], item2 = tab1[R-(1<<k)+1][k];
  ii ret = better(item1, item2);
  if ((1<<k)<R-L+1) {
    ii item3 = make_pair(query(L, R-(1<<k), 0), query(L+(1<<k), R, 1));
    ret = better(ret, item3);
  }
  return ret;
}

int main(void) {
  int kase = 0;
  while (scanf("%d%d", &n, &m)==2) {
    printf("Case %d:\n", ++kase);
    s[0] = 0;
    for (int i=1; i<=n; ++i) scanf("%lld", &a), s[i] = s[i-1]+a;
    build();
    for (int i=0; i<m; ++i) {
      int u, v; scanf("%d%d", &u, &v);
      ii item = query1(u-1, v);
      printf("%d %d\n", item.first+1, item.second);
    }
  }
  return 0;
}
