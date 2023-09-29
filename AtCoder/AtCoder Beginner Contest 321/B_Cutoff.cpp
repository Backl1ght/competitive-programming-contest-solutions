// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n, x;
  std::cin >> n >> x;

  std::vector<int> a(n);
  for (int i = 0; i < n - 1; ++i)
    std::cin >> a[i];
  int ans = -1;
  for (int i = 0; i <= 100; ++i) {
    auto b = a;
    b.back() = i;
    std::sort(b.begin(), b.end());
    int s = std::accumulate(b.begin() + 1, b.end() - 1, 0);
    if (s >= x) {
      ans = i;
      break;
    }
  }
  std::cout << ans << "\n";
}
