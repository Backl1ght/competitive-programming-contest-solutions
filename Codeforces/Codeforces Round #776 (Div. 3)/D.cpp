// Problem: D. Palindromes Coloring
// Contest: Codeforces - Codeforces Round #764 (Div. 3)
// URL: http://codeforces.com/contest/1624/problem/D
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
  int n, k;
  cin >> n >> k;
  string s;
  cin >> s;

  vector<int> c(26, 0);
  for (char ch : s) {
    ++c[ch - 'a'];
  }

  int e = 0, o = 0;
  for (int i = 0; i < 26; ++i) {
    e += c[i] / 2;
    o += c[i] % 2;
  }

  int ans = (e / k) * 2;
  if ((e % k * 2 + o >= k)) ++ans;
  cout << ans << "\n";
}