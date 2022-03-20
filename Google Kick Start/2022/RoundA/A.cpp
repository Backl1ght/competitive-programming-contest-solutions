// Problem: Speed Typing
// Contest: Google Coding Competitions - Round A 2022 - Kick Start 2022
// URL:
// https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb33e/00000000009e7021
// Memory Limit: 1024 MB
// Time Limit: 20000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

#define CPPIO ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#ifdef BACKLIGHT
#include "debug.h"
#else
#define logd(...) ;
#endif

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
  cout << "Case #" << Case << ": ";
  string s;
  cin >> s;
  string t;
  cin >> t;

  int n = s.size(), m = t.size();
  bool flag = true;
  int i = 0, j = 0;
  while (i < n) {
    while (j < m && s[i] != t[j]) ++j;
    if (j < m) {
      ++i;
      ++j;
    } else {
      flag = false;
      break;
    }
  }
  if (flag)
    cout << m - n << "\n";
  else
    cout << "IMPOSSIBLE\n";
}