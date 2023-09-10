// Problem: E. Matrix and Shifts
// Contest: Codeforces - Codeforces Round #780 (Div. 3)
// URL: https://codeforces.com/contest/1660/problem/E
// Memory Limit: 256 MB
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
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

void solve_case(int Case) {
  int n;
  std::cin >> n;

  std::vector<std::string> s(n);

  for (int i = 0; i < n; ++i)
    std::cin >> s[i];

  int all_ones = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if (s[i][j] == '1')
        ++all_ones;

  int ans = INT_MAX;
  for (int o = 0; o < n; ++o) {
    int diag_ones = 0;
    for (int i = 0; i < n; ++i) {
      if (s[i][(i + o) % n] == '1')
        ++diag_ones;
    }
    ans = std::min(ans, (all_ones - diag_ones) + (n - diag_ones));
  }

  std::cout << ans << "\n";
}