// Problem: F - Endless Walk
// Contest: AtCoder - AtCoder Beginner Contest 245
// URL: https://atcoder.jp/contests/abc245/tasks/abc245_f
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

void solve_case(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> r(n);
  std::vector<int> indeg(n, 0);
  for (int i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    --u, --v;
    ++indeg[u];
    r[v].push_back(u);
  }

  int ans = n;
  std::queue<int> q;
  for (int i = 0; i < n; ++i) {
    if (indeg[i] == 0) {
      q.push(i);
    }
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    --ans;
    for (int v : r[u]) {
      --indeg[v];
      if (indeg[v] == 0) {
        q.push(v);
      }
    }
  }
  std::cout << ans << "\n";
}