// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/math/modular/static_montgomery_mod_int.h"
using ModInt = math::StaticMontgomeryModInt<u32, 998244353>;

void Initialize() {}

void SolveCase(int Case) {
  int n, m;
  std::cin >> n >> m;

  ModInt dp0 = ModInt(1) * m * (m - 1), dp1(0);
  for (int i = 3; i <= n; ++i) {
    ModInt ndp0 = dp0 * (m - 2) + dp1 * (m - 1);
    ModInt ndp1 = dp0;
    dp0 = ndp0;
    dp1 = ndp1;
  }
  std::cout << dp0.value() << "\n";
}
