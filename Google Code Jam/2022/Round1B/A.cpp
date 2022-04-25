// Problem: Pancake Deque
// Contest: Google Coding Competitions - Round 1B 2022 - Code Jam 2022
// URL:
// https://codingcompetitions.withgoogle.com/codejam/round/000000000087711b/0000000000acd59d
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

  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int& v : a)
    std::cin >> v;

  int ans = 0;
  int l = 0, r = n - 1, ma = 0;
  while (l <= r) {
    if (a[l] <= a[r]) {
      if (a[l] >= ma)
        ++ans;
      ma = std::max(ma, a[l]);
      ++l;
    } else {
      if (a[r] >= ma)
        ++ans;
      ma = std::max(ma, a[r]);
      --r;
    }
  }
  std::cout << ans << "\n";
}