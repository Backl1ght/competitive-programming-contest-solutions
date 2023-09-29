# AtCoder Beginner Contest 306

# [E - Best Performances](https://atcoder.jp/contests/abc306/tasks/abc306_e)

拿两个 `std::set` 维护，一个放 top k 的元素，一个放剩余的，然后就是简单模拟了。

# [F - Merge Sets](https://atcoder.jp/contests/abc306/tasks/abc306_f)

每一行算贡献，加起来即为答案。假设现在正在处理第 $i$ 行的贡献，那么 $a_{i, j}$ 每超过第 $k \ge i$ 行中的一个元素，都会增加 $1$ 的贡献，注意这里第 $i$ 行的元素其实使用了 $n - i$ 次，所以要特殊处理。

我们可以把 $k = i$ 和 $k > i$ 拆开算，因为 $k = i$ 这样的贡献是固定的。

对于 $k = i$ ，第 $i$ 行中的最大值会产生 $m$ 的贡献，次大值会产生 $m - 1$ 的贡献，以此类推，共 $\sum_{i = 1}^{m} i = \frac{m(m + 1)}{2}$ 。然后一共会用 $n - i$ 次，所以一共是 $(n - i) \frac{m(m + 1)}{2}$ 。（其实还可以把每一行的这个再加起来，一共 $\frac{n(n - 1)}{2} \frac{m(m + 1)}{2}$）

然后就只需要考虑 $k > i$ 的情况了，这种情况下就是算 rank ，由于数据范围较小，可以离散化然后用权值树状数组搞。

# [G - Return to 1](https://atcoder.jp/contests/abc306/tasks/abc306_g)

首先可以删除非强连通的节点，这个两次 `dfs` 搞定。

然后考虑图中所有包含 $1$ 的环，记共 $k$ 个环，第 $i$ 个环长度为 $l_i$ ，那么根据裴蜀定理，问题有解当且仅当 $G = \gcd(l_1, l_2, \dots, l_k) \mid {10^{10^{100}}}$ ，由于后者足够大，式子成立等价于 $G$ 的素因子仅包含 $2$ 和 $5$ 。

这种环的个数可能是无限大，我们不能找出所有这种环然后算公因数。

跑出某个以 $1$ 为根的 $dfs$ 树，然后每条边都对应一个包含 $1$ 的环，我们其实只需要考虑这些环就够了，更进一步，我们只需要考虑点的深度。

记 $P(u, v)$ 表示任意一条从 $u$ 到 $v$ 的路径。对于边 $u \to v$，如果不使用这条边，图中会有一个环 $1 \to v \to P(v, 1)$ ，长度为 $dep(v) + len(P(v, 1))$ ；如果使用这条边，图中会有一个环 $1 \to u \to v \to P(v, 1)$ ，长度为 $dep(u) + 1 + len(P(v, 1))$ 。两个环的 gcd 为 $\gcd(dep(v) + len(P(v, 1)), dep(u) + 1 - dep(v))$ 。然后这里的 $P(v, 1)$ 也可以通过不断把其中一条边变成 $dep(x) + 1 - dep(y)$ 去 deduce，最后变成只剩一条边 $w \to 1$ ，然后这条边也能变成 $dep(w) + 1 - dep(0)$ ，最后变成空。

自此，我们只需要考虑 $\gcd(dep(u) + 1 - dep(v))$ 。

# [Ex - Balance Scale](https://atcoder.jp/contests/abc306/tasks/abc306_h)

To be solved.
