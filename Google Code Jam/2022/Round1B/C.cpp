// Problem: ASeDatAb
// Contest: Google Coding Competitions - Round 1B 2022 - Code Jam 2022
// URL:
// https://codingcompetitions.withgoogle.com/codejam/round/000000000087711b/0000000000acd29b
// Memory Limit: 1024 MB
// Time Limit: 10000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define CPPIO \
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
#ifdef BACKLIGHT
#include "debug.h"
#else
#define logd(...) ;
#endif

using i64 = int64_t;
using u64 = uint64_t;

void solve_case(int Case);

int main() {
  CPPIO;
  int T = 1;
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

std::mt19937 rng(114514);
int rnd(int l, int r) {
  return l + rng() % (r - l + 1);
}

void solve_case(int Case) {
  int count = 0;
  auto Q = [&](const std::string& s) {
    std::cout << s << std::endl;
    int n;
    std::cin >> n;
    ++count;
    return n;
  };

  auto OO = [](const std::string& s) { return s + s; };

  auto OZ = [](const std::string& s) { return s + std::string(s.size(), '0'); };

  std::function<std::vector<std::string>(int)> P =
      [&](int x) -> std::vector<std::string> {
    if (x == 0)
      return {"1"};
    auto v = P(x - 1);

    decltype(v) r;
    for (const std::string& s : v)
      r.push_back(OO(s));
    auto temp = r;

    for (const std::string& s : v) {
      r.push_back(OZ(s));
      r.insert(r.end(), temp.begin(), temp.end());
    }

    logd(x, r);
    return r;
  };
  auto S = P(3);
  logd(S);

  for (const std::string& s : S) {
    if (Q(s) == 0)
      break;
  }
}