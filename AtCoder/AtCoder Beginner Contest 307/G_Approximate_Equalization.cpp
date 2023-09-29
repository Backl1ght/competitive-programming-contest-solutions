// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::vector<i64> a(n + 1), s(n + 1);
  for (int i = 1; i <= n; ++i)
    std::cin >> a[i], s[i] = s[i - 1] + a[i];
  logd(a, s);

  i64 t = s[n] / n;
  i64 c = s[n] - n * t;
  if (c < 0) {
    --t;
    c = n + c;
  }
  logd(s[n], t, c);

  const i64 INF = 0x3f3f3f3f3f3f3f3f;
  std::vector<i64> dp(c + 1, INF);
  dp[0] = 0;
  for (int i = 1; i <= n; ++i) {
    std::vector<i64> ndp(c + 1, INF);
    for (int j = 0; j <= c; ++j) {
      i64 d = s[i - 1] - (i - 1 - j) * t - j * (t + 1);
      i64 x = a[i] + d;

      ndp[j] = std::min(ndp[j], dp[j] + std::abs(t - x));
      if (j != c)
        ndp[j + 1] = std::min(ndp[j + 1], dp[j] + std::abs(t + 1 - x));
    }
    dp = ndp;
  }

  std::cout << dp[c] << "\n";
}
