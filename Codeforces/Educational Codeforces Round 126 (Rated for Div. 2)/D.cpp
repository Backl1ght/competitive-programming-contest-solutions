// Problem: D. Progressions Covering
// Contest: Codeforces - Educational Codeforces Round 126 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1661/problem/D
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
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

void solve_case(int Case) {
  int n, k;
  std::cin >> n >> k;

  std::vector<i64> b(n);
  std::vector<i64> p(n);
  for (i64& v : b)
    std::cin >> v;

  i64 ans = 0;
  i64 delta = 0, count = 0;
  for (int i = n - 1; i >= 0; --i) {
    b[i] -= delta;

    if (i >= k && b[i] > 0) {
      i64 c = (b[i] + k - 1) / k;
      delta += c * k;
      count += c;
      p[i] = c;
      ans += c;
    }

    delta -= count;
    if (i + k - 1 < n)
      count -= p[i + k - 1];
  }

  i64 addon = 0;
  for (int i = 0; i < k; ++i) {
    if (b[i] > 0) {
      addon = std::max(addon, (b[i] + i) / (i + 1));
    }
  }
  ans += addon;

  std::cout << ans << "\n";
}