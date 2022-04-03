// Problem: G - Foreign Friends
// Contest: AtCoder - AtCoder Beginner Contest 245
// URL: https://atcoder.jp/contests/abc245/tasks/abc245_g
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO \
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
#ifdef BACKLIGHT
#include "debug.h"
#else
#define logd(...) ;
#endif

using i64 = int64_t;
using u64 = uint64_t;

void solve_case(int Case);

int main() {
  CPPIO;
  int T = 1;
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

struct Edge {
  int v;
  int w;
  Edge() {}
  Edge(int _v, int _w) : v(_v), w(_w) {}
};

struct Node {
  int u;
  i64 w;
  int t;
  Node() {}
  Node(int _u, i64 _w, int _t) : u(_u), w(_w), t(_t) {}
  bool operator<(const Node& node) const { return w > node.w; }
};

void solve_case(int Case) {
  int n, m, k, l;
  std::cin >> n >> m >> k >> l;

  std::vector<int> a(n);
  for (int i = 0; i < n; ++i)
    std::cin >> a[i];

  std::vector<int> b(l);
  for (int i = 0; i < l; ++i) {
    std::cin >> b[i];
    --b[i];
  }

  std::vector<std::vector<Edge>> g(n);
  int u, v, w;
  for (int i = 0; i < m; ++i) {
    std::cin >> u >> v >> w;
    --u, --v;
    g[u].push_back(Edge(v, w));
    g[v].push_back(Edge(u, w));
  }

  std::vector<i64> d1(n, INT64_MAX), d2(n, INT64_MAX);
  std::vector<i64> t1(n, -1);
  std::vector<int> d(n, -1);
  std::priority_queue<Node> q;
  for (int i = 0; i < l; ++i) {
    q.push(Node(b[i], 0, a[b[i]]));
  }
  while (!q.empty()) {
    auto [u, cost, type] = q.top();
    q.pop();

    if (d[u] == -1) {
      d1[u] = cost;
      t1[u] = type;
      d[u] = -2;
    } else if (d[u] == -2 && type != t1[u]) {
      d2[u] = cost;
      d[u] = -3;
    } else {
      continue;
    }

    for (auto [v, weight] : g[u]) {
      q.push(Node(v, cost + weight, type));
    }
  }
  for (int i = 0; i < n; ++i) {
    if (d1[i] == INT64_MAX) {
      d1[i] = -1;
      t1[i] = -1;
    }
    if (d2[i] == INT64_MAX) {
      d2[i] = -1;
    }
  }

  for (int i = 0; i < n; ++i) {
    std::cout << (t1[i] != a[i] ? d1[i] : d2[i]) << " \n"[i == n - 1];
  }
}