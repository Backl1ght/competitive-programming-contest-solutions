// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

void SolveCase(int Case) {
  int n, k, q;
  std::cin >> n >> k >> q;

  std::vector<int> a(n, 0);
  std::set<std::pair<int, int>> S, T;
  i64 sum = 0;
  for (int i = 0; i < n; ++i) {
    if (i < k)
      S.insert({a[i], i});
    else
      T.insert({a[i], i});
  }

  for (int i = 0; i < q; ++i) {
    int x, y;
    std::cin >> x >> y;
    --x;

    if (k == n) {
      sum -= a[x];
      sum += y;
    } else {
      auto it = S.find({a[x], x});
      if (it != S.end()) {
        sum -= a[x];
        S.erase(it);

        auto [ty, tx] = *(--T.end());
        T.erase(--T.end());

        S.insert({ty, tx});
        sum += ty;
      } else {
        T.erase({a[x], x});
      }

      auto [sy, sx] = *S.begin();
      if (y > sy) {
        sum -= sy;
        S.erase(S.begin());
        T.insert({sy, sx});

        S.insert({y, x});
        sum += y;
      } else {
        T.insert({y, x});
      }
    }

    a[x] = y;
    std::cout << sum << "\n";
  }
}
