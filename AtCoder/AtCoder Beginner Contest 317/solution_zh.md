# AtCoder Beginner Contest 317

## [D - President](https://atcoder.jp/contests/abc317/tasks/abc317_d)

把现在失败的城市看成物品，体积为 $z_i$ ，代价为获胜需要的最小的票数变化，即 $\lceil \frac{y_i - x_i}{2} \rceil$ 。

然后就可以背包算获取 $t$ 票需要的最小代价 $w_t$ ，如果获取了 $t$ 票之后能获胜了就可以拿 $w_t$ 更新答案。

## [E - Avoid Eye Contact](https://atcoder.jp/contests/abc317/tasks/abc317_e)

对于里面的人跑一遍染色，把视线覆盖的各自染成 `!` 。由于每个格子至多会被四个方向的人染色，所以至多染 $4NM$ 次。

然后就是简单 BFS 走迷宫了。

## [F - Nim](https://atcoder.jp/contests/abc317/tasks/abc317_f)

可以把数看成二进制数位，然后 $x_i$ 在每一个位上要么全 $0$ 要么恰好有两个 $1$。然后模 $A_i$ 的余数可以堪称状态，然后就可以数位 DP 了。

$DP(p, f_1, f_2, f_3, m_1, m_2, m_3)$ 表示：

- 考虑 $X_i$ 中 $p$ 及以上的数位
- $f_i$ 表示 $X_i$ 中 $p$ 以上的数位是否已经小于 $N$ （已经小于的话后面想放一就放一，否则要考虑放一会不会超过 $N$）。
- $m_i$ 表示 $p$ 及以上的数位模 $A_i$ 的余数。

这样 $\sum_{f_1, f_2, f_3} DP(0, f_1, f_2, f_3, 0, 0, 0)$ 就是答案。

因为 $A_i$ 并不大，所以直接枚举余数转移就可以了。

## [G - Rearranging](https://atcoder.jp/contests/abc317/tasks/abc317_g)

考虑转成图论中的匹配问题。

建图的话就是每一行对应一个点，然后每一个数对应一个点，然后在行和行中的数之间连边。

然后一列对应的就是一个完美匹配，然后就是跑 $M$ 次二分图完美匹配了，如果某一次没有完美匹配存在，那么说明无解。匹配中的一条边$(u, v)$ 当前列第 $u$ 行为数字 $v$。

证明的话就是 Hall's Theorem 及其推广。

To be solved.

## [Ex - Walk](https://atcoder.jp/contests/abc317/tasks/abc317_h)

To be solved.
