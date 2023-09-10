# AtCoder Beginner Contest 319

## [E - Bus Stops](https://atcoder.jp/contests/abc319/tasks/abc319_e)

从某个时刻 $t$ 出发的到达时间 $f(t)$ 可以 $O(n)$ 模拟计算。

然后 $f(t)$ 会有一个周期为 $\operatorname{lcm}(P_1, P_2, \dots, P_N)$ ，简单证明的话感觉可以类比一下天干地支之类的。然后由于 $P_i \le 8$ ，所以$\operatorname{lcm}(P_1, P_2, \dots, P_N) | \operatorname{lcm}(1, 2, \dots, 8)$ 且 $\operatorname{lcm}(1, 2, \dots, 8) = 840$ 。

预处理 $0$ 到 $839$ 出发的耗时，然后就是简单算数了。

## [F - Fighter Takahashi](https://atcoder.jp/contests/abc319/tasks/abc319_f)

一定是先尽可能打怪，然后再嗑药，因为 $\forall a, b, k > 0, a * k + b < (a + b) * k$ 。所以对于怪可以直接贪，拿个优先队列维护。

然后对于药，因为数量比较少，所以可以跑 bit mask dp 。

## [G - Counting Shortest Paths](https://atcoder.jp/contests/abc319/tasks/abc319_g)

To be solved.
