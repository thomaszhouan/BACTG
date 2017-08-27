#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e4+10;
int f[MAXN], d[MAXN];
int find(int u) {
  if (f[u]<0) return u;
  int v = f[u];
  f[u] = find(f[u]);
  d[u] ^= d[v];
  return f[u];
}
bool merge(int u, int v, int x) {
  int fu = find(u), fv = find(v);
  if (fu==fv) return x==(d[u]^d[v]);
  if (fu>fv)
    f[fv] = fu, d[fv] = d[u]^d[v]^x;
  else
    f[fu] = fv, d[fu] = d[u]^d[v]^x;
  return true;
}
int main(void) {
  int n, q, kase = 0;;
  while (scanf("%d%d%*c", &n, &q), n) {
    printf("Case %d:\n", ++kase);
    memset(d, 0, sizeof(d));
    memset(f, -1, sizeof(f));
    int cnt = 0; bool valid = true;
    char op[10], buf[2000];
    for (int i=0; i<q; ++i) {
      scanf("%s", op);
      fgets(buf, 1000, stdin);
      if (!valid) continue;
      if (op[0]=='I') {
        ++cnt;
        int a, b, c;
        int t = sscanf(buf, "%d%d%d", &a, &b, &c);
        if (t==2) valid = merge(a, n, b);
        else valid = merge(a, b, c);
        if (!valid) printf("The first %d facts are conflicting.\n", cnt);
      }
      if (op[0]=='Q') {
        bool know = true;
        int ans = 0;
        int tmp, k;
        string str(buf);
        stringstream ss(str);
        ss >> k;
        unordered_map<int, int> f;
        for (int j=0; j<k; ++j) {
          ss >> tmp;
          int r = find(tmp);
          ans ^= d[tmp];
          if (r==n) continue;
          if (!f.count(r)) f[r] = 0;
          ++f[r];
        }
        for (auto item : f) if (item.second&1) {know=false; break;}
        if (know) printf("%d\n", ans);
        else printf("I don't know.\n");
      }
    }
    printf("\n");
  }
  return 0;
}
