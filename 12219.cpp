#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e4+5;
char buf[7*MAXN], *p;

struct Tree {
  int l, r, root;
  int lt, rt;
  Tree(int l=0, int r=0)
    : l(l), r(r), root(0),
      lt(-1), rt(-1) {
    for (int i=l; i<r; ++i)
      root = root*27+buf[i]-'a'+1;
  }
  bool operator==(const Tree &t) const {
    return root==t.root && lt==t.lt && rt==t.rt;
  }
};

namespace std {
  template<> struct hash<Tree> {
    size_t operator()(const Tree &t) const {
      size_t res = 17;
      res = res*31+hash<int>()(t.root);
      res = res*31+hash<int>()(t.lt);
      res = res*31+hash<int>()(t.rt);
      return res;
    }
  };
}

unordered_map<Tree, int> id;
Tree node[MAXN];
char vis[MAXN];
int cnt, a[MAXN];

// linear parse, don't use l/r boundary
int parse() {
  int l = p-buf;
  while (isalpha(*p)) ++p;
  int r = p-buf;
  Tree t(l, r);
  if (*p=='(') {
    ++p, t.lt=parse(), ++p, t.rt=parse(), ++p;
  }
  if (id.count(t)) return id[t];
  id[t] = cnt, node[cnt] = t;
  return cnt++;
}

void print(int x) {
  if (vis[x]) {printf("%d", a[x]); return;}
  vis[x]=1, a[x] = ++cnt;
  auto &t = node[x];
  for (int i=t.l; i<t.r; ++i) putchar(buf[i]);
  if (t.lt<0) return;
  putchar('('); print(t.lt);
  putchar(','); print(t.rt);
  putchar(')');
}

int main(void) {
  id.reserve(MAXN);
  int Z; scanf("%d", &Z);
  while (Z--) {
    scanf("%s", buf), p=buf;
    id.clear();
    cnt = 0;
    memset(vis, 0, sizeof(vis));
    int root = parse();
    cnt = 0, print(root);
    putchar('\n');
  }
  return 0;
}
