#include <bits/stdc++.h>
using namespace std;

const int MAXN = 755;
int a[MAXN][MAXN];

struct Foo {
  int s, i;
  Foo(int s, int i) : s(s), i(i) {}
  bool operator<(const Foo &f) const {return s>f.s;}
};
void merge(int *A, int *B, int *C, int n) {
  priority_queue<Foo> q;
  for (int i=0; i<n; ++i)
    q.push(Foo(A[i]+B[0], 0));
  for (int i=0; i<n; ++i) {
    Foo f = q.top(); q.pop();
    C[i] = f.s;
    int j = f.i;
    if (j<n-1) {
      f.s += B[j+1]-B[j], ++f.i;
      q.push(f);
    }
  }
}

int main(void) {
  int k;
  while (scanf("%d", &k)==1) {
    for (int i=0; i<k; ++i) {
      for (int j=0; j<k; ++j)
        scanf("%d", &a[i][j]);
      sort(a[i], a[i]+k);
    }
    for (int i=1; i<k; ++i) merge(a[0], a[i], a[0], k);
    printf("%d", a[0][0]);
    for (int i=1; i<k; ++i) printf(" %d", a[0][i]);
    printf("\n");
  }
  return 0;
}
