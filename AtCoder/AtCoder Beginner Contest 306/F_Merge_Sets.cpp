// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/ds/fenwick_tree.h"

void Initialize() {}

void SolveCase(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> a(n, std::vector<int>(m));
  std::vector<int> b;
  b.reserve(n * m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> a[i][j];
      b.push_back(a[i][j]);
    }
  }
  std::sort(b.begin(), b.end());
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      a[i][j] = std::lower_bound(b.begin(), b.end(), a[i][j]) - b.begin() + 1;
    }
  }

  ds::FenwickTree<int> T(n * m, 0);
  for (int i = 1; i <= n * m; ++i)
    T.Update(i, 1);

  i64 ans = i64(1) * n * (n - 1) / 2 * m * (m + 1) / 2;
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < m; ++j)
      T.Update(a[i][j], -1);

    for (int j = 0; j < m; ++j) {
      ans += T.Query(a[i][j]);
    }
  }
  std::cout << ans << "\n";
}
