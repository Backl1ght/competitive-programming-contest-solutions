// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  for (int i = 0; i < n; ++i) {
    int s = 0;
    for (int j = 0; j < 7; ++j) {
      int x;
      std::cin >> x;
      s += x;
    }
    std::cout << s << " \n"[i + 1 == n];
  }
}
