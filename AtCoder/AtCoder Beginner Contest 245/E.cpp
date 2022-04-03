// Problem: E - Wrapping Chocolate
// Contest: AtCoder - AtCoder Beginner Contest 245
// URL: https://atcoder.jp/contests/abc245/tasks/abc245_e
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
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

using Rect = std::pair<int, int>;

void solve_case(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<int> a(n), b(n), c(m), d(m);
  for (int& v : a)
    std::cin >> v;
  for (int& v : b)
    std::cin >> v;
  for (int& v : c)
    std::cin >> v;
  for (int& v : d)
    std::cin >> v;

  std::vector<std::pair<int, int>> C(n);
  std::vector<std::pair<int, int>> B(m);
  for (int i = 0; i < n; ++i) {
    C[i] = Rect(a[i], b[i]);
  }
  sort(C.begin(), C.end(), std::greater<Rect>());
  for (int i = 0; i < m; ++i) {
    B[i] = Rect(c[i], d[i]);
  }
  sort(B.begin(), B.end(), std::greater<Rect>());

  std::multiset<int> cand;
  int j = 0;
  for (int i = 0; i < n; ++i) {
    while (j < m && B[j].first >= C[i].first) {
      cand.insert(B[j].second);
      ++j;
    }

    auto it = cand.lower_bound(C[i].second);
    if (it == cand.end()) {
      std::cout << "No\n";
      return;
    }
    cand.erase(it);
  }

  std::cout << "Yes\n";
}