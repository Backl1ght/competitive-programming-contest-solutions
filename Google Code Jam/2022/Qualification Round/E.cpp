// Problem: Twisty Little Passages
// Contest: Google Coding Competitions - Qualification Round 2022 - Code Jam
// 2022 URL:
// https://codingcompetitions.withgoogle.com/codejam/round/0000000000876ff1/0000000000a45fc0
// Memory Limit: 1024 MB
// Time Limit: 120000 ms
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

std::mt19937 rng(114514);
int rnd(int l, int r) {
  return l + rng() % (r - l + 1);
}

void solve_case(int Case) {
  int n, k;
  std::cin >> n >> k;
  logd(n, k);

  int r, p;
  std::cin >> r >> p;

  std::map<int, int> mpt;
  std::map<int, int> mpa;

  mpa[r] = p;

  int C = 30;
  for (int i = 0; i + 2 * C < k; i += 2 * C) {
    int k = rnd(1, n);

    for (int j = 0; j < C; ++j) {
      std::cout << "T " << k << std::endl;
      std::cin >> r >> p;
      mpa[r] = p;
      mpt[r] = p;

      std::cout << "W" << std::endl;
      std::cin >> r >> p;
      mpa[r] = p;
    }
  }

  i64 st = 0;
  for (auto p : mpt)
    st += p.second;
  i64 d = st / mpt.size();

  i64 sa = 0;
  for (auto p : mpa)
    sa += p.second;

  i64 cr = n - mpa.size();
  i64 ans = (sa + d * cr) / 2;
  logd(sa, d, cr, ans, mpa.size());

  std::cout << "E " << ans << std::endl;
}