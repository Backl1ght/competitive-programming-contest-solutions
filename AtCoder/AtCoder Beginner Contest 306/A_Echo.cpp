// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;
  std::string s;
  std::cin >> s;

  std::string t;
  for (char ch : s) {
    t.push_back(ch);
    t.push_back(ch);
  }
  std::cout << t << "\n";
}
