// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::vector<std::string> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  auto b = a;
  for (int i = 1; i < n; ++i)
    b[0][i] = a[0][i - 1];
  for (int i = 1; i < n; ++i)
    b[i][n - 1] = a[i - 1][n - 1];
  for (int i = 0; i < n - 1; ++i)
    b[n - 1][i] = a[n - 1][i + 1];
  for (int i = 0; i < n - 1; ++i)
    b[i][0] = a[i + 1][0];

  for (int i = 0; i < n; ++i)
    std::cout << b[i] << "\n";
}
