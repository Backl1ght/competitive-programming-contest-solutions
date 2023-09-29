// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::unordered_set<std::string> S;
  std::string s;
  for (int i = 0; i < n; ++i) {
    std::cin >> s;
    if (S.count(s))
      continue;
    std::reverse(s.begin(), s.end());
    if (S.count(s))
      continue;
    S.insert(s);
  }
  std::cout << S.size() << "\n";
}
