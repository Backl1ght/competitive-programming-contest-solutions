// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<int> a(n);
  for (int& v : a)
    std::cin >> v;
  int mx = *std::max_element(a.begin(), a.end());

  auto check = [&](i64 x) {
    int t = 1;
    i64 c = a[0];
    for (int i = 1; i < n; ++i) {
      if (c + 1 + a[i] > x) {
        ++t;
        c = a[i];
      } else
        c += a[i] + 1;
    }
    return t <= m;
  };

  i64 l = mx, r = 1e15, ans = r;
  while (l <= r) {
    i64 mid = (l + r) >> 1;
    if (check(mid))
      r = mid - 1, ans = mid;
    else
      l = mid + 1;
  }

  std::cout << ans << "\n";
}
