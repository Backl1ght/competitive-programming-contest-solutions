// Problem: D - Polynomial division
// Contest: AtCoder - AtCoder Beginner Contest 245
// URL: https://atcoder.jp/contests/abc245/tasks/abc245_d
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

using poly = std::vector<int>;

poly operator/(const poly& f, const poly& g) {
  poly h = f;

  size_t n = h.size() - g.size() + 1;
  poly r(n);
  for (size_t i = 0; i < r.size(); ++i) {
    size_t ph = h.size() - i - 1;
    size_t pr = r.size() - i - 1;
    r[pr] = h[ph] / g.back();
    logd(i, ph, h[ph], g.back(), r[pr]);

    for (size_t j = 0; j < g.size(); ++j) {
      size_t ih = ph - g.size() + j + 1;
      h[ih] -= r[pr] * g[j];
      logd(h);
    }

    logd(r, h);
  }
  return r;
}

void solve_case(int Case) {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> a(n + 1), c(n + m + 1);
  for (int& v : a)
    std::cin >> v;
  for (int& v : c)
    std::cin >> v;

  auto b = c / a;
  for (int i = 0; i <= m; ++i)
    std::cout << b[i] << " \n"[i == m];
}