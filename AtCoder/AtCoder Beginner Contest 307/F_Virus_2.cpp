// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/stdext/container.h"

void Initialize() {}

void SolveCase(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<std::pair<i64, i32>>> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    --u, --v;
    g[u].push_back({w, v});
    g[v].push_back({w, u});
  }

  int k;
  std::cin >> k;
  std::vector<int> a(k);
  for (int i = 0; i < k; ++i)
    std::cin >> a[i], --a[i];

  int d;
  std::cin >> d;
  std::vector<int> x(d + 1);
  for (int i = 1; i <= d; ++i)
    std::cin >> x[i];

  stdext::min_heap<std::pair<i64, i32>> q;
  for (int u : a)
    q.push({0, u});

  std::vector<int> ans(n, -1);
  for (int i = 0; i <= d; ++i) {
    std::vector<std::pair<i64, i32>> temp;

    logd(x[i]);
    logd(q);

    while (!q.empty() && q.top().first <= x[i]) {
      auto [w0, u] = q.top();
      q.pop();
      if (ans[u] != -1)
        continue;
      ans[u] = i;
      logd(u, i);

      for (auto [w, v] : g[u]) {
        if (ans[v] == -1) {
          q.push({w0 + w, v});
          temp.push_back({w, v});
        }
      }
    }
    logd(temp);

    for (auto [w, u] : temp)
      q.push({w, u});
  }

  for (int i = 0; i < n; ++i)
    std::cout << ans[i] << "\n";
}
