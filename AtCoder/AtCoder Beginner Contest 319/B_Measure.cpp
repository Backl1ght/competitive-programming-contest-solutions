// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::string t(n + 1, '-');
  for (int i = 0; i <= n; ++i) {
    for (int j = 1; j <= 9; ++j) {
      if (n % j == 0 && i % (n / j) == 0) {
        t[i] = '0' + j;
        break;
      }
    }
  }
  std::cout << t << "\n";
}
