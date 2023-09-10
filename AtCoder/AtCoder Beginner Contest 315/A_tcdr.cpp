// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  std::string s;
  std::cin >> s;

  std::string t;
  for (char ch : s) {
    if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
      continue;
    t.push_back(ch);
  }

  std::cout << t << "\n";
}
