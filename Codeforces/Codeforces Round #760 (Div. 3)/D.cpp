// Problem: D. Weights Assignment For Tree Edges
// Contest: Codeforces - Codeforces Round #756 (Div. 3)
// URL: https://codeforces.com/contest/1611/problem/D
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
  int n;
  cin >> n;
  int root;
  vector<int> b(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> b[i];
    if (b[i] == i) {
      root = i;
    }
  }
  vector<int> p(n + 1);
  for (int i = 1; i <= n; ++i) cin >> p[i];
  
  if (p[1] != root) {
    cout << -1 << "\n";
    return;
  }

  vector<int> weight(n + 1, -1), dist(n + 1, -1);
  weight[root] = dist[root] = 0;
  for (int i = 2; i <= n; ++i) {
    int u = p[i], fa = b[u];
    if (weight[fa] == -1) {
      cout << -1 << "\n";
      return;
    }
    weight[u] = dist[p[i - 1]] - dist[fa] + 1;\
    dist[u] = dist[fa] + weight[u];
  }
  
  for (int i = 1; i <= n; ++i)
    cout << weight[i] << " \n"[i == n];
}