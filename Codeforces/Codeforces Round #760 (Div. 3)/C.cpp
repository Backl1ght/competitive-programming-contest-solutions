// Problem: C. Polycarp Recovers the Permutation
// Contest: Codeforces - Codeforces Round #756 (Div. 3)
// URL: https://codeforces.com/contest/1611/problem/C
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
  int n;
  cin >> n;
  vector<int> a(n);
  for (int& v: a) cin >> v;
  if (a[0] != n && a[n - 1] != n) {
    cout << -1 << "\n";
    return;
  }
  
  if (a[n - 1] == n) {
    reverse(a.begin(), a.end() - 1);
  } else {
    reverse(a.begin() + 1, a.end());
  }
  for (int i = 0; i < n; ++i) cout << a[i] << " \n"[i == n - 1];
}