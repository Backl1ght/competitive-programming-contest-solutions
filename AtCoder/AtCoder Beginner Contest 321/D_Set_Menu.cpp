// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n, m;
  i64 p;
  std::cin >> n >> m >> p;

  std::vector<i64> a(n), b(m);
  for (int i = 0; i < n; ++i)
    std::cin >> a[i];
  for (int i = 0; i < m; ++i)
    std::cin >> b[i];
  std::sort(b.begin(), b.end());
  auto c = b;
  for (int i = 1; i < m; ++i)
    c[i] += c[i - 1];

  i64 ans = 0;
  for (int i = 0; i < n; ++i) {
    auto it = std::upper_bound(b.begin(), b.end(), p - a[i]);
    int l = it - b.begin();
    int r = m - l;
    ans += i64(1) * l * a[i];
    if (l != 0)
      ans += c[l - 1];
    ans += i64(1) * r * p;
  }
  std::cout << ans << "\n";
}
