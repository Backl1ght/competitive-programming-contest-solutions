// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::vector<std::vector<int>> a(n);
  int f, s;
  for (int i = 0; i < n; ++i) {
    std::cin >> f >> s;
    --f;
    a[f].push_back(s);
  }
  for (int i = 0; i < n; ++i)
    std::sort(a[i].begin(), a[i].end());

  std::vector<int> b;
  b.reserve(n);
  for (int i = 0; i < n; ++i) {
    if (!a[i].empty())
      b.push_back(a[i].back());
  }
  std::sort(b.begin(), b.end());

  int ans = 0;
  if (b.size() >= 2)
    ans = std::max(ans, b[b.size() - 1] + b[b.size() - 2]);
  for (int i = 0; i < n; ++i) {
    if (a[i].size() >= 2) {
      ans = std::max(ans, a[i][a[i].size() - 1] + a[i][a[i].size() - 2] / 2);
    }
  }
  std::cout << ans << "\n";
}
