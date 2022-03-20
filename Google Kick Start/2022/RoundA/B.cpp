// Problem: Challenge Nine
// Contest: Google Coding Competitions - Round A 2022 - Kick Start 2022
// URL:
// https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb33e/00000000009e7997
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
  int n = s.size();

  int m9 = 0;
  for (char ch : s) {
    m9 = m9 + (ch - '0');
    m9 %= 9;
  }
  m9 = (9 - m9) % 9;

  if (m9 == 0) {
    s.insert(s.begin() + 1, '0');
  } else {
    bool flag = false;
    char t = '0' + m9;
    for (int i = 0; i < n; ++i) {
      if (s[i] > t) {
        s.insert(s.begin() + i, t);
        flag = true;
        break;
      }
    }
    if (!flag) {
      s = s + t;
    }
  }

  cout << s << endl;
}