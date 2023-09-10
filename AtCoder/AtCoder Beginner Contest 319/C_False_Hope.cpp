// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int c[3][3];
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      std::cin >> c[i][j];

  std::vector<std::pair<int, int>> a;
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      a.push_back({i, j});
  std::sort(a.begin(), a.end());

  auto F = [](std::vector<int> a) { return a[0] == a[1] && a[0] != a[2]; };

  int x = 0, y = 0;
  do {
    ++y;

    std::vector<std::vector<int>> row(3);
    std::vector<std::vector<int>> col(3);
    std::vector<int> diag1, diag2;

    for (int i = 0; i < 9; ++i) {
      row[a[i].first].push_back(c[a[i].first][a[i].second]);
      col[a[i].second].push_back(c[a[i].first][a[i].second]);
      if (a[i].first == a[i].second)
        diag1.push_back(c[a[i].first][a[i].second]);
      if (a[i].first == 2 - a[i].second)
        diag2.push_back(c[a[i].first][a[i].second]);
    }

    bool flag = false;
    for (int i = 0; i < 3; ++i)
      flag |= F(row[i]);
    for (int i = 0; i < 3; ++i)
      flag |= F(col[i]);
    flag |= F(diag1);
    flag |= F(diag2);
    if (flag)
      ++x;
  } while (std::next_permutation(a.begin(), a.end()));

  double ans = 1 - 1.0 * x / y;
  std::cout << std::fixed << std::setprecision(12) << ans << "\n";
}
