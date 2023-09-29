// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/math/modular/static_montgomery_mod_int.h"
using ModInt = math::StaticMontgomeryModInt<u32, 998244353>;

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int& v : a)
    std::cin >> v;

  const int MASK = 1 << 10, U = MASK - 1;
  std::vector<std::vector<ModInt>> dp(n + 1,
                                      std::vector<ModInt>(MASK, ModInt(0)));
  dp[0][0] = 1;
  for (int i = 0; i < n; ++i) {
    ModInt inv = ~ModInt(a[i]);

    for (int mask = 0; mask < MASK; ++mask) {
      int t = std::min(10, a[i]);
      for (int j = 1; j <= t; ++j) {
        int new_mask = ((mask | (mask << j) | (1 << (j - 1))) & U);
        dp[i + 1][new_mask] += dp[i][mask] * inv;
      }
      dp[i + 1][mask] += dp[i][mask] * (a[i] - t) * inv;
    }
  }

  ModInt ans(0);
  for (int mask = 0; mask < MASK; ++mask) {
    if (mask >> 9 & 1)
      ans += dp[n][mask];
  }

  std::cout << ans.value() << "\n";
}
