#include <bits/stdc++.h>
using namespace std;

struct Node {
  int time, fa;
  string name;
  Node(const string &str, int time, int id)
    : name(str), time(time), fa(id) {}
  bool operator<(const Node &rhs) const {
    if (fa!=rhs.fa) return fa<rhs.fa;
    return time<rhs.time;
  }
};
vector<Node> node;
int find(int u) {
  if (node[u].fa==u) return u;
  return node[u].fa = find(node[u].fa);
}
void merge(int u, int v) {
  int fu = find(u), fv = find(v);
  if (fu != fv) {
    if (node[fu].time > node[fv].time)
      swap(fu, fv);
    node[fv].fa = fu;
  }
}
vector<int> user;
unordered_map<string, int> str_id;
int get_id(const string &str, int time) {
  if (str_id.count(str)) return str_id[str];
  int tmp = str_id.size();
  node.push_back(Node(str, time, tmp));
  return str_id[str] = tmp;
}
int n;
const int MAXLEN = 1e6;
char buf[MAXLEN+10];
int main(void) {
  scanf("%d", &n);
  int t = 0;
  for (int i=0; i<n; ++i) {
    scanf("%s", buf);
    int u = get_id(buf, t++);
    user.push_back(u);
    int nv; scanf("%d", &nv);
    for (int j=0; j<nv; ++j) {
      scanf("%s", buf);
      int v = get_id(buf, t++);
      merge(u, v);
    }
  }
  vector<Node> ans;
  for (auto u : user) find(u);
  for (auto u : user) ans.push_back(node[u]);
  sort(ans.begin(), ans.end());
  for (int u=0; u<n; ++u) {
    printf("%s", ans[u].name.c_str());
    if (u<n-1 && ans[u].fa==ans[u+1].fa) putchar(' ');
    else putchar('\n');
  }
  return 0;
}
