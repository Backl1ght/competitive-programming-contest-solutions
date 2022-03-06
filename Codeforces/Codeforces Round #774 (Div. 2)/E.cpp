// Problem: E. Power Board
// Contest: Codeforces - Codeforces Round #774 (Div. 2)
// URL: http://codeforces.com/contest/1646/problem/E
// Memory Limit: 256 MB
// Time Limit: 1500 ms
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
  // cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

void solve_case(int Case) {
  int n, m;
  cin >> n >> m;

  vector<int> fm = {0};
  bitset<20000005> vis;
  int k = 0, pk = 1;
  while (pk * 2 <= n) {
    ++k;
    pk = pk * 2;
    int fkm = fm.back();
    for (int i = 1; i <= m; ++i) {
      if (not vis[k * i]) {
        vis.set(k * i);
        ++fkm;
      }
    }
    fm.push_back(fkm);
  }
  cerr << k << endl;

  i64 ans = 1;
  vector<bool> isGood(n + 1, true);
  for (int i = 2; i <= n; ++i) {
    if (isGood[i]) {
      i64 x = i;
      int k = 1;
      while (x * i <= n) {
        x = x * i;
        ++k;
        isGood[x] = false;
      }
      ans += fm[k];
    }
  }

  cout << ans << "\n";
}