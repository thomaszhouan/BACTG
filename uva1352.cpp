#include <cstdio>
#include <cstring>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

int q[8][3]={
  {0,1,2},{3,1,0},{5,1,3},{2,1,5},
  {0,2,4},{2,5,4},{5,3,4},{3,0,4}};
int p[24][6];
#define REP(i,n) for(int i=0; i<(n); ++i)
void init(void) {
  int cnt=0;
  REP(i,8) REP(j,3) {
    REP(k,3) {
      p[cnt][k]=q[i][(j+k)%3];
      p[cnt][5-k]=5-p[cnt][k];
    }
    ++cnt;
  }
}

int main(void) {
  init();
  int n; char str[100];
  int a[4][6], b[4][6];
  int u[3];
  while (scanf("%d", &n), n) {
    int cnt=0;
    unordered_map<string, int> m;
    REP(i,n) REP(j,6) {
      scanf("%s", str);
      string s(str);
      if (m.find(s)==m.end()) m[s]=cnt++;
      a[i][j]=m[s];
      if (i==n-1) b[i][j]=m[s];
    }
    int ans=-1;
    int X=1; REP(i,n-1) X*=24;
    int g[100];
    REP(x,X) {
      int tmp=x;
      REP(i,n-1) {u[i]=tmp%24; tmp/=24;}
      REP(i,n-1) REP(j,6) b[i][j]=a[i][p[u[i]][j]];
      int tot=0, M;
      REP(j,6) {
        memset(g, 0, sizeof(g));
        M=0;
        REP(i,n) M=max(M, ++g[b[i][j]]);
        tot += n-M;
      }
      if (ans<0||ans>tot) ans=tot;
    }
    printf("%d\n", ans);
  }
  return 0;
}
