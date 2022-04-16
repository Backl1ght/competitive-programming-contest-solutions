// Problem: B - Unique Nicknames
// Contest: AtCoder - AtCoder Beginner Contest 247
// URL: https://atcoder.jp/contests/abc247/tasks/abc247_b
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

  std::vector<std::string> s(n), t(n);
  for (int i = 0; i < n; ++i)
    std::cin >> s[i] >> t[i];

  std::set<std::string> used;
  auto can = [&](int p, const std::string& a) -> bool {
    for (int i = 0; i < n; ++i) {
      if (i == p)
        continue;
      if (a == s[i] || a == t[i])
        return false;
    }
    return true;
  };
  for (int i = 0; i < n; ++i) {
    if (!can(i, s[i]) and !can(i, t[i])) {
      std::cout << "No\n";
      return;
    }
  }

  std::cout << "Yes\n";
}