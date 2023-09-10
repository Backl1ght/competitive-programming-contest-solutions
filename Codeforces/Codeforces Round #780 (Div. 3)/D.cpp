// Problem: D. Maximum Product Strikes Back
// Contest: Codeforces - Codeforces Round #780 (Div. 3)
// URL: https://codeforces.com/contest/1660/problem/D
// Memory Limit: 256 MB
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
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int& v : a)
    std::cin >> v;

  int ans = 0, ansl = n, ansr = 0;
  auto work = [&](int l, int r) -> void {
    int c2 = 0, f = 1;
    for (int i = l; i <= r; ++i) {
      if (a[i] == -2) {
        ++c2;
        f = -f;
      } else if (a[i] == -1) {
        f = -f;
      } else if (a[i] == 2) {
        ++c2;
      }
    }

    if (f == 1) {
      if (c2 > ans) {
        ans = c2;
        ansl = l;
        ansr = n - r - 1;
      }
    } else {
      int p;
      int cl = c2;
      for (int i = l; i <= r; ++i) {
        if (a[i] == -2) {
          --cl;
          p = i + 1;
          break;
        } else if (a[i] == -1) {
          p = i + 1;
          break;
        } else if (a[i] == 2) {
          --cl;
        }
      }
      if (cl > ans) {
        ans = cl;
        ansl = p;
        ansr = n - r - 1;
      }

      int cr = c2;
      for (int i = r; i >= l; --i) {
        if (a[i] == -2) {
          --cr;
          p = i - 1;
          break;
        } else if (a[i] == -1) {
          p = i - 1;
          break;
        } else if (a[i] == 2) {
          --cr;
        }
      }
      if (cr > ans) {
        ans = cr;
        ansl = l;
        ansr = n - p - 1;
      }
    }
  };

  for (int l = 0; l < n; ++l) {
    if (a[l] == 0)
      continue;
    int r = l;
    while (r + 1 < n && a[r + 1] != 0)
      ++r;
    work(l, r);
    logd(l, r);
    l = r;
  }

  std::cout << ansl << " " << ansr << "\n";
}