// Problem: Interesting Integers
// Contest: Google Coding Competitions - Round A 2022 - Kick Start 2022
// URL:
// https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb33e/00000000009e73ea
// Memory Limit: 1024 MB
// Time Limit: 20000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

#define CPPIO ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
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
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

int len;
int d[15];
i64 dp[15][150][150];
i64 dfs(int x, int sum, int prod, int zero, int lim, int target_sum) {
  if (x == 0) {
    return sum == target_sum && prod == 0;
  }

  if (!lim && !zero && dp[x][sum][prod] != -1) {
    return dp[x][sum][prod];
  }

  i64 result = 0;
  int lst = lim ? d[x] : 9;
  for (int i = 0; i <= lst; ++i) {
    if (zero && i == 0) {
      result += dfs(x - 1, 0, 1, zero, lim && i == lst, target_sum);
    } else {
      result += dfs(x - 1, sum + i, (prod * i) % target_sum, 0, lim && i == lst,
                    target_sum);
    }
  }
  if (!lim && !zero) dp[x][sum][prod] = result;
  return result;
}
i64 f(i64 x) {
  if (x == 0) return 0;

  len = 0;
  while (x) {
    d[++len] = x % 10;
    x /= 10;
  }

  i64 result = 0;
  for (int i = 1; i <= 12 * 9; ++i) {
    memset(dp, -1, sizeof(dp));
    result += dfs(len, 0, 1, 1, 1, i);
  }
  return result;
}

void solve_fast(i64 a, i64 b) { cout << f(b) - f(a - 1) << "\n"; }

void solve_case(int Case) {
  cout << "Case #" << Case << ": ";
  i64 a, b;
  cin >> a >> b;
  solve_fast(a, b);
}