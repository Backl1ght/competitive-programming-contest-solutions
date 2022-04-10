// Problem: A. Array Balancing
// Contest: Codeforces - Educational Codeforces Round 126 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1661/problem/A
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

  std::vector<int> a(n), b(n);
  for (int& v : a)
    std::cin >> v;
  for (int& v : b)
    std::cin >> v;

  for (int i = 0; i < n; ++i) {
    if (a[i] < b[i])
      std::swap(a[i], b[i]);
  }

  i64 ans = 0;
  for (int i = 1; i < n; ++i) {
    ans += std::abs(a[i] - a[i - 1]);
    ans += std::abs(b[i] - b[i - 1]);
  }

  std::cout << ans << "\n";
}