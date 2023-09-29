// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    a[i] = x;
    b[i] = x + y;
  }

  std::vector<int> id(n);
  std::iota(id.begin(), id.end(), 0);
  std::sort(id.begin(), id.end(), [&](int x, int y) {
    i64 lhs = 1ll * a[x] * b[y];
    i64 rhs = 1ll * a[y] * b[x];
    if (lhs == rhs)
      return x < y;
    return lhs > rhs;
  });

  for (int i = 0; i < n; ++i)
    std::cout << id[i] + 1 << " \n"[i + 1 == n];
}
