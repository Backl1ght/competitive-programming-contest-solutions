// Problem: d1000000
// Contest: Google Coding Competitions - Qualification Round 2022 - Code Jam
// 2022 URL:
// https://codingcompetitions.withgoogle.com/codejam/round/0000000000876ff1/0000000000a46471
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

  int N;
  std::cin >> N;

  std::vector<int> S(N);
  for (int& v : S)
    std::cin >> v;
  std::sort(S.begin(), S.end());

  int ans = 0;
  for (int i = 0; i < N; ++i) {
    if (ans + 1 <= S[i])
      ++ans;
  }
  std::cout << ans << "\n";
}