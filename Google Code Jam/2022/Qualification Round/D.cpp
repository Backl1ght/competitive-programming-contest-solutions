// Problem: Chain Reactions
// Contest: Google Coding Competitions - Qualification Round 2022 - Code Jam
// 2022 URL:
// https://codingcompetitions.withgoogle.com/codejam/round/0000000000876ff1/0000000000a45ef7
// Memory Limit: 1024 MB
// Time Limit: 5000 ms
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
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

void solve_case(int Case) {
  std::cout << "Case #" << Case << ": ";

  int N;
  std::cin >> N;

  std::vector<int> F(N);
  for (int i = 0; i < N; ++i)
    std::cin >> F[i];

  std::vector<std::vector<int>> g(N);
  std::vector<int> P(N);
  for (int i = 0; i < N; ++i) {
    std::cin >> P[i];
    --P[i];
    if (P[i] != -1) {
      g[P[i]].push_back(i);
    }
  }

  std::vector<std::pair<int, i64>> dp(N, std::make_pair(0, 0));
  std::function<void(int)> dfs = [&](int u) -> void {
    if (g[u].size() == 0) {
      dp[u] = std::pair<int, i64>(F[u], F[u]);
      return;
    }

    int p = -1;
    for (int v : g[u]) {
      dfs(v);
      if (p == -1 || dp[v].first < dp[p].first) {
        p = v;
      }
    }

    dp[u].first = std::max(F[u], dp[p].first);
    dp[u].second = dp[u].first + dp[p].second - dp[p].first;
    for (int v : g[u]) {
      if (v != p)
        dp[u].second += dp[v].second;
    }
  };

  i64 ans = 0;
  for (int i = 0; i < N; ++i) {
    if (P[i] == -1) {
      dfs(i);
      ans += dp[i].second;
    }
  }
  logd(dp);
  std::cout << ans << "\n";
}