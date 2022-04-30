// Problem: Palindromic Factors
// Contest: Google Coding Competitions - Round B 2022 - Kick Start 2022
// URL:
// https://codingcompetitions.withgoogle.com/kickstart/round/00000000008caa74/0000000000acee89
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
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

void solve_case(int Case) {
  std::cout << "Case #" << Case << ": ";
  i64 n;
  std::cin >> n;

  auto f = [](i64 x) {
    std::string s = std::to_string(x);
    std::string t = s;
    std::reverse(t.begin(), t.end());
    return s == t;
  };

  int ans = 0;
  for (i64 i = 1; i * i <= n; ++i) {
    if (n % i == 0) {
      if (f(i))
        ++ans;
      if (i * i != n) {
        if (f(n / i))
          ++ans;
      }
    }
  }

  std::cout << ans << "\n";
}