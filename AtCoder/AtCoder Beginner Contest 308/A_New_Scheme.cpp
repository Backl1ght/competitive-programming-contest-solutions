// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  const int n = 8;
  bool flag = true;
  int a[8];
  for (int i = 0; i < n; ++i)
    std::cin >> a[i];
  int x = 0;
  for (int v : a) {
    if (v % 25)
      flag = false;
    if (v < 100 || v > 675)
      flag = false;
    if (v < x)
      flag = false;
    x = v;
  }
  std::cout << (flag ? "Yes" : "No") << "\n";
}
