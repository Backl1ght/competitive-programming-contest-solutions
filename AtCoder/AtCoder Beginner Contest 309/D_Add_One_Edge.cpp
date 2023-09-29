// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/graph/shortest_path/dijkstra.h"

void Initialize() {}

void SolveCase(int Case) {
  int n1, n2, m;
  std::cin >> n1 >> n2 >> m;
  int n = n1 + n2;

  std::vector<std::vector<std::pair<int, int>>> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    g[u].push_back({1, v});
    g[v].push_back({1, u});
  }

  auto d1 = graph::Dijkstra<int>(g, {0});
  auto dn = graph::Dijkstra<int>(g, {n - 1});
  const int INF = std::numeric_limits<int>::max();
  int x1 = 0, xn = 0;
  for (int i = 0; i < n; ++i) {
    if (d1[i] != INF)
      x1 = std::max(x1, d1[i]);
    if (dn[i] != INF)
      xn = std::max(xn, dn[i]);
  }
  std::cout << x1 + xn + 1 << "\n";
}
