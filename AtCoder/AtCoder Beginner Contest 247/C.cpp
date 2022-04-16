// Problem: C - 1 2 1 3 1 2 1
// Contest: AtCoder - AtCoder Beginner Contest 247
// URL: https://atcoder.jp/contests/abc247/tasks/abc247_c
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
  std::string s = "1";
  for (int i = 2; i <= n; ++i) {
    s = s + " " + std::to_string(i) + " " + s;
  }
  std::cout << s << "\n";
}