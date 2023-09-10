// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; ++i)
    std::cin >> a[i];
  std::sort(a.begin(), a.end());
  for (int i = 1; i < n; ++i) {
    if (a[i] != a[i - 1] + 1) {
      std::cout << a[i - 1] + 1 << "\n";
      return;
    }
  }
  assert(false);
}
