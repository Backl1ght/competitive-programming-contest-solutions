// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::vector<i64> x(n);
  for (int i = 0; i < n; ++i)
    std::cin >> x[i];

  std::vector<i64> l(n);
  for (int i = 0; i < n; ++i)
    std::cin >> l[i];

  auto can = [&](i64 k) {
    std::vector<i64> d(n);
    for (int i = 0; i < n; ++i) {
      d[i] = std::abs(k - x[i]);
    }
    std::sort(d.begin(), d.end());
    for (int i = 0; i < n; ++i)
      if (d[i] > l[i])
        return false;
    return true;
  };

  std::vector<i64> s(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      s.push_back(x[i] + l[j]);
      s.push_back(x[i] - l[j] - 1);
    }
  }
  std::sort(s.begin(), s.end());

  i64 ans = 0;
  for (int i = 1; i < s.size(); ++i) {
    if (can(s[i])) {
      ans += s[i] - s[i - 1];
    }
  }
  std::cout << ans << "\n";
}
