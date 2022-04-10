// Problem: D. GCD Guess
// Contest: Codeforces - Codeforces Round #781 (Div. 2)
// URL: https://codeforces.com/contest/1665/problem/D
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
#define int i64

void solve_case(int Case);

signed main() {
  CPPIO;
#ifdef BACKLIGHT
  int T = 100;
#else
  int T = 1;
  std::cin >> T;
#endif
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

std::mt19937 rng(19981010);
int rnd(int l, int r) {
  return l + rng() % (r - l + 1);
}

void solve_case(int Case) {
  int x = 0;

#ifdef BACKLIGHT
  int X = rnd(1, 1e9);
  logd(X);
  auto Q = [&](int a, int b) -> int {
    logd(x, a, b, x + a, x + b);
    assert(a >= 0 && a <= 2e9);
    assert(b >= 0 && b <= 2e9);
    int r = std::gcd(X + a, X + b);
    return r;
  };
#else
  auto Q = [](int a, int b) -> int {
    assert(a >= 0 && a <= 2e9);
    assert(b >= 0 && b <= 2e9);
    std::cout << "? " << a << " " << b << std::endl;
    int r;
    std::cin >> r;
    return r;
  };
#endif

  int r = Q(2, 4);
  if (r != 2)
    x |= 1;

  for (int i = 1; i < 29; ++i) {
    int a = (1LL << (i + 1)) - x;
    int b = a + (1LL << (i + 1));
    int r = Q(a, b);
    if (r != (1LL << (i + 1))) {
      x |= (1LL << i);
    }
  }
  if (Q(1, (x | (1LL << 29)) + 2) == (x | (1LL << 29)) + 1) {
    x |= (1LL << 29);
  }

#ifdef BACKLIGHT
  logd(x, X);
  assert(x == X);
#endif

  std::cout << "! " << x << std::endl;
}