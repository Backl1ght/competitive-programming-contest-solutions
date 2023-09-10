// Problem: C. Tree Infection
// Contest: Codeforces - Codeforces Round #781 (Div. 2)
// URL: https://codeforces.com/contest/1665/problem/C
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

  std::vector<std::vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int p;
    std::cin >> p;
    --p;
    g[p].push_back(i);
  }
  logd(g);

  std::vector<int> a;
  for (int i = 0; i < n; ++i) {
    if (!g[i].empty()) {
      a.push_back(g[i].size());
    }
  }
  a.push_back(1);
  std::sort(a.begin(), a.end(), std::greater<int>());
  assert(n == std::accumulate(a.begin(), a.end(), 0));
  logd(a);

  auto check = [&](int x) -> bool {
    int e = 0;
    int y = x;
    for (int v : a) {
      if (y < 0)
        return false;
      if (e > x)
        return false;
      ++e;
      e += std::max(0, v - y);
      --y;
    }

    return e <= x;
  };

  int l = 1, r = n, mid, ans = -1;
  while (l <= r) {
    mid = (l + r) >> 1;
    logd(l, r, mid);
    if (check(mid))
      r = mid - 1, ans = mid;
    else
      l = mid + 1;
  }
  assert(ans != -1);
  std::cout << ans << "\n";
}