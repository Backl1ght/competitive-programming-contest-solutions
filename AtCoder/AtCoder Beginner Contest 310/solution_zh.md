# AtCoder Beginner Contest 310

## [F - Make 10 Again](https://atcoder.jp/contests/abc310/tasks/abc310_f)

对于 $a_i$ ，当且仅当摇出 $10$ 或 $10$ 以下的数时可能作为构成 $10$ 的一部分。

所以维护 $dp(i, S)$ ： 前 $i$ 个元素， $S$ 表示前 $i$ 个数可以表示的数的集合与 $\{x | 0 \le x \le 10\}$ 的交集，的概率。

然后转移的时候，一种情况就是摇出了大于 $10$ 的数，此时有 $dp(i + 1, S) += dp(i, S) * \frac{a_{i + 1} - 10}{a_{i + 1}}$ 。

另外一种情况就是摇出了小于等于 $10$ 的数 $x$ ，此时有 $dp(i + 1, S \cup f(S, x) \cup \{x\}) += dp(i, S) * \frac{1}{a_{i + 1}}$ 。其中 $f(S, x) = \{x + y | y \in S\} \cap \{x | 0 \le x \le 10\}$ 。

答案即为 $\sum_{10 \in S} dp(n, S)$ 。

## [G - Takahashi And Pass-The-Ball Game](https://atcoder.jp/contests/abc310/tasks/abc310_g)

倍增。

To be added.

## [Ex - Negative Cost](https://atcoder.jp/contests/abc310/tasks/abc310_h)

To be solved.
