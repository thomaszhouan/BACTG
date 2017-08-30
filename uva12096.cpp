#include <bits/stdc++.h>
using namespace std;
typedef set<int> Set;
map<Set, int> ID;
vector<Set> a;
vector<int> s;
char buf[100];

int getID(const Set &x) {
  if (ID.count(x)) return ID[x];
  a.push_back(x);
  int tmp = ID.size();
  return ID[x] = tmp;
}

#define ALL(x) x.begin(), x.end()
#define INS(x) inserter(x, x.begin())

int main(void) {
  int Z; scanf("%d", &Z);
  while (Z--) {
    ID.clear(), a.clear(), s.clear();
    int n; scanf("%d", &n);
    for (int i=0; i<n; ++i) {
      scanf("%s", buf);
      if (buf[0]=='P') s.push_back(getID(Set()));
      else if (buf[0]=='D') s.push_back(s.back());
      else {
        Set x1 = a[s.back()]; s.pop_back();
        Set x2 = a[s.back()]; s.pop_back();
        Set x;
        if (buf[0]=='U') set_union(ALL(x1), ALL(x2), INS(x));
        else if (buf[0]=='I') set_intersection(ALL(x1), ALL(x2), INS(x));
        else {x=x2; x.insert(getID(x1));}
        s.push_back(getID(x));
      }
      printf("%d\n", (int)a[s.back()].size());
    }
    printf("***\n");
  }
  return 0;
}
