// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::vector<int> x(n);
  std::vector<int> y(n);
  for (int i = 0; i < n; ++i)
    std::cin >> x[i] >> y[i];

  const i64 INF = 0x3f3f3f3f3f3f3f3f;
  i64 dp0 = 0, dp1 = -INF;
  for (int i = 0; i < n; ++i) {
    if (x[i] == 0) {
      dp0 = std::max(dp0, dp0 + y[i]);
      dp0 = std::max(dp0, dp1 + y[i]);
    } else if (x[i] == 1) {
      dp1 = std::max(dp1, dp0 + y[i]);
    }
  }
  std::cout << std::max(dp0, dp1) << "\n";
}
