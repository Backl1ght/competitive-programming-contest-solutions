// #define MULTIPLE_TASK
#include "hira/main.cpp"

void Initialize() {}

i64 ExGCD(i64 a, i64 b, i64& x, i64& y) {
  if (!b) {
    x = 1;
    y = 0;
    return a;
  }
  i64 d = ExGCD(b, a % b, x, y);
  i64 t = x;
  x = y;
  y = t - (a / b) * y;
  return d;
}

void SolveCase(int Case) {
  i64 N, A, B, C, X;
  std::cin >> N >> A >> B >> C >> X;
  X -= A + B + C;
  --N;
  if (X < 0) {
    std::cout << "0\n";
    return;
  }

  i64 x0, y0;
  i64 g = ExGCD(B, C, x0, y0);
  i64 b = B / g;
  i64 c = C / g;

  i64 ans = 0;
  for (int i = 0; i <= N; ++i) {
    i64 Y = X - A * i;
    if (Y < 0)
      break;
    if (Y % g != 0)
      continue;

    i64 x = x0 * Y / g % c;
    if (x < 0)
      x += c;
    if (x > N)
      continue;

    i64 y = (Y - x * B) / C;
    if (y < 0)
      continue;

    i64 low = std::max<i64>(0, (y - N + b - 1) / b);
    i64 high = std::min<i64>((N - x) / c, y / b);
    if (low <= high)
      ans += high - low + 1;
  }
  std::cout << ans << "\n";
}
