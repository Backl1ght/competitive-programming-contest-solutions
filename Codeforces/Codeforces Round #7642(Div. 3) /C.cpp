// Problem: C. Wrong Addition
// Contest: Codeforces - Codeforces Round #762 (Div. 3)
// URL: http://codeforces.com/contest/1619/problem/C
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
  string a, s;
  cin >> a >> s;
  reverse(a.begin(), a.end());
  reverse(s.begin(), s.end());

  string b;
  int i = 0, j = 0;
  while (i < a.size() && j < s.size()) {
    if (s[j] < a[i]) {
      if (j + 1 == s.size()) goto failed;
      if (s[j + 1] != '1') goto failed;
      int vb = 10 + (s[j] - '0') - (a[i] - '0');
      b += char(vb + '0');

      ++i;
      ++j;
      ++j;
    } else {
      b += s[j] - a[i] + '0';

      ++i;
      ++j;
    }
  }
  if (i != a.size()) goto failed;
  while(j != s.size()) {
    b += s[j];
    ++j;
  }
  
  while(b.back() == '0') b.pop_back();

  reverse(b.begin(), b.end());
  cout << b << "\n";
  return;
failed:
  cout << "-1\n";
}