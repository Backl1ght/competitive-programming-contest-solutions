// Problem: E - Max Min
// Contest: AtCoder - AtCoder Beginner Contest 247
// URL: https://atcoder.jp/contests/abc247/tasks/abc247_e
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

std::mt19937 rng(time(0));
int rnd(int l, int r) {
  return l + rng() % (r - l + 1);
}

void solve_case(int Case) {
  int n, x, y;
  std::cin >> n >> x >> y;

  std::vector<int> a(n);
  for (int& v : a) {
    std::cin >> v;
  }

  i64 std = 0;
#ifdef BACKLIGHT
  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      int ma = *std::max_element(a.begin() + i, a.begin() + j + 1);
      int mi = *std::min_element(a.begin() + i, a.begin() + j + 1);
      if (ma == x && mi == y) {
        ++std;
      }
    }
  }
#endif

  i64 ans = 0;
  if (x == y) {
    for (int i = 0; i < n; ++i) {
      if (a[i] != x)
        continue;
      int j = i;
      while (j + 1 < n && a[j + 1] == x)
        ++j;
      ans += i64(1) * (j - i + 2) * (j - i + 1) / 2;
      i = j;
    }
  } else {
    auto work = [&](int l, int r) -> void {
      int lx = -1, ly = -1;
      for (int i = l; i <= r; ++i) {
        if (a[i] == x) {
          if (ly != -1 && ly > lx) {
            if (lx == -1)
              lx = l - 1;
            int len1 = ly - (lx + 1) + 1;
            int len2 = r - i + 1;
            ans += i64(1) * len1 * len2;
            logd(lx, ly, i, len1, len2);
          }
          lx = i;
        } else if (a[i] == y) {
          if (lx != -1 && lx > ly) {
            if (ly == -1)
              ly = l - 1;
            int len1 = lx - (ly + 1) + 1;
            int len2 = r - i + 1;
            ans += i64(1) * len1 * len2;
            logd(lx, ly, i, len1, len2);
          }
          ly = i;
        }
        logd(ans);
      }
    };

    for (int i = 0; i < n; ++i) {
      if (a[i] < y || a[i] > x)
        continue;
      int j = i;
      while (j + 1 < n && a[j + 1] >= y && a[j + 1] <= x)
        ++j;
      work(i, j);
      i = j;
    }
  }

  std::cout << ans << "\n";
  logd(ans, std);
#ifdef BACKLIGHT
  assert(ans == std);
#endif
}