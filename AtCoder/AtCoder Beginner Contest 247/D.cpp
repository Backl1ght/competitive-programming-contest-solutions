// Problem: D - Cylinder
// Contest: AtCoder - AtCoder Beginner Contest 247
// URL: https://atcoder.jp/contests/abc247/tasks/abc247_d
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
  int n;
  std::cin >> n;
  std::queue<std::pair<int, int>> q;
  for (int _ = 1, op, x, c; _ <= n; ++_) {
    std::cin >> op;
    if (op == 1) {
      std::cin >> x >> c;
      q.push(std::make_pair(x, c));
    } else {
      std::cin >> c;
      i64 sum = 0;
      while (c) {
        auto& [a, b] = q.front();

        int t = std::min(c, b);
        c -= t;
        b -= t;
        sum += i64(a) * t;

        if (b == 0)
          q.pop();
      }
      std::cout << sum << "\n";
    }
  }
}