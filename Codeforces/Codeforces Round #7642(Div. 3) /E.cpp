// Problem: E. MEX and Increments
// Contest: Codeforces - Codeforces Round #762 (Div. 3)
// URL: http://codeforces.com/contest/1619/problem/E
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

const int N = 2e5 + 5;
int n, a[N], c[N];
void solve_case(int Case) {
  cin >> n;

  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    ++c[a[i]];
  }

  cout << c[0] << " ";

  multiset<int> st;
  i64 cost = 0;
  for (int i = 1; i <= n; ++i) {
    if (cost == -1) {
      cout << "-1"
           << " \n"[i == n];
      continue;
    }
    if (c[i - 1] == 0) {
      if (st.empty()) {
        cost = -1;
        cout << "-1"
             << " \n"[i == n];
        continue;
      } else {
        cost += i - 1 - *(--st.end());
        st.erase(--st.end());
      }
    }
    for (int j = 1; j <= c[i - 1] - 1; ++j) st.insert(i - 1);
    cout << cost + c[i] << " \n"[i == n];
  }

  for (int i = 1; i <= n; ++i) {
    --c[a[i]];
  }
}