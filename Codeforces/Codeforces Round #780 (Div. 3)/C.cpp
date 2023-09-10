// Problem: C. Get an Even String
// Contest: Codeforces - Codeforces Round #780 (Div. 3)
// URL: https://codeforces.com/contest/1660/problem/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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

const int N = 2e5 + 5;
char s[N];
int dp[N][3], p[26];
void solve_case(int Case) {
  std::cin >> s + 1;
  int n = std::strlen(s + 1);

  memset(p, 0, sizeof(p));
  memset(dp, 0x3f, sizeof(dp));
  dp[0][0] = 0;
  for (int i = 1; i <= n; ++i) {
    int ch = s[i] - 'a';

    dp[i][0] = std::min(dp[i - 1][0], dp[i - 1][2]) + 1;

    dp[i][1] = std::min(dp[i - 1][0], dp[i - 1][2]);

    if (p[ch] != 0) {
      dp[i][2] = dp[p[ch]][1] + (i - p[ch] + 1 - 2);
    }

    p[ch] = i;
  }

  int ans = std::min(dp[n][0], dp[n][2]);
  std::cout << ans << "\n";
}