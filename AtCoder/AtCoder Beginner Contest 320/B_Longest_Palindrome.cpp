// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  std::string s;
  std::cin >> s;
  const int n = s.size();

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      std::string t = s.substr(i, j - i + 1);
      std::string r = t;
      std::reverse(t.begin(), t.end());
      if (t == r)
        ans = std::max(ans, (int)t.size());
    }
  }
  std::cout << ans << "\n";
}
