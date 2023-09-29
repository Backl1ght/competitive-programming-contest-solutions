// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int a, b;
  std::cin >> a >> b;

  auto pow = [](int a, int b) {
    int r = 1;
    for (int i = 0; i < b; ++i)
      r *= a;
    return r;
  };

  std::cout << pow(a, b) + pow(b, a) << "\n";
}
