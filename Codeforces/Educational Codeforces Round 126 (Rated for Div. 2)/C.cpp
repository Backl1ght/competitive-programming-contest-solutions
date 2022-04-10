// Problem: C. Water the Trees
// Contest: Codeforces - Educational Codeforces Round 126 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1661/problem/C
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

i64 work(const std::vector<int>& a, int target) {
  auto check = [&](i64 x) -> bool {
    i64 c1 = x / 2 + x % 2, c2 = x / 2;
    for (int v : a) {
      i64 d = target - v;

      i64 t2 = std::min(c2, d / 2);
      c2 -= t2;
      d -= t2 * 2;

      if (c1 < d)
        return false;
      c1 -= d;
    }
    return true;
  };

  i64 l = 0, r = 1e18, mid, ans = 0;
  while (l <= r) {
    mid = (l + r) >> 1;
    if (check(mid))
      r = mid - 1, ans = mid;
    else
      l = mid + 1;
  }
  return ans;
}

void solve_case(int Case) {
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int& v : a)
    std::cin >> v;

  int ma = *std::max_element(a.begin(), a.end());

  i64 ans = std::min({work(a, ma), work(a, ma + 1), work(a, ma + 2)});

  std::cout << ans << "\n";
}