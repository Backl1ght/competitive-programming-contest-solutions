#define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  u64 n, x, k;
  std::cin >> n >> x >> k;

  if (k == 0) {
    std::cout << "1\n";
    return;
  }

  auto f = [&](u64 x, u64 k, u64 d) -> u64 {
    if (x > n)
      return 0;
    if (k == 0)
      return 1;

    x = x * 2 + d;
    --k;
    if (x > n)
      return 0;

    u64 l = x;
    for (u64 i = 0; i < k; ++i) {
      l = l * 2;
      if (l > n)
        return 0;
    }
    u64 r = x;
    for (u64 i = 0; i < k; ++i) {
      r = r * 2 + 1;
      if (r > n) {
        r = n;
        break;
      }
    }
    logd(x, k, d, l, r);
    return r - l + 1;
  };

  u64 ans = 0;
  ans += f(x, k, 0);
  ans += f(x, k, 1);
  while (true) {
    u64 d = 1 - (x & 1);

    if (k == 0)
      break;
    --k;

    if (x == 1)
      break;
    x /= 2;

    ans += f(x, k, d);
  }

  std::cout << ans << "\n";
}
