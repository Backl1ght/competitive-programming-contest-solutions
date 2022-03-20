// Problem: Palindrome Free Strings
// Contest: Google Coding Competitions - Round A 2022 - Kick Start 2022
// URL:
// https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb33e/00000000009e762e
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

bool palindrome5(int x) {
  static char s[6];
  for (int i = 4; i >= 0; --i) {
    s[i] = x % 2 + '0';
    x >>= 1;
  }
  return (s[0] == s[4]) && (s[1] == s[3]);
}

bool palindrome6(int x) {
  static char s[7];
  for (int i = 5; i >= 0; --i) {
    s[i] = x % 2 + '0';
    x >>= 1;
  }
  return (s[0] == s[5]) && (s[1] == s[4]) && (s[2] == s[3]);
}

bool judge(int x, int y) {
  int z = (x << 1) | y;
  return !palindrome5(z & 0x1f) && !palindrome6(z);
}

vector<int> G(string s) {
  logd(s);
  string t = s;
  vector<int> ret;
  function<void(int)> dfs = [&](int x) -> void {
    if (x == 5) {
      int y = 0;
      for (char ch : s) y = (y << 1) | (ch - '0');
      logd(s, y);
      if (!palindrome5(y)) ret.push_back(y);
      return;
    }
    if (t[x] == '?') {
      s[x] = '0';
      dfs(x + 1);
      s[x] = '1';
      dfs(x + 1);
    } else {
      dfs(x + 1);
    }
  };
  dfs(0);
  return ret;
}

void solve_case(int Case) {
  cout << "Case #" << Case << ": ";

  int n;
  cin >> n;
  string s;
  cin >> s;

  if (n < 5) {
    cout << "POSSIBLE\n";
    return;
  }

  vector<vector<int>> dp(n, vector<int>(32, 0));
  for (int x : G(s.substr(0, 5))) {
    dp[4][x] = 1;
  }
  for (int i = 5; i < n; ++i) {
    for (int j = 0; j < 32; ++j) {
      if (dp[i - 1][j] != 0) {
        int nxt;
        if ((s[i] == '0' || s[i] == '?') && judge(j, 0)) {
          nxt = ((j << 1) | 0) & 0x1f;
          dp[i][nxt] = 1;
        }
        if ((s[i] == '1' || s[i] == '?') && judge(j, 1)) {
          nxt = ((j << 1) | 1) & 0x1f;
          dp[i][nxt] = 1;
        }
      }
    }
  }

  logd(dp);

  cout << (*max_element(dp[n - 1].begin(), dp[n - 1].end()) == 1 ? "POSSIBLE"
                                                                 : "IMPOSSIBLE")
       << "\n";
}