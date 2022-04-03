// Problem: C - Choose Elements
// Contest: AtCoder - AtCoder Beginner Contest 245
// URL: https://atcoder.jp/contests/abc245/tasks/abc245_c
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
  int n, k;
  std::cin >> n >> k;
  std::vector<int> a(n), b(n);
  for (int& v : a)
    std::cin >> v;
  for (int& v : b)
    std::cin >> v;

  std::vector<std::vector<int>> dp(n, std::vector<int>(2, 0));
  dp[0][0] = dp[0][1] = 1;
  for (int i = 1; i < n; ++i) {
    if (std::abs(a[i] - a[i - 1]) <= k)
      dp[i][0] |= dp[i - 1][0];
    if (std::abs(a[i] - b[i - 1]) <= k)
      dp[i][0] |= dp[i - 1][1];
    if (std::abs(b[i] - a[i - 1]) <= k)
      dp[i][1] |= dp[i - 1][0];
    if (std::abs(b[i] - b[i - 1]) <= k)
      dp[i][1] |= dp[i - 1][1];
  }
  std::cout << ((dp[n - 1][0] || dp[n - 1][1]) ? "Yes" : "No") << "\n";
}