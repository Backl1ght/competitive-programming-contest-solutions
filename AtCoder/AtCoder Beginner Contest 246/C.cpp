// Problem: C - Coupon
// Contest: AtCoder - AtCoder Beginner Contest 246
// URL: https://atcoder.jp/contests/abc246/tasks/abc246_c
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
  i64 n, k, x;
  std::cin >> n >> k >> x;
  std::vector<i64> a(n);
  for (i64& v : a)
    std::cin >> v;

  for (i64& v : a) {
    i64 z = v / x;
    i64 t = std::min(z, k);
    v -= t * x;
    k -= t;
  }

  sort(a.begin(), a.end());
  i64 ans = 0;
  for (int i = 0; i < n - k; ++i)
    ans += a[i];
  logd(a);
  std::cout << ans << "\n";
}