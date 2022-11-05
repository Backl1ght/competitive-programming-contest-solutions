# Codeforces Round #832 (Div. 2)

## [A. Two Groups](https://codeforces.com/contest/1747/problem/A)

数组和的绝对值即为答案。

## [B. BAN BAN](https://codeforces.com/contest/1747/problem/B)

大概就是尽可能把前面的 `B` 搞到后面，尽可能把后面的 `N` 搞到前面。

答案为 $\lceil \frac{n}{2} \rceil$ ，操作为每次交换正数第 $i$ 个 `BAN` 的 `B` 和倒数第 $i$ 个 `BAN` 的 `N` 。

## [C. Swap Game](https://codeforces.com/contest/1747/problem/C)

先说结论：若 $a_1$ 等于 $\min_{i = 1}^{n} a_i$，则先手必败，反之先手必胜。

推导过程如下：

$a_1 > 0, \exist a_i = 0$ ，此时先手必胜；

$a_1 = 1, a_i > 0$ 时，走一步到先手必胜，所以先手必败；

$a_1 > 1, \exist a_i = 1$ 时，走一步到先手必败，所以先手必胜。

$a_2 = 2, a_i > 1$ 时，走一步到先手必胜，所以先手必败。

以此类推，观察可得 $a_1$ 是最小值时先手必败，并且走一步之后 $a_1$ 就不是最小值了，先手必胜。

## [D. Yet Another Problem](https://codeforces.com/contest/1747/problem/D)

特判全 $0$ 的情况。

**观察**： 操作$a_{L \dots R}$相当于把 $a_{L \dots R}$ 变成了 $\oplus_{i = L}^{R} a_i$。
**推论**： 若 $\oplus_{i = l}^{r} a_i \ne 0$ ，则无解。因为不管怎么操作，$\oplus_{i = l}^{r} a_i \ne 0$ 的值不会变。

现在只需要考虑 $\oplus_{i = l}^{r} a_i = 0$ 的情况。

易得：若 $r - l + 1$ 为奇数，则一次就能搞定。同理，若 $a_l = 0$ 或 $a_r = 0$ 则一次就能搞定。

现在只需要考虑 $r - l + 1$ 为偶数，且 $a_l$ 和 $a_r$ 均不为 $0$ 的情况。这种情况下至少需要两次操作，因为操作不能同时包括 $a_l$ 和 $a_r$ 。

如果存在某个 $p$ 使得 $p \in [l, r]$ 且 $p - l + 1$ 为奇数且 $\oplus_{i = l}^{p} a_i = 0$ ，则 $r - (i + 1) + 1$ 也为奇数且 $\oplus_{i = p + 1}^{r} a_i = 0$ 。所以如果存在这样的 $p$ 就能用两次操作解决问题，否则就不行。

然后就是简单模拟了。

## [E. List Generation](https://codeforces.com/contest/1747/problem/E)

参考[cf1747-sol](https://www.luogu.com.cn/blog/340163/cf1747-sol)。