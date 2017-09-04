#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const double EPS = 1e-7;
int dp[MAXN<<1][MAXN<<1], n;
struct Rect {
  double l, r, d, u;
  Rect(double l, double r, double d, double u) : l(l), r(r), d(d), u(u) {}
};
#define ALL(x) (x).begin(), (x).end()

int main(void) {
  int kase = 0;
  while (scanf("%d", &n), n) {
    printf("Test case #%d\n", ++kase);
    vector<Rect> rect;
    vector<double> X, Y;
    for (int i=0; i<n; ++i) {
      double l, r, d, u; scanf("%lf%lf%lf%lf", &l, &d, &r, &u);
      if (l>r) swap(l, r);
      if (d>u) swap(d, u);
      rect.push_back(Rect(l, r, d, u));
      X.push_back(l), X.push_back(r);
      Y.push_back(d), Y.push_back(u);
    }
    sort(ALL(X)), sort(ALL(Y));
    X.erase(unique(ALL(X)), X.end());
    Y.erase(unique(ALL(Y)), Y.end());
    memset(dp, 0, sizeof(dp));
    for (int i=0; i<n; ++i) {
      int xs = lower_bound(ALL(X), rect[i].l)-X.begin();
      int xe = lower_bound(ALL(X), rect[i].r)-X.begin();
      int ys = lower_bound(ALL(Y), rect[i].d)-Y.begin();
      int ye = lower_bound(ALL(Y), rect[i].u)-Y.begin();
      ++dp[xs][ys], ++dp[xe][ye];
      --dp[xs][ye], --dp[xe][ys];
    }
    double ans = 0;
    for (int i=0; i<X.size()-1; ++i) for (int j=0; j<Y.size()-1; ++j) {
      if (i && j) dp[i][j] += dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1];
      else if (i) dp[i][j] += dp[i-1][j];
      else if (j) dp[i][j] += dp[i][j-1];
      if (!dp[i][j]) continue;
      ans += (X[i+1]-X[i])*(Y[j+1]-Y[j]);
    }
    printf("Total explored area: %.2f\n\n", ans+EPS);
  }
  return 0;
}
