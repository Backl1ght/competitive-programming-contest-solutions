// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/graph/flow/dinic_max_flow.h"

void Initialize() {}

void SolveCase(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::string> s(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> s[i];
    s[i] = '#' + s[i];
  }

  std::vector<std::vector<std::vector<int>>> p(
      10, std::vector<std::vector<int>>(n, std::vector<int>()));
  for (int i = 0; i < n; ++i) {
    for (int t = 0; t < m; ++t) {
      int d = s[i][t + 1] - '0';
      p[d][i].push_back(t);
    }
  }

  auto check = [&](int maxt) {
    for (int d = 0; d < 10; ++d) {
      std::vector<int> ts;
      std::vector<std::pair<int, int>> E;
      for (int i = 0; i < n; ++i) {
        int sz = p[d][i].size();
        if (sz == 0)
          break;

        for (int j = 0; j < n; ++j) {
          int t = p[d][i][j % sz] + (j / sz) * m;
          if (t <= maxt) {
            ts.push_back(t);
            E.push_back({t, i});
          }
        }
      }
      std::sort(ts.begin(), ts.end());
      ts.erase(std::unique(ts.begin(), ts.end()), ts.end());
      for (auto& [t, i] : E)
        t = std::lower_bound(ts.begin(), ts.end(), t) - ts.begin();

      int S = ts.size() + n, T = S + 1;
      graph::DinicMaxFlow<int> mf(T + 1);
      for (int t = 0; t < ts.size(); ++t)
        mf.AddEdge(S, t, 1);
      for (const auto& [t, i] : E)
        mf.AddEdge(t, ts.size() + i, 1);
      for (int i = 0; i < n; ++i)
        mf.AddEdge(ts.size() + i, T, 1);

      if (mf.Dinic(S, T) == n)
        return true;
    }

    return false;
  };

  int l = 0, r = n * m, ans = INT_MAX;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (check(mid))
      r = mid - 1, ans = mid;
    else
      l = mid + 1;
  }
  if (ans == INT_MAX)
    ans = -1;
  std::cout << ans << "\n";
}
