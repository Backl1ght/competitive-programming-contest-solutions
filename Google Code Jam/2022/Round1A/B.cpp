// Problem: Equal Sum
// Contest: Google Coding Competitions - Round 1A 2022 - Code Jam 2022
// URL:
// https://codingcompetitions.withgoogle.com/codejam/round/0000000000877ba5/0000000000aa8fc1
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
  int N;
  std::cin >> N;

  i64 sum = 0;
  for (int i = 0; i < 30; ++i) {
    std::cout << (1 << i) << " ";
    sum += (1 << i);
  }

  std::set<int> a;
  for (int i = 0; i < N - 30; ++i) {
    int x = 1'000'000'000 - i;
    a.insert(x);
    sum += x;
    std::cout << x << " ";
  }
  std::cout << std::endl;

  for (int i = 0; i < N; ++i) {
    int x;
    std::cin >> x;
    a.insert(x);
    sum += x;
  }
  sum = sum >> 1;

  std::set<int> b;
  for (int x : a) {
    if (sum >= x) {
      sum -= x;
      b.insert(x);
    }
  }

  for (int i = 29; i >= 0; --i) {
    if (sum & (1 << i)) {
      sum -= (1 << i);
      b.insert(1 << i);
    }
  }

  for (int v : b) {
    std::cout << v << " ";
  }
  std::cout << std::endl;
}