# AtCoder Beginner Contest 321

## [E - Complete Binary Tree](https://atcoder.jp/contests/abc321/tasks/abc321_e)

完全二叉树有个性质：节点 $x$ 的子树中，与 $x$ 距离为 $k$ 且最靠左的点 $l$ 为 $x * 2^k$ ，与 $x$ 距离为 $k$ 且最靠右的点 $r$ 为 $(x + 1) * 2^k - 1$ 。如果前者不在树中则 $x$ 的子树中没有与 $x$ 距离为 $k$ 的点；后者如果不在树中就和 $n$ 取最小值。然后数量就是 $r - l + 1$ 。

$x$ 子树中的点就直接算，不是 $x$ 子树中的点就不断往父亲节点跳，然后累加。跳父亲的情况要只算兄弟节点那边的，不然会重复计数。

## [F - #(subset sum = K) with Add and Erase](https://atcoder.jp/contests/abc321/tasks/abc321_f)

只考虑加的话，那么就是 01 背包。

这题还加了删除，其实就是增加的逆。

增加的时候是从 $k$ 到 $x$ 支持 `dp[k] += dp[k - x]` 。

删除的时候就是反过来，然后减，即从 $x$ 到 $k$ 执行 `dp[k] -= dp[k - x]` 。

## [G - Electric Circuit](https://atcoder.jp/contests/abc321/tasks/abc321_g)

To be solved.
