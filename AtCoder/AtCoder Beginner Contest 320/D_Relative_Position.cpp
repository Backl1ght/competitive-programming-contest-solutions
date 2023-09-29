// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<i64> x(n), y(n);
  std::vector<std::vector<std::array<int, 3>>> g(n);
  for (int i = 0; i < m; ++i) {
    int a, b, dx, dy;
    std::cin >> a >> b >> dx >> dy;
    --a, --b;

    g[a].push_back({b, dx, dy});
    g[b].push_back({a, -dx, -dy});
  }

  std::vector<bool> f(n, false);
  std::function<void(int, int)> dfs = [&](int u, int fa) {
    f[u] = true;
    for (auto [v, dx, dy] : g[u]) {
      if (f[v])
        continue;
      x[v] = x[u] + dx;
      y[v] = y[u] + dy;
      dfs(v, u);
    }
  };
  dfs(0, 0);

  for (int i = 0; i < n; ++i) {
    if (!f[i]) {
      std::cout << "undecidable\n";
      continue;
    }
    std::cout << x[i] << " " << y[i] << "\n";
  }
}
