// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::vector<std::string> s(n);
  for (int i = 0; i < n; ++i)
    std::cin >> s[i];

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j)
        continue;
      std::string t = s[i] + s[j];
      std::string r = t;
      std::reverse(r.begin(), r.end());
      if (t == r) {
        std::cout << "Yes\n";
        return;
      }
    }
  }
  std::cout << "No\n";
  return;
}
