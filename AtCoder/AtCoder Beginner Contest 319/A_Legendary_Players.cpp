// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  std::map<std::string, int> mp;
  mp["tourist"] = 3858;
  mp["ksun48"] = 3679;
  mp["Benq"] = 3658;
  mp["Um_nik"] = 3648;
  mp["apiad"] = 3638;
  mp["Stonefeang"] = 3630;
  mp["ecnerwala"] = 3613;
  mp["mnbvmar"] = 3555;
  mp["newbiedmy"] = 3516;
  mp["semiexp"] = 3481;

  std::string s;
  std::cin >> s;
  std::cout << mp[s] << "\n";
}
