// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<std::pair<int, int>>> g(n + 1);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    g[u].push_back({w, v});
    g[v].push_back({w, u});
  }
  for (int i = 1; i <= n; ++i)
    g[0].push_back({0, i});

  const int INF = 0x3f3f3f3f;
  int ans = 0;
  std::vector<std::vector<int>> dp(1 << (n + 1), std::vector<int>(n + 1, -INF));
  dp[0][0] = 0;
  for (int i = 0; i < (1 << (n + 1)); ++i) {
    for (int j = 0; j <= n; ++j) {
      if (dp[i][j] == -INF)
        continue;

      for (auto [w, k] : g[j]) {
        if (i >> k & 1)
          continue;
        dp[i | (1 << k)][k] = std::max(dp[i | (1 << k)][k], dp[i][j] + w);
      }

      ans = std::max(ans, dp[i][j]);
    }
  }
  std::cout << ans << "\n";
}
