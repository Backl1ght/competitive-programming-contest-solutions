// Problem: A. Make Even
// Contest: Codeforces - Codeforces Round #756 (Div. 3)
// URL: http://codeforces.com/contest/1611/problem/A
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
  string s;
  cin >> s;
  if ((s.back() - '0') % 2 == 0)
    cout << 0 << "\n";
  else if ((s.front() - '0') % 2 == 0)
    cout << 1 << "\n";
  else {
    for (char ch : s)
      if ((ch - '0') % 2 == 0) {
        cout << 2 << "\n";
        return;
      }
    cout << -1 << "\n";
  }
}