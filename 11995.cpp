#include <bits/stdc++.h>
using namespace std;

char flag[3];
int main(void) {
  int n;
  while (scanf("%d", &n)==1) {
    vector<int> s;
    deque<int> q;
    priority_queue<int> pq;
    memset(flag, 1, sizeof(flag));
    for (int i=0; i<n; ++i) {
      int op, x; scanf("%d%d", &op, &x);
      if (op==1) {
        if (flag[0]) s.push_back(x);
        if (flag[1]) q.push_back(x);
        if (flag[2]) pq.push(x);
      }
      if (op==2) {
        if (flag[0]) {
          if (s.empty()||s.back()!=x) flag[0] = 0;
          else s.pop_back();
        }
        if (flag[1]) {
          if (q.empty()||q.front()!=x) flag[1] = 0;
          else q.pop_front();
        }
        if (flag[2]) {
          if (pq.empty()||pq.top()!=x) flag[2] = 0;
          else pq.pop();
        }
      }
    }
    int sum = 0;
    for (int i=0; i<3; ++i) sum += flag[i]<<i;
    switch (sum) {
      case 0: printf("impossible\n"); break;
      case 1: printf("stack\n"); break;
      case 2: printf("queue\n"); break;
      case 4: printf("priority queue\n"); break;
      default: printf("not sure\n");
    }
  }
  return 0;
}
