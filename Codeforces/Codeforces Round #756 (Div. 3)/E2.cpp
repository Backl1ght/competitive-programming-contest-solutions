// Problem: E2. Escape The Maze (hard version)
// Contest: Codeforces - Codeforces Round #756 (Div. 3)
// URL: https://codeforces.com/contest/1611/problem/E2
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
  vector<vector<int>> g(n);
  vector<int> x(k);
  set<int> keep;

  for (int i = 0; i < k; ++i) cin >> x[i], --x[i];
  for (int i = 0, u, v; i < n - 1; ++i) {
    cin >> u >> v;
    --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  vector<int> fa(n), dep(n);
  function<void(int, int, int)> getFaAndDep = [&](int u, int f, int d) -> void {
    fa[u] = f;
    dep[u] = d;
    for (int v : g[u]) {
      if (v == f) continue;
      getFaAndDep(v, u, d + 1);
    }
  };
  getFaAndDep(0, -1, 0);
  sort(x.begin(), x.end(),
       [&dep](int x, int y) -> bool { return dep[x] < dep[y]; });

  int fr;
  vector<int> friendAt(n, -1), limit(n, 1e6);
  function<void(int)> limitDown = [&](int u) -> void {
    if (limit[u] == 0) return;
    limit[u] = 0;
    friendAt[u] = fr;
    for (int v : g[u]) {
      if (v == fa[u]) continue;
      limitDown(v);
    }
  };
  function<void(int)> limitUp = [&](int u) -> void {
    while (fa[u] != -1) {
      if (limit[fa[u]] <= limit[u] + 1)
        break;
      else {
        limit[fa[u]] = limit[u] + 1;
        friendAt[fa[u]] = fr;
      }
      u = fa[u];
    }
  };
  for (int p : x) {
    fr = p;
    limitDown(p);
    limitUp(p);
  }

  function<bool(int, int)> goDown = [&](int u, int timestamp) -> bool {
    if (timestamp >= limit[u]) {
      assert(friendAt[u] != -1);
      keep.insert(friendAt[u]);
      return false;
    }
    if (g[u].size() == 1 && u != 0) return true;

    for (int v : g[u]) {
      if (v == fa[u]) continue;
      if (goDown(v, timestamp + 1)) return true;
    }
    return false;
  };
  cout << (goDown(0, 0) ? -1 : int(keep.size())) << "\n";
}