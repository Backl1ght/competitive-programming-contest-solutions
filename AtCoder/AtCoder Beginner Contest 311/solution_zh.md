# AtCoder Beginner Contest 311

## [C - Find it!](https://atcoder.jp/contests/abc311/tasks/abc311_c)

写的时候没注意题干，写了普适版本的，大概就是拓扑排序，然后就只用考虑环和环能到达的点。然后再 dfs，如果遇到了本次遍历过的点说明找到了环，环之外的点出发的话不会遇到本次遍历过的点。

注意每个点只有一条出边，所以随便从一个点开始走，一定能遇到已经遍历过的点。

## [D - Grid Ice Floor](https://atcoder.jp/contests/abc311/tasks/abc311_d)

就 BFS 搜，每个格子加一个方向维度就行。因为一定会滑到底，所以起点不重要，只需要额外考虑经过格子的方向即可。

## [E - Defect-free Squares](https://atcoder.jp/contests/abc311/tasks/abc311_e)

### 做法1

观察到满足条件的正方形大小有单调性，如果以 $(x, y)$ 为右下角，以 $d$ 为边长的正方形有洞，那么以 $d + 1$ 为边长的正方形也一定会有洞。

然后就二分完事。

### 做法2

考虑 DP ，其实 $dp(i, j)$ 的结果至多在 $\min\{dp(i - 1, j - 1), dp(i - 1, j), dp(i, j - 1)\}$ 的基础上增加 $1$ 。这就已经足够搞 $O(NM)$ 的 DP 了。

然后其实如果 $(i, j)$ 不是洞的话， $dp(i, j)$ 其实就是 $\min\{dp(i - 1, j - 1), dp(i - 1, j), dp(i, j - 1)\} + 1$ 。

## [F - Yet Another Grid Task](https://atcoder.jp/contests/abc311/tasks/abc311_f)

一眼 DP 。

记 $dp(i, j)$ 为前 $j$ 列，第 $j$ 列上的黑点最高在 $i$ 的方案数。然后虚拟一个第 $n$ 行表示对应列没有黑点。然后就有

$$
dp(i, j) = \sum_{k = i - 1}^{n} dp(k, j - 1)
$$

$\sum_{i = 0}^{n} dp(i， m - 1)$ 即为答案。

## [G - One More Grid Task](https://atcoder.jp/contests/abc311/tasks/abc311_g)

想到之前遇到过给一个数组 $a$ ，然后求 $a$ 一段区间内最小值乘区间和的最大值。然后还有一堆变种，比如最小值乘最大值之类的。大概都可以借助单调栈线性预处理出每个位置作为最小值的最大区间，然后最小值有了，借助数据结构区间查询或者预处理求出另外一个参数，然后更新答案。总的时间复杂度 $O(n \log n)$ 或者 $O(n)$ 。

然后这题的话，由于范围比较小，可以枚举列的范围，然后把二维压到一维，再然后就是前面说的了。

## [Ex - Many Illumination Plans](https://atcoder.jp/contests/abc311/tasks/abc311_h)

To be solved.
