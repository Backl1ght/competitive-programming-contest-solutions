// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {
  int g = 1;
  for (int i = 1; i <= 8; ++i)
    g = i * g / std::gcd(i, g);
  logd(g);
}

void SolveCase(int Case) {
  int n, x, y;
  std::cin >> n >> x >> y;

  std::vector<int> p(n - 1), t(n - 1);
  for (int i = 0; i < n - 1; ++i)
    std::cin >> p[i] >> t[i];

  auto f = [&](i64 ct) {
    logd("t", ct);
    ct += x;
    logd("0", ct);
    for (int i = 0; i < n - 1; ++i) {
      ct = ct % p[i] == 0 ? ct : ct + (p[i] - ct % p[i]);
      logd("w", i, ct);
      ct += t[i];
      logd("b", i + 1, ct);
    }
    ct += y;
    logd("a", ct);
    return ct;
  };

  int N = 840;
  std::vector<i64> cost(N);
  for (int i = 0; i < N; ++i) {
    cost[i] = f(i);
  }
  logd(cost);

  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    int j;
    std::cin >> j;
    std::cout << (j - j % N) + cost[j % N] << "\n";
  }
}
