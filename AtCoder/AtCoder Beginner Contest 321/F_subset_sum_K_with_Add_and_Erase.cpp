// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/math/modular/static_montgomery_mod_int.h"
using ModInt = math::StaticMontgomeryModInt<u32, 998244353>;

void Initialize() {}

void SolveCase(int Case) {
  int q, k;
  std::cin >> q >> k;

  std::vector<ModInt> dp(k + 1);
  dp[0] = 1;
  for (int i = 0; i < q; ++i) {
    std::string s;
    int x;
    std::cin >> s >> x;
    if (s == "-") {
      for (int j = x; j <= k; ++j)
        dp[j] -= dp[j - x];
    } else {
      for (int j = k; j >= x; --j)
        dp[j] += dp[j - x];
    }
    std::cout << dp[k].value() << "\n";
  }
}
