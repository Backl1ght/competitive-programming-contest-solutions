// Problem: Weightlifting
// Contest: Google Coding Competitions - Round 1A 2022 - Code Jam 2022
// URL:
// https://codingcompetitions.withgoogle.com/codejam/round/0000000000877ba5/0000000000aa9280
// Memory Limit: 1024 MB
// Time Limit: 20000 ms
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

const int N = 105;
int E, W;
int X[N][N], necessary[N][N], dp[N][N];

int DP(int l, int r) {
  if (dp[l][r] == -1) {
    if (l == r) {
      dp[l][r] = 0;
    } else {
      dp[l][r] = INT_MAX;
      for (int i = l; i + 1 <= r; ++i) {
        dp[l][r] =
            std::min(dp[l][r], DP(l, i) + DP(i + 1, r) +
                                   2 * (necessary[l][i] - necessary[l][r]) +
                                   2 * (necessary[i + 1][r] - necessary[l][r]));
      }
    }
    logd(l, r, dp[l][r]);
  }
  return dp[l][r];
}

void solve_case(int Case) {
  std::cout << "Case #" << Case << ": ";

  std::cin >> E >> W;
  for (int i = 1; i <= E; ++i) {
    for (int j = 1; j <= W; ++j) {
      std::cin >> X[i][j];
    }
  }

  for (int i = 1; i <= E; ++i) {
    for (int j = 1; j <= E; ++j) {
      necessary[i][j] = 0;
      dp[i][j] = -1;
    }
  }

  for (int k = 1; k <= W; ++k) {
    for (int i = 1; i <= E; ++i) {
      int necessary_k = 105;
      for (int j = i; j <= E; ++j) {
        necessary_k = std::min(necessary_k, X[j][k]);
        necessary[i][j] += necessary_k;
      }
    }
  }

  std::cout << DP(1, E) + 2 * necessary[1][E] << "\n";
}