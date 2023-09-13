// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/math/modular/static_montgomery_mod_int.h"
#include "hira/stdext/container.h"
using ModInt = math::StaticMontgomeryModInt<u32, 998244353>;

void Initialize() {}

void SolveCase(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::string> s(n);
  for (int i = 0; i < n; ++i)
    std::cin >> s[i];

  auto dp = stdext::n_vector<ModInt>(n + 1, ModInt(0));
  dp[n] = 1;
  for (int j = 0; j < m; ++j) {
    auto ndp = stdext::n_vector<ModInt>(n + 1, ModInt(0));
    for (int i = n - 1; i >= 0; --i)
      dp[i] += dp[i + 1];

    bool has_black = false;
    for (int i = 0; i < n; ++i) {
      if (s[i][j] == '#')
        has_black = true;

      ndp[i] = dp[std::max(0, i - 1)];
      if (has_black)
        break;
    }
    if (!has_black)
      ndp[n] = dp[n - 1];
    dp = std::move(ndp);
  }

  ModInt ans = std::accumulate(dp.begin(), dp.end(), ModInt(0));
  std::cout << ans.value() << "\n";
}
