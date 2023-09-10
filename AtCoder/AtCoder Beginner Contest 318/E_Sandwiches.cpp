// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::vector<std::vector<int>> p(n);
  for (int i = 0; i < n; ++i) {
    int v;
    std::cin >> v;
    --v;
    p[v].push_back(i);
  }
  i64 ans = 0;
  for (int i = 0; i < n; ++i) {
    if (p[i].size() < 2)
      continue;

    for (int j = 1; j < p[i].size(); ++j) {
      int d = p[i][j] - p[i][j - 1] - 1;
      ans += i64(d) * (j) * (p[i].size() - j);
    }
  }

  std::cout << ans << "\n";
}
