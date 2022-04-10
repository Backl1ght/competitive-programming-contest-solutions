// Problem: Double or One Thing
// Contest: Google Coding Competitions - Round 1A 2022 - Code Jam 2022
// URL:
// https://codingcompetitions.withgoogle.com/codejam/round/0000000000877ba5/0000000000aa8e9c
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
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

void solve_case(int Case) {
  std::cout << "Case #" << Case << ": ";
  std::string s;
  std::cin >> s;

  std::string t;
  for (int i = 0; i < s.size(); ++i) {
    int j = i;
    while (j + 1 < s.size() && s[j + 1] == s[i])
      ++j;

    for (int k = i; k <= j; ++k)
      t += s[i];

    if (j + 1 < s.size() && s[j + 1] > s[i])
      for (int k = i; k <= j; ++k)
        t += s[i];

    i = j;
  }
  std::cout << t << "\n";
}