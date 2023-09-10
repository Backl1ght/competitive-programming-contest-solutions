// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/math/modular/static_montgomery_mod_int.h"
#include "hira/stdext/container.h"
using ModInt = math::StaticMontgomeryModInt<u32, 998244353>;

void Initialize() {}

void SolveCase(int Case) {
  i64 n, A, B, C;
  std::cin >> n >> A >> B >> C;

  auto dp = stdext::n_vector<ModInt>(2, 2, 2, A, B, C, ModInt(0));
  dp[0][0][0][0][0][0] = 1;

  for (int i = 60; i >= 0; --i) {
    int d = ((n >> i) & 1);
    auto ndp = stdext::n_vector<ModInt>(2, 2, 2, A, B, C, ModInt(0));

    for (int fa : {0, 1}) {
      for (int fb : {0, 1}) {
        for (int fc : {0, 1}) {
          //

          for (int ma = 0; ma < A; ++ma) {
            for (int mb = 0; mb < B; ++mb) {
              for (int mc = 0; mc < C; ++mc) {
                //

                for (int da = 0; da <= (fa ? 1 : d); ++da) {
                  for (int db = 0; db <= (fb ? 1 : d); ++db) {
                    for (int dc = 0; dc <= (fc ? 1 : d); ++dc) {
                      if ((da ^ db ^ dc) != 0)
                        continue;

                      int na = (da + ma * 2) % A;
                      int nb = (db + mb * 2) % B;
                      int nc = (dc + mc * 2) % C;
                      ndp[fa || da < d][fb || db < d][fc || dc < d][na][nb]
                         [nc] += dp[fa][fb][fc][ma][mb][mc];
                    }
                  }
                }
              }
            }
          }
        }
      }
    }

    dp = ndp;
  }

  ModInt ans = 0;
  for (int fa : {0, 1})
    for (int fb : {0, 1})
      for (int fc : {0, 1})
        ans += dp[fa][fb][fc][0][0][0];
  ans -= n / std::lcm(A, B);
  ans -= n / std::lcm(A, C);
  ans -= n / std::lcm(B, C);
  ans -= 1;

  std::cout << ans.value() << "\n";
}
