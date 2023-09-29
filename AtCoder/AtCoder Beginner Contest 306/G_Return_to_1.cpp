#define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> g(n), rg(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;

    g[u].push_back(v);
    rg[v].push_back(u);
  }

  std::vector<int> dep(n, -1);
  std::function<void(int, int)> dfs = [&](int u, int depth) {
    dep[u] = depth;
    for (int v : g[u]) {
      if (dep[v] == -1) {
        dfs(v, depth + 1);
      }
    }
  };
  dfs(0, 0);

  std::vector<bool> vis(n, false);
  std::function<void(int)> dfs_r = [&](int u) {
    vis[u] = true;

    for (int v : rg[u]) {
      if (dep[v] != -1 && !vis[v]) {
        dfs_r(v);
      }
    }
  };
  dfs_r(0);
  for (int i = 0; i < n; ++i)
    if (!vis[i])
      dep[i] = -1;

  int gcd = 0;
  for (int i = 0; i < n; ++i) {
    if (dep[i] == -1)
      continue;
    for (int j : g[i]) {
      if (dep[j] == -1)
        continue;

      gcd = std::gcd(gcd, std::abs(dep[i] + 1 - dep[j]));
    }
  }
  while (gcd != 0 && gcd % 2 == 0)
    gcd /= 2;
  while (gcd != 0 && gcd % 5 == 0)
    gcd /= 5;

  std::cout << (gcd == 1 ? "Yes" : "No") << "\n";
}
