# Codeforces Round #787 (Div. 3)

## A. Food for Animals

优先买前两种，再用第三种。

## B. Make It Increasing

感觉自己写复杂了。

$dp_{i, j}$表示第$i$个元素使用$j$次操作的代价。

$$
dp_{i + 1, k} = 
\left\{
    \begin{aligned}
    &\min_j dp_{i, j} + k & f(a_i, j) < f(a_{i + 1}, k)\\
    &\inf & else\\
    \end{aligned}
\right.
$$
其中$f(x, y)$表示对$x$用$y$次操作后的结果。

## C. Detective Task

对于$i$，如果前面没有`0`且后面没有`1`，那么$i$就是一个可行的解。

预处理一下前后缀就可以线性解决。

## D. Vertical Paths

观察可得：路径数量等于叶子的数量。

枚举所有的叶子，对于每一个叶子，不断往父亲跳直到遇到已经经过的节点，每遇到一个节点就将其加入这个叶子对应的路径。

## E. Replace With the Previous, Minimize

维护一个映射$f(ch)$表示字符串中所有的$ch$已经被替换为$f(ch)$。

然后从前往后枚举字符串中的字符，遇到一个不是`a`的字符，就对其使用操作直到操作耗尽或者其变成`a`。

由于只有26个字母，所以维护还是比较简单的。

## F. Vlad and Unfinished Business

首先，考虑$x = y$的情况，这是一个经典的问题。从$x$开始DFS，对于边$u \rightarrow v$，如果以$v$为根的子树包含需要去的节点，那么边$u \rightarrow v$对答案有$2$的贡献（最优的情况下会经过这条边两次，递归和回溯各一次）。假设这种情况的答案为$sum$，跑遍DFS就可以算出来。

考虑$x = y$不一定成立的情况。假设已经经过了所有需要去得节点，且所有需要去的节点中最后一个去的是$z$，并且现在停在$z$。此时耗费的代价为$sum - dep_z$，其中$dep_i$表示节点$i$的深度。现在只需要再从$z$走到$y$就可以了，代价为$z$到$y$的最短路，这个借助LCA就可以$O(n\log n) \sim O(\log n)$。这里我用的树剖算LCA。

由于计算是$O(\log n)$的，$z$的可能取值有$O(n)$种，直接枚举所有要去的节点即可。

总的时间复杂度是$O(n \log n)$，瓶颈在于LCA的计算。

## G. Sorting Pancakes

DP。

令$f_{i, j, k}$表示以$i$结尾，最后一个元素等于$j$，且前缀和为$k$的最小代价。易得答案为$\min_j f_{n - 1, j, m}$。$f_{i, j, k}$可以从$f_{i - 1, l, k - j}, l \ge j$转移得到。这样子的时间复杂度是$O(nm^3)$的，不够优秀。

令$g_{i, j, k}$表示以$i$结尾，最后一个元素**大于等于**$j$，且前缀和为$k$的最小代价。易得答案为$g_{n - 1, 0, m}$。这样$g_{i, j, k}$就可以直接从$g_{i - 1, j, k - j}$转移得到，可以不用枚举$l$，时间复杂度为$O(nm^2)$。

为了方便计算，记录$b$表示$a$的前缀和，$id$表示将煎饼按下标排序后第$i$个煎饼的下标，$c$表示$id$的前缀和。

转移的时候：
- 如果$b_i \ge k$，则说明需要借助向右移动的操作，将多余的煎饼移动到$i+1$，使得前缀和为$k$。代价为$b_i - k$。
- 否则说明需要借助向左移动的操作，将不足的煎饼移动到$i$使得前缀和为$k$。需要移动的数量是$d = k - \max(k - j, b_i)$，易得最优的操作肯定是移动离得近的煎饼，也就是说需要将第$k -d + 1$个煎饼到第$k$个煎饼移动到$i$，代价为$s_{k} - s_{k - d} - i \times d$。

## 写在最后

下班的时候就只剩1h了，F结束后几分钟过的，G还没时间看。