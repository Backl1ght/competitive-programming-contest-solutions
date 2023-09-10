// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::vector<std::vector<int>> cnt(101, std::vector<int>(101, 0));
  for (int i = 0; i < n; ++i) {
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;
    for (int x = a; x <= b - 1; ++x) {
      for (int y = c; y <= d - 1; ++y) {
        ++cnt[x][y];
      }
    }
  }

  int s = 0;
  for (int x = 0; x <= 100; ++x) {
    for (int y = 0; y <= 100; ++y) {
      if (cnt[x][y] >= 1)
        ++s;
    }
  }
  std::cout << s << "\n";
}
