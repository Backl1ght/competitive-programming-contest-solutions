// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int p;
    std::cin >> p;
    --p;
    g[p].push_back(i);
  }

  std::vector<int> z(n);
  for (int i = 0; i < m; ++i) {
    int x, y;
    std::cin >> x >> y;
    --x;
    z[x] = std::max(z[x], y);
  }

  int ans = 0;
  std::function<void(int, int)> dfs = [&](int u, int y) {
    if (z[u] || y)
      ++ans;
    y = std::max(y, z[u] + 1);
    y = std::max(0, y - 1);
    for (int v : g[u]) {
      dfs(v, y);
    }
  };
  dfs(0, 0);

  std::cout << ans << "\n";
}
