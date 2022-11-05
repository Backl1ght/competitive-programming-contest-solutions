# AtCoder Beginner Contest 237

## [E - Skiing](https://atcoder.jp/contests/abc237/tasks/abc237_e)

一眼最短路，但是并不能直接用 Dijkstra 跑，因为有负权。

通过修改建图方式可以去掉负权，具体如下：从点 $u$ 到 点 $v$ ，如果高度下降，那么边权为 $0$ ，反之边权为 $h_v - h_u$ 。那么从 $0 \to v$ 的收益就是 $h_0 - h_v - d_v$ ， $d_v$ 表示 $0$ 到 $v$ 的最短路。

## [F - |LIS| = 3](https://atcoder.jp/contests/abc237/tasks/abc237_f)

记 $dp(n, a_1, a_2, a_3)$ 表示长度为 $n$ ，所有子序列长度为 $k$ 的子序列中，子序列结尾的最小值为 $a_k$，的方案数。

转移的时候枚举第 $n + 1$ 位上的数字 $x$ ，如果 $x \le a_1$，那么就能从 $dp(n, a_1, a_2, a_3)$ 转移到 $dp(n + 1, x, a_2, a_3)$ ；否则，如果 $a_1 < x \le a_2$ ，那么就能在 $a_1$ 对应的子序列后面插入 $x$，从而转移到 $dp(n + 1, a_1, x, a_3)$ ； $a_3$ 类似。

时间复杂度为 $O(nm^4)$。

## [G - Range Sort Query](https://atcoder.jp/contests/abc237/tasks/abc237_g)

问题只关心 $x$ 的位置，那么就可以只维护相对 $x$ 的大小关系，令
$$
a_i = 
\left\{
\begin{aligned}
0 & \text{, if } p_i \le x \\
1 & \text{, else } \\
\end{aligned}
\right.
$$

对于操作 `1 l r` ，就是把区间内的 $0$ 都移动到前面，这个通过计算区间和$sum$，把区间前 $sum$ 个元素置 $0$，区间内剩余元素置 $1$ 即可。

操作 `2 l r` 类似。

这样得到的结果还不足以判断 $x$ 的位置，但是如果再计算 $x - 1$ 的结果，两个结果不同的位置就是 $x$ 的位置。

## [Ex - Hakata](https://atcoder.jp/contests/abc237/tasks/abc237_h)

处理出所有回文子串，假设每个回文子串对应一个节点，如果 $s$ 是 $t$ 的子串则从 $s$ 对应节点向 $t$ 对应节点连边，显然这是个 DAG ，同时是个传递闭包。现在问题转化为选择的节点间不能有路径，最多能选几个节点（ DAG 最小链覆盖）。

然后就是 Dilworth’s theorem 转成二分图最大匹配了，二分图板子年久失修所以用了最大流板子，针对二分图的算法可以了解 Hungarian Algorithm 或者 Hopcroft-Karp Algorithm。