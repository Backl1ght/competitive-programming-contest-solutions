// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  std::string s;
  std::cin >> s;
  const int n = s.size();
  for (int i = 0; i + 1 < n; ++i) {
    if (s[i] <= s[i + 1]) {
      std::cout << "No\n";
      return;
    }
  }
  std::cout << "Yes\n";
}
