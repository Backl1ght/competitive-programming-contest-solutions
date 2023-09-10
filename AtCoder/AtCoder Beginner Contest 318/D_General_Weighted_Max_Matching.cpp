// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::vector<std::vector<int>> c(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      std::cin >> c[i][j];
    }
  }

  std::vector<i64> dp(1 << n, 0);
  for (int mask = 0; mask < (1 << n); ++mask) {
    for (int i = 0; i < n; ++i) {
      if (mask >> i & 1)
        continue;
      for (int j = i + 1; j < n; ++j) {
        if (mask >> j & 1)
          continue;

        dp[mask | (1 << i) | (1 << j)] =
            std::max(dp[mask | (1 << i) | (1 << j)], dp[mask] + c[i][j]);
      }
    }
  }

  std::cout << dp.back() << "\n";
}
