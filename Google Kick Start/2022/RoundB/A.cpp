// Problem: Infinity Area
// Contest: Google Coding Competitions - Round B 2022 - Kick Start 2022
// URL:
// https://codingcompetitions.withgoogle.com/kickstart/round/00000000008caa74/0000000000acf079
// Memory Limit: 1024 MB
// Time Limit: 20000 ms
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
  std::cout << "Case #" << Case << ": ";

  int r, a, b;
  std::cin >> r >> a >> b;
  int A = 0, B = 0;
  int x = r;
  double pi = acos(-1.0);
  double ans = 0;
  for (int i = 1;; ++i) {
    if (x == 0)
      break;
    ans = ans + pi * x * x;
    if (i & 1) {
      x = x * a;
    } else {
      x = x / b;
    }
  }

  std::cout << std::fixed << std::setprecision(6) << ans << "\n";
}