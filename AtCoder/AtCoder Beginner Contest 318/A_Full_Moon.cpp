// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n, m, p;
  std::cin >> n >> m >> p;

  int c = 0;
  while (m <= n) {
    ++c;
    m += p;
  }
  std::cout << c << "\n";
}
