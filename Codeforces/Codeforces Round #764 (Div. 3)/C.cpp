// Problem: C. Division by Two and Permutation
// Contest: Codeforces - Codeforces Round #764 (Div. 3)
// URL: http://codeforces.com/contest/1624/problem/C
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

void solve_case(int Case) {
  int n;
  cin >> n;
  map<int, int> mp;
  for (int i = 0; i < n; ++i) {
    int v;
    cin >> v;
    while (v > n) v >>= 1;
    ++mp[v];
  }
  
  for (int i = n; i >= 1; --i) {
    if (!mp[i]) {
      cout << "NO\n";
      return;
    }
    for (int j = 1; j <= mp[i] - 1; ++j) {
      ++mp[i >> 1];
    }
  }
  cout << "YES\n";
}