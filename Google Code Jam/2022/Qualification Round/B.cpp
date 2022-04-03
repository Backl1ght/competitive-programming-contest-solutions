// Problem: 3D Printing
// Contest: Google Coding Competitions - Qualification Round 2022 - Code Jam
// 2022 URL:
// https://codingcompetitions.withgoogle.com/codejam/round/0000000000876ff1/0000000000a4672b
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
  std::cout << "Case #" << Case << ": ";

  std::vector<std::vector<int>> a(4, std::vector<int>(3));
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      std::cin >> a[j][i];
    }
  }

  std::vector<int> b(4);
  for (int i = 0; i < 4; ++i) {
    b[i] = *std::min_element(a[i].begin(), a[i].end());
  }

  if (std::accumulate(b.begin(), b.end(), 0) < 1'000'000)
    std::cout << "IMPOSSIBLE\n";
  else {
    int sum = 0;
    for (int i = 0; i < 4; ++i) {
      b[i] = std::min(b[i], 1'000'000 - sum);
      sum += b[i];
    }
    for (int i = 0; i < 4; ++i)
      std::cout << b[i] << " \n"[i == 3];
  }
}