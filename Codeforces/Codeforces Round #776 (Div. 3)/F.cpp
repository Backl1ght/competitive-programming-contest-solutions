// Problem: F. Interacdive Problem
// Contest: Codeforces - Codeforces Round #764 (Div. 3)
// URL: http://codeforces.com/contest/1624/problem/F
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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
  // cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

void solve_case(int Case) {
  int n, y = 0, z;
  cin >> n;

  auto Q = [&](int c) -> int {
    cout << "+ " << c << endl;
    int ret;
    cin >> ret;
    return ret;
  };

  function<int(int, int)> solve = [&](int l, int r) -> int {
    // cerr << l << " " << r << endl;
    if (l == r) return l;
    int mid = (l + r) >> 1;

    int c = (r / n + 1) * n - (mid + 1);
    z = Q(c);
    if (z == y) {
      return solve(l + c, mid + c);
    } else {
      y = z;
      return solve(mid + 1 + c, r + c);
    }
  };

  int x = solve(1, n - 1);
  cout << "! " << x << endl;
}