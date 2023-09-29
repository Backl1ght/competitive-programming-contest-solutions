// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::cin >> n;

  std::string s;
  std::cin >> s;

  std::string t;
  int c = 0;
  for (char ch : s) {
    if (c && ch == ')') {
      while (t.back() != '(')
        t.pop_back();
      t.pop_back();
      --c;
    } else {
      t.push_back(ch);
      c += ch == '(';
    }
  }

  std::cout << t << "\n";
}
