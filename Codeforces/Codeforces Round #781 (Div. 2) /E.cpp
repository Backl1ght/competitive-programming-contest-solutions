// Problem: E. MinimizOR
// Contest: Codeforces - Codeforces Round #781 (Div. 2)
// URL: https://codeforces.com/contest/1665/problem/E
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

const int N = 1e5 + 5;
int n, q, a[N];
std::pair<int, int> mi[N << 2];
void build(int x, int l, int r) {
  if (l == r) {
    mi[x] = std::make_pair(a[l], l);
    return;
  }
  int mid = (l + r) >> 1;
  build(x << 1, l, mid);
  build(x << 1 | 1, mid + 1, r);
  mi[x] = std::min(mi[x << 1], mi[x << 1 | 1]);
}

void update(int x, int l, int r, int p, int v) {
  if (l == r) {
    mi[x] = std::make_pair(v, l);
    return;
  }
  int mid = (l + r) >> 1;
  if (p <= mid)
    update(x << 1, l, mid, p, v);
  else
    update(x << 1 | 1, mid + 1, r, p, v);
  mi[x] = std::min(mi[x << 1], mi[x << 1 | 1]);
}

std::pair<int, int> query(int x, int l, int r, int L, int R) {
  if (l == L && r == R) {
    return mi[x];
  }
  int mid = (l + r) >> 1;
  if (R <= mid)
    return query(x << 1, l, mid, L, R);
  else if (L > mid)
    return query(x << 1 | 1, mid + 1, r, L, R);
  return std::min(query(x << 1, l, mid, L, mid),
                  query(x << 1 | 1, mid + 1, r, mid + 1, R));
}

void solve_case(int Case) {
  std::cin >> n;

  for (int i = 1; i <= n; ++i)
    std::cin >> a[i];

  build(1, 1, n);

  std::cin >> q;
  for (int _ = 1; _ <= q; ++_) {
    int l, r;
    std::cin >> l >> r;

    std::vector<std::pair<int, int>> vec;
    for (int i = 1; i <= std::min(r - l + 1, 31); ++i) {
      auto p = query(1, 1, n, l, r);
      vec.push_back(p);
      update(1, 1, n, p.second, INT_MAX);
    }

    int ans = INT_MAX;
    for (int i = 0; i < vec.size(); ++i) {
      for (int j = i + 1; j < vec.size(); ++j) {
        ans = std::min(ans, vec[i].first | vec[j].first);
      }
    }
    std::cout << ans << "\n";

    for (auto p : vec) {
      update(1, 1, n, p.second, p.first);
    }
  }
}