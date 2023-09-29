// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n, m;
  std::cin >> n >> m;

  std::vector<int> p(n);
  std::vector<std::bitset<100>> f(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> p[i];
    int c;
    std::cin >> c;
    for (int j = 0; j < c; ++j) {
      int x;
      std::cin >> x;
      --x;
      f[i].set(x);
    }
  }

  bool flag = false;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j)
        continue;

      if (p[i] < p[j])
        continue;
      if ((f[i] | f[j]) != f[j])
        continue;

      if (p[i] > p[j] || f[j].count() > f[i].count()) {
        flag = true;
        break;
      }
    }
    if (flag)
      break;
  }
  std::cout << (flag ? "Yes" : "No") << "\n";
}
