#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const double EPS = 1e-7;
int dp[MAXN<<1][MAXN<<1];
struct Rect {
  double L, R, U, D;
  Rect(double L, double R, double U, double D)
    : L(L), R(R), U(U), D(D) {}
};
int n;
#define ALL(x) (x).begin(), (x).end()

int main(void) {
  int Z; scanf("%d",&Z);
  while (Z--) {
    scanf("%d", &n);
    vector<Rect> rect;
    vector<double> X, Y;
    for (int i=0; i<n; ++i) {
      double l, r, u, d; scanf("%lf%lf%lf%lf", &l, &u, &r, &d);
      if (l>r) swap(l, r);
      if (u<d) swap(u, d);
      rect.push_back(Rect(l, r, u, d));
      X.push_back(l), X.push_back(r);
      Y.push_back(u), Y.push_back(d);
    }
    sort(ALL(X)), sort(ALL(Y));
    X.erase(unique(ALL(X)), X.end());
    Y.erase(unique(ALL(Y)), Y.end());
    memset(dp, 0, sizeof(dp));
    for (int i=0; i<n; ++i) {
      int xs = lower_bound(ALL(X), rect[i].L)-X.begin();
      int xe = lower_bound(ALL(X), rect[i].R)-X.begin();
      int ys = lower_bound(ALL(Y), rect[i].D)-Y.begin();
      int ye = lower_bound(ALL(Y), rect[i].U)-Y.begin();
      ++dp[xs][ys], ++dp[xe][ye];
      --dp[xs][ye], --dp[xe][ys];
    }
    double ans = 0;
    for (int i=0; i<X.size()-1; ++i) for (int j=0; j<Y.size()-1; ++j) {
      if (i && j) dp[i][j] += dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1];
      else if (i) dp[i][j] += dp[i-1][j];
      else if (j) dp[i][j] += dp[i][j-1];
      if (dp[i][j]<2) continue;
      ans += (X[i+1]-X[i])*(Y[j+1]-Y[j]);
    }
    printf("%.2f\n", ans+EPS);
  }
  return 0;
}
