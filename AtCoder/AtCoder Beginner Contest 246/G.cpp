// Problem: G - Game on Tree 3
// Contest: AtCoder - AtCoder Beginner Contest 246
// URL: https://atcoder.jp/contests/abc246/tasks/abc246_g
// Memory Limit: 1024 MB
// Time Limit: 6000 ms
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
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 1; i < n; ++i)
    std ::cin >> a[i];

  std::vector<std::vector<int>> g(n);
  for (int i = 1, u, v; i < n; ++i) {
    std::cin >> u >> v;
    --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  auto check = [&](int x) -> bool {
    std::vector<int> dp(n, 0);
    std::function<void(int, int)> dfs = [&](int u, int fa) -> void {
      int c = 0;
      for (int v : g[u]) {
        if (v == fa)
          continue;
        dfs(v, u);
        c += dp[v];
      }
      dp[u] = std::max(c - 1, 0) + (a[u] > x);
    };
    dfs(0, -1);
    logd(dp);
    return (dp[0] == 0);
  };

  int l = 0, r = *std::max_element(a.begin(), a.end()), mid, ans = -1;
  while (l <= r) {
    mid = (l + r) >> 1;
    logd(l, r, mid);
    if (check(mid))
      r = mid - 1, ans = mid;
    else
      l = mid + 1;
  }
  std::cout << ans << "\n";
}