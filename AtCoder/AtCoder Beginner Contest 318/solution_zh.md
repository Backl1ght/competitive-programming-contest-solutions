# AtCoder Beginner Contest 318

## [E - Sandwiches](https://atcoder.jp/contests/abc318/tasks/abc318_e)

记录每个数出现的位置，假设数 $x$ 出现的位置依次为 $P_{x, 1}, P_{x, 2}, \dots, P_{x, c_x}$。

那么对于 $(P_{x, a - 1}, P_{x, a})$ 这个区间中的所有数，都可以作为 $A_j$ ，然后 $P_{x, a - 1}$ 及其左侧的 $x$ 可以作为 $A_i$ ， $P_{x, a}$ 及其右侧的 $x$ 可以作为 $A_k$ 。然后就是简单数数了。

## [F - Octopus](https://atcoder.jp/contests/abc318/tasks/abc318_f)

易得满足条件的位置会是连续的一段区间，然后就只需要求边界。

因为是边界，所以左边界满足 $k$ 可行但是 $k - 1$ 不可行，右边界满足 $k$ 可行但是 $k + 1$ 不可行。

因为是边界，所以必定有 $|k - x_i| = l_i$，这样的位置至多有 $O(N^2)$ 个。

然后对于某个候选的边界位置 $k$ ，可以 $O(N \log N)$ 或者 $O(N)$ 判断这个位置是否可行。

前者就是算出所有 $y_i = |k - x_i|$ , 然后升序排序，然后如果对于 $i \in [1, N]$ 都有 $y_i < l_i$ 那么就可行，否则就不可行。

后者也是和 $l_i$ 一一对应，但是算 $y_i$ 的时候是从 $k$ 开始向两边扩展，这样也能按升序找到所有 $y_i$ 。


## [G - Typical Path Problem](https://atcoder.jp/contests/abc318/tasks/abc318_g)

### 做法1 - 网络流

转成最大流问题，大概就是：

- 拆点，入点和出点间连容量为 $1$ 的边，意思是一个点只能经过一次。
- 对于原图中的边 $(u, v)$，在 $in(u)$ 和 $out(v)$ 之间连容量为 $1$ 的边，在 $in(v)$ 和 $out(u)$ 之间连容量为 $1$ 的边。对应原图中的无向边。
- 从 $S$ 向 $out(B)$ 连一条容量为 $2$ 的边。
- 从 $out(A)$ 和 $out(C)$ 向 $T$ 连一条容量为 $1$ 的边。
- 如果 $S$ 到 $T$ 的最大流为 $2$ ，说明有解。两条流分别对应路径 $B->A$ 和路径 $B->C$。

### 做法2 - 圆方树

对原图建圆方树，路径存在对应圆方树上 $A$ 到 $C$ 的路径中存在一条边到 $B$ 。

## [Ex - Count Strong Test Cases](https://atcoder.jp/contests/abc318/tasks/abc318_h)

To be solved.
