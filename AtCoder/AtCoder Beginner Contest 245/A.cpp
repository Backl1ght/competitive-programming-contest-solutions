// Problem: A - Good morning
// Contest: AtCoder - AtCoder Beginner Contest 245
// URL: https://atcoder.jp/contests/abc245/tasks/abc245_a
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
  int a, b, c, d;
  std::cin >> a >> b >> c >> d;
  int x = a * 60 + b;
  int y = c * 60 + d;
  std::cout << (x <= y ? "Takahashi" : "Aoki") << "\n";
}