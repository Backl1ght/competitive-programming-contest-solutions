// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/math/modular/static_montgomery_mod_int.h"
using ModInt = math::StaticMontgomeryModInt<u32, 998244353>;

void Initialize() {}

void SolveCase(int Case) {
  int n;
  i64 k;
  std::cin >> n >> k;
  ModInt inv = ~ModInt(k);

  std::vector<int> a(n);
  for (int i = 0; i < n; ++i)
    std::cin >> a[i], --a[i];

  std::vector<ModInt> b(n);
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    b[i] = ModInt(x);
  }

  auto multiply = [](const std::vector<int>& a, const std::vector<int>& b) {
    const int n = a.size();
    std::vector<int> c(n);
    for (int i = 0; i < n; ++i)
      c[i] = a[b[i]];
    return c;
  };

  auto apply = [](const std::vector<int>& a, const std::vector<ModInt>& b) {
    const int n = a.size();
    std::vector<ModInt> c(n, 0);
    for (int i = 0; i < n; ++i)
      c[a[i]] += b[i];
    return c;
  };

  auto add = [](const std::vector<ModInt>& a, const std::vector<ModInt>& b) {
    const int n = a.size();
    std::vector<ModInt> c = a;
    for (int i = 0; i < n; ++i)
      c[i] += b[i];
    return c;
  };

  std::vector<ModInt> ans(n, 0);
  b = apply(a, b);
  while (k) {
    if (k & 1) {
      ans = add(ans, b);
      b = apply(a, b);
    }

    b = add(b, apply(a, b));
    a = multiply(a, a);
    k >>= 1;
  }
  logd(ans);

  for (int i = 0; i < n; ++i)
    std::cout << (ans[i] * inv).value() << " \n"[i + 1 == n];
}
