// Problem: H. Permutation and Queries
// Contest: Codeforces - Codeforces Round #762 (Div. 3)
// URL: http://codeforces.com/contest/1619/problem/H
// Memory Limit: 256 MB
// Time Limit: 4000 ms
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
  vector<int> p(n + 1), r(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> p[i];
    r[p[i]] = i;
  }

  int Q = sqrt(n) + 1;
  vector<int> nxt(n + 1);
  for (int i = 1; i <= n; ++i) {
    int x = i;
    for (int j = 1; j <= Q; ++j) {
      x = p[x];
    }
    nxt[i] = x;
  }

  auto update = [&](int x, int y) -> void {
    int z = x;
    for (int j = 1; j <= Q; ++j) {
      z = p[z];
    }
    for (int j = 1; j <= Q; ++j) {
      nxt[x] = z;
      z = r[z];
      x = r[x];
    }
  };

  int op, x, y;
  for (int _ = 0; _ < m; ++_) {
    cin >> op >> x >> y;
    if (op == 1) {
      swap(r[p[x]], r[p[y]]);
      swap(p[x], p[y]);
      update(x, y);
      update(y, x);
    } else {
      while (y > Q) {
        x = nxt[x];
        y -= Q;
      }
      while (y) {
        --y;
        x = p[x];
      }
      cout << x << "\n";
    }
  }
}