# AtCoder Beginner Contest 315

## [D - Magical Cookies](https://atcoder.jp/contests/abc315/tasks/abc315_d)

记剩余的行数为 $tn$ ，列数为 $tm$。

对于每一行统计这一行里颜色 $i$ 有多少个，如果某个颜色的数量大于 $2$ 且等于剩余的列数（之多只有一种颜色满足这个要求），就说明这行可以删了。

列类似。

这样就可以 $O(n)$ 完成一轮的操作，至多 $O(n)$ 轮，时间复杂度为 $O(n^2)$ 。

## [E - Prerequisites](https://atcoder.jp/contests/abc315/tasks/abc315_e)

一次 dfs 跑出所有依赖的点，然后拓扑排序。

## [F - Shortcuts](https://atcoder.jp/contests/abc315/tasks/abc315_f)

可以算出最差最差代价也不会超过 $M = \sqrt{2} \times {10}^{8}$ ，从而跳过的次数不会超过 $\log_{2}{M}$ ，大概在 $30$ 次。

然后就可以 DP 了。 $dp(i, j)$ 表示到第 $i$ 个检查点然后用了 $j$ 次跳过的最小代价。转移的时候枚举 $i$ 到前一个点之间跳过了多少个点然后就可以从已经计算过的结果转移过来了。

## [G - Ai + Bj + Ck = X (1 <= i, j, k <= N)](https://atcoder.jp/contests/abc315/tasks/abc315_g)

枚举 $i$ ，然后就只需要计算 $Bj + Ck = X - Ai = Y$ 了，然后这个等式一眼扩展欧几里得 + Bézout's lemma.

大概就是扩欧算 $ax + by = c$ 的一个特解 $x_0, y_0$ ，然后这个式子的通解为

$$
x = x_0 + t\frac{b}{\gcd(a, b)}\\
y = y_0 - t\frac{a}{\gcd(a, b)}
$$

其中 $t \in \Z$。

然后又就是简单计数了。大概就是先算出满足条件的最小的 $x$ 以及对应情况下的 $y$ ，然后 $x$ 至多增大到 $n$ ， $y$ 至多减小到 $1$ ，这样 $t$ 的范围也有了。

## [Ex - Typical Convolution Problem](https://atcoder.jp/contests/abc315/tasks/abc315_h)

半在线卷积或者说 Relaxed Convolution 的板子。

[editorial](https://atcoder.jp/contests/abc315/editorial/6997)

[hly's blog](https://hly1204.blog.uoj.ac/blog/7319?locale=zh-cn)

To be solved.