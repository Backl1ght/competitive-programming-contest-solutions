// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n, p, q;
  std::cin >> n >> p >> q;

  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    p = std::min(p, q + x);
  }
  std::cout << p << "\n";
}
