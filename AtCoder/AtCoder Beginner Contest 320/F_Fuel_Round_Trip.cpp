// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n, h;
  std::cin >> n >> h;

  std::vector<int> x(n + 1), p(n), f(n);
  for (int i = 1; i <= n; ++i)
    std::cin >> x[i];
  for (int i = 1; i <= n - 1; ++i)
    std::cin >> p[i] >> f[i];

  const int INF = 0x3f3f3f3f;
  std::vector<std::vector<int>> dp(h + 1, std::vector<int>(h + 1, INF));
  for (int i = 0; i <= h; ++i)
    dp[h][i] = 0;
  for (int i = 1; i <= n; ++i) {
    int diff = x[i] - x[i - 1];

    std::vector<std::vector<int>> ndp(h + 1, std::vector<int>(h + 1, INF));
    for (int j = 0; j <= h; ++j) {
      for (int k = 0; k <= h; ++k) {
        if (j - diff < 0 || k + diff > h)
          continue;

        ndp[j - diff][k + diff] = std::min(ndp[j - diff][k + diff], dp[j][k]);
      }
    }
    dp = std::move(ndp);

    if (i != n) {
      std::vector<std::vector<int>> ndp(h + 1, std::vector<int>(h + 1, INF));
      for (int j = 0; j <= h; ++j) {
        for (int k = 0; k <= h; ++k) {
          ndp[j][k] = std::min(ndp[j][k], dp[j][k]);

          ndp[std::min(h, j + f[i])][k] =
              std::min(ndp[std::min(h, j + f[i])][k], dp[j][k] + p[i]);

          if (k >= f[i])
            ndp[j][k - f[i]] = std::min(ndp[j][k - f[i]], dp[j][k] + p[i]);

          if (k + f[i] >= h)
            ndp[j][k] = std::min(ndp[j][k], dp[j][h] + p[i]);
        }
      }
      dp = std::move(ndp);
    }
  }

  int ans = INF;
  for (int i = 0; i <= h; ++i)
    ans = std::min(ans, dp[i][i]);
  if (ans == INF)
    ans = -1;

  std::cout << ans << "\n";
}
