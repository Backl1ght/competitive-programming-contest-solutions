// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n;
  std::string s;
  std::cin >> n;
  std::cin >> s;
  std::set<char> st;
  int i;
  for (i = 0; i < n; ++i) {
    st.insert(s[i]);
    if (st.size() == 3)
      break;
  }
  std::cout << i + 1 << "\n";
}
