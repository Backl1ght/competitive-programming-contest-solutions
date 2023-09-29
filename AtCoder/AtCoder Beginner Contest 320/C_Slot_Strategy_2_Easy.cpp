// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;
  std::vector<std::string> s(3);
  for (int i = 0; i < 3; ++i) {
    std::cin >> s[i];
    s[i] = '#' + s[i];
  }

  const int INF = 0x3f3f3f3f;
  int ans = INF;
  std::vector<int> p = {0, 1, 2};
  do {
    for (int i = 0; i < 3 * n; ++i) {
      for (int j = i + 1; j < 3 * n; ++j) {
        for (int k = j + 1; k < 3 * n; ++k) {
          if (s[p[0]][i % n + 1] == s[p[1]][j % n + 1] &&
              s[p[0]][i % n + 1] == s[p[2]][k % n + 1]) {
            ans = std::min(ans, k);
          }
        }
      }
    }
  } while (std::next_permutation(p.begin(), p.end()));
  if (ans == INF)
    ans = -1;
  std::cout << ans << "\n";
}
