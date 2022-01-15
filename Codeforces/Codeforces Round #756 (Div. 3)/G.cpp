// Problem: G. Robot and Candies
// Contest: Codeforces - Codeforces Round #756 (Div. 3)
// URL: https://codeforces.com/contest/1611/problem/G
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
  int n, m;
  cin >> n >> m;

  vector<string> s(n);
  for (int i = 0; i < n; ++i) cin >> s[i];

  int ans = 0;
  auto work = [n, m, &ans, &s](int party) {
    vector<vector<int>> vx(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if ((i + j) % 2 == party && s[i][j] == '1') {
          vx[i].push_back(j);
        }
      }
    }

    while (true) {
      vector<pair<int, int>> right_most;
      for (int i = 0; i < n; ++i) {
        if (not vx[i].empty()) {
          right_most.emplace_back(i, vx[i].back());
        }
      }

      if (right_most.empty()) {
        break;
      }

      ++ans;

      sort(right_most.begin(), right_most.end(),
           [](const pair<int, int>& l, const pair<int, int>& r) -> bool {
             return l.second > r.second;
           });

      set<pair<int, int>> collect;
      collect.insert(right_most[0]);
      for (int i = 1; i < int(right_most.size()); ++i) {
        bool can_collect = true;
        auto [x, y] = right_most[i];

        auto it = collect.upper_bound(make_pair(x, 0));
        if (it != collect.begin()) {
          auto [nx, ny] = *(prev(it));
          if (x - nx < ny - y) {
            can_collect = false;
          }
        }
        if (it != collect.end()) {
          auto [nx, ny] = *(it);
          if (nx - x < ny - y) {
            can_collect = false;
          }
        }

        if (can_collect) {
          collect.insert(right_most[i]);
        }
      }

      for (auto [x, y] : collect) {
        vx[x].pop_back();
      }
    }
  };

  work(0);
  work(1);
  cout << ans << "\n";
}