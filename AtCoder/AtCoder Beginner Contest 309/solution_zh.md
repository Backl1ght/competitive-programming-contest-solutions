# AtCoder Beginner Contest 309

## [F - Box in Box](https://atcoder.jp/contests/abc309/tasks/abc309_f)

### 我的解法

对原本的箱子进行旋转，将值最小的作为第一维，次小的作为第二维，剩下的作为第三维。这样子肯定最优。

> 证明：原本满足条件的箱子，旋转之后依旧满足。

CDQ 分治改改就行。

### 官方题解

离散化。

按第一维升序插入箱子，拿一个线段树维护第二维为 $x$ 的箱子，第三维的最小值。

对于要插入的箱子 $(h, w, d)$ ，如果此时线段树中 $[1, w - 1]$ 区间的最小值小于 $d$ ，那么就有解。不然就用 $d$ 更新 $w$ 的值。

## [G - Ban Permutation](https://atcoder.jp/contests/abc309/tasks/abc309_g)

To be solved.

## [Ex - Simple Path Counting Problem](https://atcoder.jp/contests/abc309/tasks/abc309_h)

To be solved.
