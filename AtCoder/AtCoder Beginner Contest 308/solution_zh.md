# AtCoder Beginner Contest 308

## [E - MEX](https://atcoder.jp/contests/abc308/tasks/abc308_e)

前缀和，后缀和。

## [F - Vouchers](https://atcoder.jp/contests/abc308/tasks/abc308_f)

从小到大枚举物品，然后用双指针和优先队列维护可用的优惠券，每次贪心拿优惠最大的。

> This greedy algorithm is valid because we ultimately need to maximize the sum of $D_i$ of the coupon used, and those coupons used in an optimal solution can be used however early as long as applicable.

## [G - Minimum Xor Pair Query](https://atcoder.jp/contests/abc308/tasks/abc308_g)

### 我的解法

考虑在一颗 01 字典树中，对于其中一个节点 $u$ ，如果其子树中有分叉，那么肯定是子树中的答案更优。所以只需要考虑叶子到根的路径中第一次分叉的地方，然后每次插入或者删除只会影响一条链，所以单词复杂度为 $O(\log V)$ 搞。

### 官方题解

其实我的解法再推一下就是：答案一定是排名相邻的数产生的。

然后就是 `std::multiset` 维护一下。

## [Ex - Make Q](https://atcoder.jp/contests/abc308/tasks/abc308_h)

To be solved.
