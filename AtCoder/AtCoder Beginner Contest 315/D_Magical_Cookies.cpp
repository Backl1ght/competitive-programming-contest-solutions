// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::string> s(n);
  for (int i = 0; i < n; ++i)
    std::cin >> s[i];

  std::vector<std::vector<int>> row(n, std::vector<int>(26, 0));
  std::vector<std::vector<int>> col(m, std::vector<int>(26, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      ++row[i][s[i][j] - 'a'];
      ++col[j][s[i][j] - 'a'];
    }
  }

  int ans = n * m;
  int tn = n, tm = m;
  for (;;) {
    bool flag = true;

    for (int c = 0; c < 26; ++c) {
      int t1 = 0;
      for (int i = 0; i < n; ++i) {
        if (row[i][c] > 1 && row[i][c] == tm) {
          ans -= tm;
          row[i][c] = -1;
          flag = false;
          ++t1;
          logd("R", c, i);
        }
      }

      int t2 = 0;
      for (int j = 0; j < m; ++j) {
        if (col[j][c] > 1 && col[j][c] == tn) {
          ans -= tn;
          col[j][c] = -1;
          flag = false;
          ++t2;
          logd("C", c, j);
        }
      }

      for (int j = 0; j < m; ++j)
        col[j][c] -= t1;
      for (int i = 0; i < n; ++i)
        row[i][c] -= t2;
      ans += t1 * t2;
      tn -= t1;
      tm -= t2;
    }

    if (flag)
      break;
  }

  std::cout << ans << "\n";
}
