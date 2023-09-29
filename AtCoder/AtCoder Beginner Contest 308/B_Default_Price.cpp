// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::string> c(n + 1);
  for (int i = 1; i <= n; ++i)
    std::cin >> c[i];

  std::vector<std::string> d(m + 1);
  std::vector<int> p(m + 1);
  for (int i = 1; i <= m; ++i)
    std::cin >> d[i];
  for (int i = 0; i <= m; ++i)
    std::cin >> p[i];

  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    int x = 0;
    for (int j = 1; j <= m; ++j) {
      if (c[i] == d[j]) {
        x = j;
        break;
      }
    }
    ans += p[x];
  }
  std::cout << ans << "\n";
}
