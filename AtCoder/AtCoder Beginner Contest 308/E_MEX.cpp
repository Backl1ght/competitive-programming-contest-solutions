// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/stdext/container.h"

void Initialize() {}

void SolveCase(int Case) {
  auto MEX = [](int x, int y, int z) {
    int r = 0;
    while (x == r || y == r || z == r)
      ++r;
    return r;
  };

  int n;
  std::cin >> n;

  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i)
    std::cin >> a[i];

  std::string s;
  std::cin >> s;

  std::vector<int> b(n + 1);
  for (int i = 1; i <= n; ++i) {
    if (s[i - 1] == 'M')
      b[i] = 0;
    if (s[i - 1] == 'E')
      b[i] = 1;
    if (s[i - 1] == 'X')
      b[i] = 2;
  }

  auto pref = stdext::n_vector<int>(n + 2, 3, 3, 0);
  for (int i = 1; i <= n; ++i) {
    pref[i] = pref[i - 1];
    ++pref[i][b[i]][a[i]];
  }

  auto suff = stdext::n_vector<int>(n + 2, 3, 3, 0);
  for (int i = n; i >= 1; --i) {
    suff[i] = suff[i + 1];
    ++suff[i][b[i]][a[i]];
  }

  i64 ans = 0;
  for (int i = 2; i <= n - 1; ++i) {
    if (b[i] != 1)
      continue;

    for (int x : {0, 1, 2}) {
      for (int y : {0, 1, 2}) {
        int l = pref[i - 1][0][x];
        int r = suff[i + 1][2][y];
        ans += i64(1) * MEX(x, y, a[i]) * l * r;
        logd(ans, x, y, a[i], MEX(x, y, a[i]), l, r);
      }
    }
  }
  std::cout << ans << "\n";
}
