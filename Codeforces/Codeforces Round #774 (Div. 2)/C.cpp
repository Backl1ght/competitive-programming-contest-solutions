// Problem: C. Factorials and Powers of Two
// Contest: Codeforces - Codeforces Round #774 (Div. 2)
// URL: http://codeforces.com/contest/1646/problem/C
// Memory Limit: 256 MB
// Time Limit: 3000 ms
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

mt19937_64 rng(time(0));

void solve_case(int Case) {
  i64 n;
  cin >> n;

  vector<i64> s;
  i64 x = 1, y = 1;
  while (x <= n) {
    s.push_back(x);
    y = y + 1;
    x = x * y;
  }
  reverse(s.begin(), s.end());

  int ans = __builtin_popcountll(n);
  function<void(int, i64, int)> dfs = [&](int x, i64 value, int delta) -> void {
    if (x == s.size()) {
      return;
    }
    ans = min(ans, __builtin_popcountll(value) + delta);
    if (value >= s[x]) {
      dfs(x + 1, value - s[x], delta + 1);
    }
    dfs(x + 1, value, delta);
  };
  dfs(0, n, 0);

  cout << ans << "\n";
}