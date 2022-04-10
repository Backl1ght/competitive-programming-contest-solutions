# Google Code Jam 2022 Round1A

## Double or One Thing

### 做法1

假设当前字符比下一个字符小，那么复制一遍肯定更优。

假设当前字符比下一个字符大，那么复制一遍肯定更优。

假设当前字符和下一个字符相等，那么就看下一个不等的字符的大小，更大就这一串全复制，不然就全不复制。

### 做法2

从后面开始贪心，每次看是否复制，贪心的选小的。

## Equal Sum

比赛的时候想到了利用二进制来构造任何数，但是就是差一步。

首先，把$\{2^i | 0\le i \le 29\}$共30个数加入$A$，剩下70个数随意。

然后再输入进来100个数。

考虑先将后170个数分成两个集合$A$和$B$，记$S(x)$表示集合$x$中元素之和。依次考虑每一个数，每次将数加入较小的那个集合，易得这样的话$S(A)$和$S(B)$的差值是小于$10^9$的。

后面考虑用2的幂次来消除差值。现在需要划分的200个数都确定了，他们的和能确定，最后两个集合相等，那么其中一个集合的和$S$也确定了。

现在考虑把较小的那个集合，假设它的元素和为$S^{\prime}$吧，用2的幂次补到$S$。易得$S$的取值介于$S(A)$和$S(B)$之间，所以$d = S - S^{\prime}$的值会小于$10^9。然后根据$d$的二进制可以轻易做到。

## Weightlifting

比赛的时候没想出来，写了一小时爆搜都没恰到部分分。

对于一个区间内的训练(exercise)，可以先将区间内共有的负重(weights)加入栈中，对于该区间而言加入的顺序不影响结果，等这个区间都处理完了之后，再依次出栈。

对于一个区间，可以将其拆分为两个部分，先做左区间，在做右区间，对于每一个区间，都利用上述观察，这样问题就可以通过一个递归的过程解决，然后结合记忆话搜索或者说区间DP，就可以解觉问题，复杂度大概在立方级别。

具体而言就是，记$c(l, r)$为区间$[l,r]$中所有训练共有的负重数量，$dp(1, n)$为区间$[l, r]$除了共有的负重之外还需要的代价。那么最后的答案就是$dp(1, E) + 2 c(1, E)$，然后有
$$
dp(l, r) = 
\left\{
    \begin{aligned}
        &0 & l = r \\
        &\min_{l \le i \le r - 1}(dp(l, i) + dp(i + 1, r) + 2(c(l, i) - c(l, r)) + 2 (c(i + 1, r) - c(l, r))) & \text{otherwise}\\
    \end{aligned}
\right.
$$