// Problem: G. Unusual Minesweeper
// Contest: Codeforces - Codeforces Round #762 (Div. 3)
// URL: http://codeforces.com/contest/1619/problem/G
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

  vector<int> x(n), y(n), z(n);
  for (int i = 0; i < n; ++i) {
    cin >> x[i] >> y[i] >> z[i];
  }
  map<int, set<pair<int, int>>> mx, my;
  for (int i = 0; i < n; ++i) {
    mx[x[i]].insert(make_pair(y[i], i));
    my[y[i]].insert(make_pair(x[i], i));
  }
  // cerr << "Case #" << Case << ": " << endl;

  vector<bool> vis(n, false);
  vector<int> T;
  for (int i = 0; i < n; ++i) {
    if (vis[i]) continue;

    // cerr << "# " << i << endl;

    vis[i] = true;
    int t = INT_MAX;
    queue<int> q;
    q.push(i);
    while (!q.empty()) {
      int u = q.front();
      q.pop();

      // cerr << u << " ";

      t = min(t, z[u]);

      {
        auto s = mx[x[u]];
        auto it = s.lower_bound(make_pair(y[u] - k, 0));
        while (it != s.end()) {
          if (it->first > y[u] + k) break;
          if (vis[it->second]) {
            it = s.erase(it);
            continue;
          }
          vis[it->second] = true;
          q.push(it->second);
          it = s.erase(it);
        }
      }

      {
        auto s = my[y[u]];
        auto it = s.lower_bound(make_pair(x[u] - k, 0));
        while (it != s.end()) {
          if (it->first > x[u] + k) break;
          if (vis[it->second]) {
            it = s.erase(it);
            continue;
          }
          vis[it->second] = true;
          q.push(it->second);
          it = s.erase(it);
        }
      }
    }
    // cerr << endl;

    T.emplace_back(t);
  }
  sort(T.begin(), T.end());

  auto check = [&T](int x) -> bool {
    int c1 = upper_bound(T.begin(), T.end(), x) - T.begin();
    int c2 = T.size() - c1;
    return c2 <= x + 1;
  };
  int l = 0, r = T.size(), mid, ans = T.size();
  while (l <= r) {
    mid = (l + r) >> 1;
    if (check(mid))
      r = mid - 1, ans = mid;
    else
      l = mid + 1;
  }

  cout << ans << "\n";
}