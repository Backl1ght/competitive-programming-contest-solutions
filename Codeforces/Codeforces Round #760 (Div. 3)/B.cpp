// Problem: B. Team Composition: Programmers and Mathematicians
// Contest: Codeforces - Codeforces Round #756 (Div. 3)
// URL: https://codeforces.com/contest/1611/problem/B
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
  int a, b;
  cin >> a >> b;
  int ans = min((a + b) / 4, min(a, b));
  cout << ans << "\n";
}