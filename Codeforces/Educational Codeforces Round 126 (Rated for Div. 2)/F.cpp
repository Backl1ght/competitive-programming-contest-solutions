// Problem: F. Teleporters
// Contest: Codeforces - Educational Codeforces Round 126 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1661/problem/F
// Memory Limit: 512 MB
// Time Limit: 7000 ms
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
  for (int i = 0, last = 0, x; i < n; ++i) {
    std::cin >> x;
    a[i] = x - last;
    last = x;
  }

  auto f = [](int l, int k) {
    ++k;
    i64 x = l / k;
    i64 t1 = l % k;
    i64 t2 = k - t1;
    return t1 * (x + 1) * (x + 1) + t2 * x * x;
  };

  auto eval_one = [&](int len, i64 bound) -> std::pair<int, i64> {
    if (bound <= 2 || len == 1)
      return std::make_pair(len - 1, len);
    int l = 1, r = len, mid, k = 0;
    while (l <= r) {
      mid = (l + r) >> 1;
      if (f(len, mid - 1) - f(len, mid) >= bound)
        l = mid + 1, k = mid;
      else
        r = mid - 1;
    }
    return std::make_pair(k, f(len, k));
  };

  auto eval = [&](i64 bound) {
    std::pair<int, i64> r(0, 0);
    for (int i = 0; i < n; ++i) {
      auto t = eval_one(a[i], bound);
      r.first += t.first;
      r.second += t.second;
    }
    logd(r);
    return r;
  };

  i64 m;
  std::cin >> m;

  if (eval(INT64_MAX).second <= m) {
    std::cout << "0\n";
    return;
  }

  i64 l = 0, r = 2e18, mid, bound = INT64_MAX;
  while (l <= r) {
    mid = (l + r) >> 1;
    if (eval(mid).second <= m)
      l = mid + 1, bound = mid;
    else
      r = mid - 1;
  }

  auto rc = eval(bound);
  logd(bound, rc, rc1);

  std::cout << (rc.first + (rc.second - m) / bound) << "\n";
}