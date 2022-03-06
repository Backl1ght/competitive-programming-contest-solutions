// Problem: D. Weight the Tree
// Contest: Codeforces - Codeforces Round #774 (Div. 2)
// URL: http://codeforces.com/contest/1646/problem/D
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
  // cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

pair<int, int> operator+(const pair<int, int>& x, const pair<int, int>& y) {
  return make_pair(x.first + y.first, x.second + y.second);
}

void solve_case(int Case) {
  int n;
  cin >> n;

  if (n == 2) {
    cout << "2 2\n1 1\n";
    return;
  }

  vector<vector<int>> g(n);
  int u, v;
  for (int i = 0; i < n - 1; ++i) {
    cin >> u >> v;
    --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  vector<pair<int, int>> d0(n), d1(n);
  function<void(int, int)> dfs1 = [&](int u, int fa) -> void {
    d0[u] = make_pair(0, -1);
    d1[u] = make_pair(1, -g[u].size());
    for (int v : g[u]) {
      if (v == fa) continue;
      dfs1(v, u);
      d0[u] = d0[u] + max(d0[v], d1[v]);
      d1[u] = d1[u] + d0[v];
    }
  };
  dfs1(0, -1);

  vector<int> w(n);
  int numGood = 0, sumWeight = 0;
  function<void(int, int, bool)> dfs2 = [&](int u, int fa, bool can) -> void {
    if (can && d1[u] > d0[u]) {
      w[u] = g[u].size();
      numGood += 1;
      sumWeight += w[u];
      for (int v : g[u]) {
        if (v == fa) continue;
        dfs2(v, u, false);
      }
    } else {
      w[u] = 1;
      sumWeight += w[u];
      for (int v : g[u]) {
        if (v == fa) continue;
        dfs2(v, u, true);
      }
    }
  };
  dfs2(0, -1, true);

  cout << numGood << " " << sumWeight << "\n";
  for (int i = 0; i < n; ++i) cout << w[i] << " \n"[i == n - 1];
}