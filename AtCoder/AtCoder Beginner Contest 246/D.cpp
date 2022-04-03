// Problem: D - 2-variable Function
// Contest: AtCoder - AtCoder Beginner Contest 246
// URL: https://atcoder.jp/contests/abc246/tasks/abc246_d
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
  i64 n;
  std::cin >> n;

  auto f = [](i64 a, i64 b) -> i64 {
    return a * a * a + a * a * b + a * b * b + b * b * b;
  };

  i64 ans = INT64_MAX;
  for (i64 a = 0; a <= 1e6 + 5; ++a) {
    i64 l = 0, r = 1e6 + 5, mid, b;
    while (l <= r) {
      mid = (l + r) >> 1;
      if (f(a, mid) >= n)
        r = mid - 1, b = mid;
      else
        l = mid + 1;
    }
    ans = std::min(ans, f(a, b));
  }

  std::cout << ans << "\n";
}