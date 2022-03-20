// Problem: E. Masha-forgetful
// Contest: Codeforces - Codeforces Round #764 (Div. 3)
// URL: http://codeforces.com/contest/1624/problem/E
// Memory Limit: 256 MB
// Time Limit: 3000 ms
//
// Powered by CP Editor (https://cpeditor.org)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define CPPIO ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

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

void solve_case(int Case) {
  using T = tuple<int, int, int>;
  int n, m;
  cin >> n >> m;

  vector<T> v2(100), v3(1000);

  for (int i = 1; i <= n; ++i) {
    string s;
    cin >> s;
    for (int j = 0; j < m; ++j) {
      if (j + 1 < m) {
        int x = stoi(s.substr(j, 2));
        v2[x] = T(j, j + 1, i);
      }
      if (j + 2 < m) {
        int x = stoi(s.substr(j, 3));
        v3[x] = T(j, j + 2, i);
      }
    }
  }

  string s;
  cin >> s;

  if (m == 1) {
    cout << "-1\n";
    return;
  }

  vector<vector<T>> t(m, vector<T>(2));
  for (int i = 0; i < m; ++i) {
    if (i + 1 < m) {
      int x = stoi(s.substr(i, 2));
      t[i][0] = v2[x];
    }
    if (i + 2 < m) {
      int x = stoi(s.substr(i, 3));
      t[i][1] = v3[x];
    }
  }

  vector<vector<T>> dp(m, vector<T>(2));
  if (m > 1) dp[1][0] = t[0][0];
  if (m > 2) dp[2][1] = t[0][1];
  for (int i = 3; i < m; ++i) {
    if ((dp[i - 2][0] != T() || dp[i - 2][1] != T()) && t[i - 1][0] != T()) {
      dp[i][0] = t[i - 1][0];
    }
    if ((dp[i - 3][0] != T() || dp[i - 3][1] != T()) && t[i - 2][1] != T()) {
      dp[i][1] = t[i - 2][1];
    }
  }

  vector<T> ans;
  int i = m - 1;
  while (i > 0) {
    if (dp[i][0] == T() && dp[i][1] == T()) {
      cout << "-1\n";
      return;
    }

    if ((i - 2 == -1 || dp[i - 2][0] != T() || dp[i - 2][1] != T()) &&
        dp[i][0] != T()) {
      ans.push_back(dp[i][0]);
      i -= 2;
      continue;
    }

    if ((i - 3 == -1 || dp[i - 3][0] != T() || dp[i - 3][1] != T()) &&
        dp[i][1] != T()) {
      ans.push_back(dp[i][1]);
      i -= 3;
      continue;
    }

    cout << "-1\n";
    return;
  }

  reverse(ans.begin(), ans.end());
  cout << ans.size() << "\n";
  for (auto [x, y, z] : ans) cout << x + 1 << " " << y + 1 << " " << z << "\n";
}