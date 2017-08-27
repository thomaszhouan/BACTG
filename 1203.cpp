#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
const int MAXN = 3005;
int p[MAXN];
int main(void) {
  char buf[100];
  priority_queue<ii> q;
  for (;;) {
    scanf("%s", buf);
    if (buf[0]=='#') break;
    int a, b; scanf("%d%d", &a, &b);
    p[a] = b;
    q.push(make_pair(-b, -a));
  }
  int k; scanf("%d", &k);
  for (int i=0; i<k; ++i) {
    ii item = q.top(); q.pop();
    int a = -item.second, b = -item.first;
    printf("%d\n", a);
    q.push(make_pair(-(b+p[a]), -a));
  }
  return 0;
}
