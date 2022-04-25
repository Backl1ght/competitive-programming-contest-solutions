// Problem: Controlled Inflation
// Contest: Google Coding Competitions - Round 1B 2022 - Code Jam 2022
// URL:
// https://codingcompetitions.withgoogle.com/codejam/round/000000000087711b/0000000000accfdb
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

  int n, p;
  std::cin >> n >> p;

  std::vector<std::vector<int>> a(n + 1, std::vector<int>(p + 1));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= p; ++j)
      std::cin >> a[i][j];
    std::sort(a[i].begin() + 1, a[i].end());
  }
  logd(a);

  std::vector<std::vector<i64>> dp(n + 1, std::vector<i64>(2, INT64_MAX));
  dp[0][0] = dp[0][1] = 0;

  for (int i = 1; i <= n; ++i) {
    // inc
    dp[i][0] =
        std::min(dp[i][0], dp[i - 1][0] + std::abs(a[i][1] - a[i - 1][p]) +
                               a[i][p] - a[i][1]);
    dp[i][0] =
        std::min(dp[i][0], dp[i - 1][1] + std::abs(a[i][1] - a[i - 1][1]) +
                               a[i][p] - a[i][1]);

    // dec
    dp[i][1] =
        std::min(dp[i][1], dp[i - 1][0] + std::abs(a[i][p] - a[i - 1][p]) +
                               a[i][p] - a[i][1]);
    dp[i][1] =
        std::min(dp[i][1], dp[i - 1][1] + std::abs(a[i][p] - a[i - 1][1]) +
                               a[i][p] - a[i][1]);
    logd(i, dp[i]);
  }

  std::cout << std::min(dp[n][0], dp[n][1]) << "\n";
}