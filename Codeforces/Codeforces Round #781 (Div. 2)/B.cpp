// Problem: B. Array Cloning Technique
// Contest: Codeforces - Codeforces Round #781 (Div. 2)
// URL: https://codeforces.com/contest/1665/problem/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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

  std::map<int, int> c;
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    ++c[x];
  }

  int ma = 0;
  for (auto p : c) {
    ma = std::max(ma, p.second);
  }

  int ans = n - ma;
  int r = n - ma;
  while (r > 0) {
    ++ans;
    r -= ma;
    ma = ma * 2;
  }

  std::cout << ans << "\n";
}