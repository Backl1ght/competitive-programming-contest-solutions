// Problem: B. Make AP
// Contest: Codeforces - Codeforces Round #764 (Div. 3)
// URL: http://codeforces.com/contest/1624/problem/B
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
  int a, b, c, d;
  cin >> a >> b >> c;

  bool can = false;

  d = 2 * b - c;
  if (d % a == 0 && d / a > 0) can = true;

  if ((a + c) % 2 == 0) {
    d = (a + c) / 2;
    if (d % b == 0 && d / b > 0) can = true;
  }

  d = 2 * b - a;
  if (d % c == 0 && d / c > 0) can = true;

  cout << (can ? "YES" : "NO") << "\n";
}