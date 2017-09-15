#include <bits/stdc++.h>
using namespace std;

const int SIGMA = 26;
struct Trie {
  vector< vector<int> > node;
  vector<int> val;
  int sz;

  Trie() : sz(1) {
    val.push_back(0);
    node.push_back(vector<int>(SIGMA, 0));
  }
  int id(char ch) {return ch-'a';}
  void insert(char *s, int v) {
    int u = 0;
    for (; *s; ++s) {
      int c = id(*s);
      if (!node[u][c]) {
        node.push_back(vector<int>(SIGMA, 0));
        val.push_back(0), node[u][c] = sz++;
      }
      u = node[u][c];
    }
    val[u] = v;
  }
  int find(char *s) {
    int u = 0;
    for (; *s; ++s) {
      int c = id(*s);
      if (node[u][c]) u = node[u][c];
      else return 0;
    }
    return val[u];
  }
  void dfs(int u) {
    for (int c=0; c<SIGMA; ++c) if (node[u][c])
      dfs(node[u][c]), val[u] += val[node[u][c]];
  }
};

const int MAXLEN = 20;
char buf[MAXLEN];
bool read_buf(void) {
  char *s = buf, ch;
  while ((ch = getchar())!='\n' && !feof(stdin)) *s++ = ch;
  *s = 0;
  return s!=buf;
}
int main(void) {
  Trie trie;
  while (read_buf()) trie.insert(buf, 1);
  trie.dfs(0);
  while (read_buf()) printf("%d\n", trie.find(buf));
  return 0;
}
