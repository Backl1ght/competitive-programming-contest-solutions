// Problem: Punched Cards
// Contest: Google Coding Competitions - Qualification Round 2022 - Code Jam
// 2022 URL:
// https://codingcompetitions.withgoogle.com/codejam/round/0000000000876ff1/0000000000a4621b
// Memory Limit: 1024 MB
// Time Limit: 5000 ms
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
  std::cout << "Case #" << Case << ": \n";
  int R, C;
  std::cin >> R >> C;
  logd(R, C);
  R = 2 * R + 1;
  C = 2 * C + 1;

  std::vector<std::string> s(R);
  s[0].resize(C);
  for (int i = 0; i < C; ++i) {
    if (i & 1)
      s[0][i] = '-';
    else
      s[0][i] = '+';
  }

  s[1].resize(C);
  for (int i = 0; i < C; ++i) {
    if (i & 1)
      s[1][i] = '.';
    else
      s[1][i] = '|';
  }

  for (int i = 2; i < R; ++i) {
    s[i] = s[i % 2];
  }
  s[0][0] = s[0][1] = s[1][0] = '.';

  for (int i = 0; i < R; ++i)
    std::cout << s[i] << "\n";
}