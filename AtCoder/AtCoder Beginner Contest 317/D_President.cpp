// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::vector<int> x(n), y(n), z(n);
  for (int i = 0; i < n; ++i)
    std::cin >> x[i] >> y[i] >> z[i];
  int Z = std::accumulate(z.begin(), z.end(), 0);

  std::vector<int> w, v;
  int tz = 0;
  for (int i = 0; i < n; ++i) {
    if (x[i] > y[i]) {
      tz += z[i];
    } else {
      v.push_back(z[i]);
      w.push_back((y[i] - x[i] + 1) / 2);
    }
  }

  if (2 * tz >= Z) {
    std::cout << "0\n";
    return;
  }

  const int N = 1e5 + 5;
  const i64 INF = 0x3f3f3f3f3f3f3f3f;
  std::vector<i64> dp(N, INF);
  dp[0] = 0;
  for (int i = 0; i < w.size(); ++i) {
    for (int j = N - 1; j >= v[i]; --j) {
      dp[j] = std::min(dp[j], dp[j - v[i]] + w[i]);
    }
  }
  i64 ans = INF;
  for (int i = 0; i < N; ++i) {
    if (2 * (tz + i) > Z) {
      ans = std::min(ans, dp[i]);
    }
  }
  std::cout << ans << "\n";
}
