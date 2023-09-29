// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int a, b;
  std::cin >> a >> b;

  std::cout << ((a + 1 == b && (a - 1) / 3 == (b - 1) / 3) ? "Yes" : "No")
            << "\n";
}
