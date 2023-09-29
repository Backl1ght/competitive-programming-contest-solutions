// #define MULTIPLE_TASK
#include "hira/main.cpp"

#include "hira/stdext/container.h"

void Initialize() {}

void SolveCase(int Case) {
  i64 k;
  std::cin >> k;

  stdext::min_heap<i64> q;
  for (int i = 1; i <= 9; ++i)
    q.push(i), q.push(i * 10);
  while (--k) {
    i64 x = q.top();
    q.pop();

    logd(x);

    i64 t = x, y = 0, z = 1;
    while (t) {
      y = t % 10;
      t /= 10;
      z *= 10;
    }
    // logd(x, y, z);
    for (i64 i = y + 1; i <= 9; ++i) {
      //   logd(i * z + x);
      q.push(i * z + x);
    }
  }

  std::cout << q.top() << "\n";
}
