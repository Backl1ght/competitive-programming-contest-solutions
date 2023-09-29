# AtCoder Beginner Contest 307

## [E - Distinct Adjacent](https://atcoder.jp/contests/abc307/tasks/abc307_e)

DP ，经典把环拆成链。

记 $f(x)$ 表示长度为 $x$ 首尾不同且相邻不同的链的方案数， $g(x)$ 表示长度为 $x$ 首尾相同且相邻不同的链的方案数。

$f(n)$ 即为答案，然后 $f(n) = (m - 2)f(n - 1) + (m - 1)g(n - 1)$ ， $g(n) = f(n - 1)$。

## [F - Virus 2](https://atcoder.jp/contests/abc307/tasks/abc307_f)

记已经感染的点集为 $S$。维护一个小顶堆 $Q$ ， $Q$ 中的元素 $(w, u)$ 表示有一个点 $u$ 距离 $S$ 中点的最小距离为 $w$ 。然后就是模拟每轮的感染情况，有点类似 Prim 最小生成树？

## [G - Approximate Equalization](https://atcoder.jp/contests/abc307/tasks/abc307_g)

DP 。

最后一定是有 $n - c$ 个 $t$ ，以及 $c$ 个 $t + 1$ 。这个简单数学就能求出来。

然后考虑 $dp(i, c)$ 表示前 $i$ 个元素，其中有 $c$ 个 $t + 1$ 。考虑从 $i$ 转移至 $i + 1$ ，此时借助前缀和可以求出当前 $a_{i + 1}$ 的值 $x$，然后就有

$$
\begin{aligned}
dp(i + 1, c) &= \max(dp(i + 1, c), dp(i, c) + |x - t|) \\
dp(i + 1, c + 1) &= \max(dp(i + 1, c + 1), dp(i, c) + |x - (t + 1)|)
\end{aligned}
$$

## [Ex - Marquee](https://atcoder.jp/contests/abc307/tasks/abc307_h)

To be solved.