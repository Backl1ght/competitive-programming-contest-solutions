// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/stdext/container.h"

void Initialize() {}

double dist(int x1, int y1, int x2, int y2) {
  int x = x1 - x2;
  int y = y1 - y2;
  return std::sqrt(x * x + y * y);
}

void SolveCase(int Case) {
  constexpr int N = 30;
  std::vector<double> p2(N);
  p2[0] = 0;
  p2[1] = 1;
  for (int i = 2; i < N; ++i)
    p2[i] = p2[i - 1] * 2;

  int n;
  std::cin >> n;

  std::vector<int> x(n), y(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> x[i] >> y[i];
  }

  constexpr double INF = 1e18;
  auto dp = stdext::n_vector<double>(n, N, INF);
  dp[0][0] = 0;
  for (int i = 1; i < n; ++i) {
    for (int skip_at_i = 0; skip_at_i < N; ++skip_at_i) {
      int previous_index = i - 1 - skip_at_i;
      if (previous_index < 0)
        break;

      for (int total_skip_at_previous_index = 0;
           total_skip_at_previous_index < N; ++total_skip_at_previous_index) {
        int total_skip_at_i = skip_at_i + total_skip_at_previous_index;
        if (total_skip_at_i >= N)
          break;

        double cost_at_i =
            dist(x[i], y[i], x[previous_index], y[previous_index]);
        dp[i][total_skip_at_i] = std::min(
            dp[i][total_skip_at_i],
            dp[previous_index][total_skip_at_previous_index] +
                dist(x[i], y[i], x[previous_index], y[previous_index]) +
                p2[total_skip_at_i] - p2[total_skip_at_previous_index]);
      }
    }
  }

  double ans = *std::min_element(dp.back().begin(), dp.back().end());
  std::cout << std::fixed << std::setprecision(12) << ans << "\n";
}
