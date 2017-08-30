#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
const int MAXM = 105;
const int MAXN = 8+5;

unordered_map<int, pair<ll, int> > dp[MAXM];
unordered_map<int, int> ID;
vector<vector<ii> > sell, buy;
vector<string> name;
ll price[MAXM][MAXN];
ll limit[MAXN], L, n, m, C;
double c;
char buf[200];
int POW10[] = {1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};

ll toll(double x) {
  return (ll)(x*100+0.1);
}

void dfs(int state) {
  if (ID.count(state)) return;
  int a[MAXN], sum=0, tmp=state;
  int cnt = ID.size();
  ID[state] = cnt;
  sell.push_back(vector<ii>());
  buy.push_back(vector<ii>());
  for (int i=1; i<=n; ++i) {
    a[i]=tmp%10, sum+=a[i];
    tmp/=10;
  }
  for (int i=1; i<=n; ++i) {
    if (a[i]) { //sell
      int new_state = state-POW10[i-1];
      dfs(new_state);
      sell[ID[state]].push_back(make_pair(i, ID[new_state]));
    }
    if (a[i]<limit[i]&&sum<L) { // buy
      int new_state = state+POW10[i-1];
      dfs(new_state);
      buy[ID[state]].push_back(make_pair(i, ID[new_state]));
    }
  }
}

void update(int s, int k, ll money, int op) {
  if (money<0) return;
  bool flag = !dp[k].count(s) || dp[k][s].first<money;
  if (flag) dp[k][s] = make_pair(money, op);
}

void print_ans(int state, int k) {
  if (k==0) return;
  int a[MAXN]; memset(a, 0, sizeof(a));
  int tmp = state;
  for (int i=1; i<=n; ++i) a[i]=tmp%10, tmp/=10;
  int op = dp[k][ID[state]].second;
  if (op>0) --a[op];
  else if (op<0) ++a[-op];
  int new_state = 0;
  for (int i=1; i<=n; ++i) new_state += POW10[i-1]*a[i];
  print_ans(new_state, k-1);
  if (op>0) printf("BUY %s\n", name[op].c_str());
  else if (op<0) printf("SELL %s\n", name[-op].c_str());
  else printf("HOLD\n");
}

int main(void) {
  bool is_first = true;
  while (scanf("%lf%lld%lld%lld\n", &c, &m, &n, &L)==4) {
    if (is_first) is_first = false;
    else printf("\n");
    C = toll(c);
    name.clear(); name.push_back("");
    for (int i=1; i<=n; ++i) {
      ll tmp;
      scanf("%s%lld%lld", buf, &tmp, limit+i);
      string s(buf); name.push_back(s);
      for (int j=1; j<=m; ++j)
        scanf("%lf", &c), price[j][i] = toll(c)*tmp;
    }

    ID.clear(), sell.clear(), buy.clear();
    dfs(0);
    for (int i=0; i<=m; ++i) dp[i].clear();
    dp[0][0] = make_pair(C, 0);
    for (int i=1; i<=m; ++i) for (auto item : dp[i-1]) {
      int s = item.first;
      ll money = item.second.first;
      update(s, i, money, 0);
      for (auto x : sell[s]) update(x.second, i, money+price[i][x.first], -x.first);
      for (auto x : buy[s]) update(x.second, i, money-price[i][x.first], x.first);
    }
    ll ans = dp[m][0].first;
    printf("%lld.%02lld\n", ans/100, ans%100);
    print_ans(0, m);
  }
  return 0;
}
