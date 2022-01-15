// Problem: D. New Year's Problem
// Contest: Codeforces - Codeforces Round #762 (Div. 3)
// URL: http://codeforces.com/contest/1619/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

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
  int n, m;
  cin >> m >> n;
  vector<vector<int>> p(m, vector<int>(n));
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < n; ++j) cin >> p[i][j];

  vector<multiset<int>> s(n);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      s[j].insert(p[i][j]);
    }
  }

  function<bool(int x)> check = [&](int x) -> bool {
    vector<int> can(n);
    bool pair = false;
    for (int i = 0; i < m; ++i) {
      int c = 0;
      for (int j = 0; j < n; ++j) {
        if (p[i][j] >= x) {
          ++c;
          ++can[j];
        }
      }
      if (c > 1) pair = true;
    }

    bool flag = true;
    for (int j = 0; j < n; ++j) {
      if (can[j] == 0) {
        flag = false;
        break;
      }
    }
    return flag && pair;
  };

  int l = 0, r = 1e9 + 5, mid, ans = 1;
  while (l <= r) {
    mid = (l + r) >> 1;
    if (check(mid))
      l = mid + 1, ans = mid;
    else
      r = mid - 1;
  }
  cout << ans << "\n";
}