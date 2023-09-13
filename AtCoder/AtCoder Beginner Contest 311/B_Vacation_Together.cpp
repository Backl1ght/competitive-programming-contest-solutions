// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> c(m, 0);
  std::string s;
  for (int i = 0; i < n; ++i) {
    std::cin >> s;
    for (int j = 0; j < m; ++j) {
      c[j] += s[j] == 'o';
    }
  }

  int ans = 0;
  for (int i = 0; i < m; ++i) {
    if (c[i] == n) {
      int j = i;
      while (j + 1 < m && c[j + 1] == n)
        ++j;
      ans = std::max(ans, j - i + 1);
      i = j;
    }
  }
  std::cout << ans << "\n";
}
