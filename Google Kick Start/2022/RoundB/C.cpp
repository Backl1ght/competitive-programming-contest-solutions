// Problem: Unlock the Padlock
// Contest: Google Coding Competitions - Round B 2022 - Kick Start 2022
// URL:
// https://codingcompetitions.withgoogle.com/kickstart/round/00000000008caa74/0000000000acef55
// Memory Limit: 1024 MB
// Time Limit: 30000 ms
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

  int n, d;
  std::cin >> n >> d;

  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }

  auto cost = [&d](int s, int t) {
    int x = std::abs(s - t);
    return std::min(x, d - x);
  };

  std::vector<std::vector<std::vector<i64>>> dp(
      n, std::vector<std::vector<i64>>(n, std::vector<i64>(2, INT64_MAX)));
  for (int i = 0; i < n; ++i) {
    dp[i][i][0] = dp[i][i][1] = 0;
  }
  for (int len = 2; len <= n; ++len) {
    for (int s = 0; s < n; ++s) {
      int e = s + len - 1;
      if (e >= n)
        break;
      dp[s][e][0] =
          std::min(dp[s][e][0], dp[s + 1][e][0] + cost(a[s + 1], a[s]));
      dp[s][e][0] = std::min(dp[s][e][0], dp[s + 1][e][1] + cost(a[e], a[s]));

      dp[s][e][1] = std::min(dp[s][e][1], dp[s][e - 1][0] + cost(a[s], a[e]));
      dp[s][e][1] =
          std::min(dp[s][e][1], dp[s][e - 1][1] + cost(a[e - 1], a[e]));
    }
  }
  logd(dp);

  i64 ans = INT64_MAX;
  ans = std::min(ans, dp[0][n - 1][0] + cost(a[0], 0));
  ans = std::min(ans, dp[0][n - 1][1] + cost(a[n - 1], 0));

  std::cout << ans << "\n";
}