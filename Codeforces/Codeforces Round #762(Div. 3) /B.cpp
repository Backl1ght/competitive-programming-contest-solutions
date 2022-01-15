// Problem: B. Squares and Cubes
// Contest: Codeforces - Codeforces Round #762 (Div. 3)
// URL: http://codeforces.com/contest/1619/problem/B
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
  int n;
  cin >> n;
  set<int> s;
  for (int i = 1;; ++i) {
    i64 x = i64(1) * i * i;
    if (x <= n)
      s.insert(x);
    else
      break;
    x *= i;
    if (x <= n) s.insert(x);
  }
  cout << s.size() << "\n";
}