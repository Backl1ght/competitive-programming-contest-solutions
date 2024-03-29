# Google Code Jam Round 1B 2022

## Pancake Deque

贪心，队首队尾两个候选，贪心先选较小的。线性模拟一下就可以了。

## Controlled Inflation

猜结论：同一个人的物品必定是非降序或者非升序。

这样输入之后，对每一个人的物品排下序，然后就可以DP了。

记$dp_{i, j}$表示前$i$个人，第$i$个人的物品是升序$(j=0)$或者降序$(j=1)$，的最小代价。然后转移方程也很容易的能推出来。

为了防止讨论边界，加入物品全为$0$的第$0$个人，这样$\min\{dp_{n, 0}, dp_{n, 1}\}$就是答案。

## ASeDatAb

### Test Set 1

看到参数随机就想着直接乱搞了。

第一次随便搞个数输出，之后每一次询问，如果上一次询问返回$x$，那么这一次询问就搞$x$个$1$放在开头，然后补$0$。

过题概率$P = \text{能过}\%$。

### Test Set 2

假设$P_i$是一系列操作，能让长度为$2^i$的串变成全$0$，即必胜策略。

假设$P_i + P_i$表示$P_i$中元素对应位置相加，$P_i + 0$表示$P_i$中元素在尾部补0，$0$的个数和对应元素的长度相等。

对于长度为$1$的串，因为非全$0$，所以只能是$1$。所以$P_0 = \{\text{"1"}\}$;

对于长度为$2$的串，假设左半和右半相等，因为非全$0$，所以只能是$11$。如果现在没赢，那就说明假设错误，原本是$01$或者$10$，所以可以借助一次$10$操作，把两半搞成相等的，然后再通过至多一次$11$搞成全零。所以$P_1 = \{\text{"11"}, \text{"01"}, \text{"11"}\}$

以此类推，对于长度为$2^k$的串，假设左半边和右半边相等，那么通过将$P_{k - 1} + P_{k - 1}$到达全$0$；不然就说明左右两边不等，通过$P_{k - 1} + 0$可以达到左右两边相等，但是不清楚什么时候相等的，所以每一次操作完都再做一次$P_{k - 1} + P_{k - 1}$。

借助递归或者递推可以算出$P_3$，其大小为$255$，所以可以稳定在$300$步内解决。

## 写在最后

第一题6:55过的，第二题25：34过的，第三题小数据51:40过的，看榜rank差不多200？感觉晋级差不多稳了就run了，毕竟明天还得上班。

其实也不是完全没思路，因为大数据的条件下，一定是有必胜策略才能过的，感觉是博弈论题，但是没想到必胜策略。

这场感觉是手速场，前两题害怕最后一个点挂掉检查了好久，不过最后还是靠着手速rank 293，