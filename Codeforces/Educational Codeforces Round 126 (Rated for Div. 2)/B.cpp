// Problem: B. Getting Zero
// Contest: Codeforces - Educational Codeforces Round 126 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1661/problem/B
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

const int N = 32768;
int a[N + 5];

void prework() {
  std::memset(a, -1, sizeof(a));
  a[0] = 0;
  std::queue<std::pair<int, int>> q;
  q.push(std::make_pair(N, 0));
  while (!q.empty()) {
    auto [v, c] = q.front();
    q.pop();

    if (a[v - 1] == -1) {
      a[v - 1] = c + 1;
      q.push(std::make_pair(v - 1, c + 1));
    }

    if (v % 2 == 0 && a[v / 2] == -1) {
      a[v / 2] = c + 1;
      q.push(std::make_pair(v / 2, c + 1));
    }

    if ((v + N) % 2 == 0) {
      int x = (v + N) / 2;
      if (x >= 0 && x < N && a[x] == -1) {
        a[x] = c + 1;
        q.push(std::make_pair(x, c + 1));
      }
    }
  }
}

int main() {
  prework();
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
  std::cout << a[n] << " ";
}