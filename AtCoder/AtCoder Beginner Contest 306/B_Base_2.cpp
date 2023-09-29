// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  u64 x = 0, y = 1;
  for (int i = 0; i < 64; ++i) {
    u64 z;
    std::cin >> z;
    x += y * z;
    y *= 2;
  }
  std::cout << x << "\n";
}
