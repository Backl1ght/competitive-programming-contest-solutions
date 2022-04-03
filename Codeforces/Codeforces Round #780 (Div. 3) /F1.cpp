// Problem: F1. Promising String (easy version)
// Contest: Codeforces - Codeforces Round #780 (Div. 3)
// URL: https://codeforces.com/contest/1660/problem/F1
// Memory Limit: 256 MB
// Time Limit: 3000 ms
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
  std::string s;
  std::cin >> s;

  std::vector<int> c(n + 1);
  for (int i = 0; i < n; ++i) {
    c[i + 1] = c[i] + (s[i] == '+');
  }

  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; ++j) {
      int a = c[j] - c[i - 1];
      int b = j - i + 1 - a;
      if (a == b)
        ++ans;
      else if (a < b && (b - a) % 3 == 0)
        ++ans;
    }
  }
  std::cout << ans << "\n";
}