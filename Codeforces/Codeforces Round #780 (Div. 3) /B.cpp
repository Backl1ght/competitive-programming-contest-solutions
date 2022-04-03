// Problem: B. Vlad and Candies
// Contest: Codeforces - Codeforces Round #780 (Div. 3)
// URL: https://codeforces.com/contest/1660/problem/B
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
  std::vector<int> a(n);
  for (int& v : a)
    std::cin >> v;
  std::sort(a.begin(), a.end());
  if (n == 1) {
    std::cout << (a[0] == 1 ? "YES" : "NO") << "\n";
    return;
  }

  std::cout << (a[n - 1] - a[n - 2] > 1 ? "NO" : "YES") << "\n";
}