// Problem: A. Square Counting
// Contest: Codeforces - Codeforces Round #774 (Div. 2)
// URL: http://codeforces.com/contest/1646/problem/0
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
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

void solve_case(int Case) {
  i64 n;
  i64 s;
  cin >> n >> s;
  n = n * n;
  cout << s / n << "\n";
}