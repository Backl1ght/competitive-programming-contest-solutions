// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n, h, x;
  std::cin >> n >> h >> x;

  std::vector<int> p(n);
  for (int i = 0; i < n; ++i)
    std::cin >> p[i];

  for (int i = 0; i < n; ++i) {
    if (h + p[i] >= x) {
      std::cout << i + 1 << "\n";
      return;
    }
  }
}
