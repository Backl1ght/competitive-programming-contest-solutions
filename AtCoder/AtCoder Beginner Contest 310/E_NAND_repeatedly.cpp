// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;
  std::string s;
  std::cin >> s;

  int dp[2] = {0, 0};
  dp[s[0] - '0'] = 1;
  i64 ans = dp[1];
  for (int i = 1; i < n; ++i) {
    if (s[i] == '0') {
      dp[1] = dp[0] + dp[1];
      dp[0] = 1;
    } else {
      std::swap(dp[0], dp[1]);
      ++dp[1];
    }
    ans += dp[1];
  }
  std::cout << ans << "\n";
}
