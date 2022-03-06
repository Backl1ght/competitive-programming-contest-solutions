// Problem: B. Quality vs Quantity
// Contest: Codeforces - Codeforces Round #774 (Div. 2)
// URL: http://codeforces.com/contest/1646/problem/B
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
  for (int& v : a) cin >> v;
  sort(a.begin(), a.end());
  bool flag = false;
  int l = 1, r = n - 1;
  i64 sl = a[0], sr = 0;
  while (l < r) {
    sl += a[l];
    sr += a[r];
    if (sl < sr) flag = true;
    ++l;
    --r;
  }
  cout << (flag ? "YES" : "NO") << "\n";
}