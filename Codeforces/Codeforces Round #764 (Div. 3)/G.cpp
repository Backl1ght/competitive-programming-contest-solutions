// Problem: G. MinOr Tree
// Contest: Codeforces - Codeforces Round #764 (Div. 3)
// URL: http://codeforces.com/contest/1624/problem/G
// Memory Limit: 256 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

#define CPPIO ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

using i64 = int64_t;
using u64 = uint64_t;

void solve_case(int Case);

int main() {
  CPPIO;
  int T = 1;
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

template <typename T>
class DSU {
 private:
  int n;
  vector<int> fa;
  vector<int> size;

 public:
  DSU(int n) {
    this->n = n;
    fa.resize(n);
    size.resize(n);
    for (int i = 0; i < n; ++i) {
      fa[i] = i;
      size[i] = 1;
    }
  }

  int find(int x) { return x == fa[x] ? x : (fa[x] = find(fa[x])); }

  bool merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return false;
    fa[x] = y;
    size[y] += size[x];
    return true;
  }

  bool connected() {
    int count = 0;
    for (int i = 0; i < n; ++i) {
      if (fa[i] == i) {
        ++count;
      }
    }
    return count == 1;
  }
};

struct Edge {
  int u, v, w;
  Edge() {}
  Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
};

void solve_case(int Case) {
  int n, m;
  cin >> n >> m;

  vector<Edge> E(m);
  for (auto& [u, v, w] : E) {
    cin >> u >> v >> w;
    --u, --v;
  }

  int mask = (1 << 30) - 1;
  for (int b = 29; b >= 0; --b) {
    DSU<int> D(n);
    for (auto& [u, v, w] : E) {
      if (((w | mask) == mask) && ((w & (1 << b)) == 0)) {
        D.merge(u, v);
      }
    }
    if (D.connected()) {
      mask -= (1 << b);
    }
  }

  cout << mask << "\n";
}