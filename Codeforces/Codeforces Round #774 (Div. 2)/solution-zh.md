# Codeforces Round #774 (Div. 2)

[比赛链接](http://codeforces.com/contest/1646)

## A. Square Counting

易得除$a_i = n^2$之外的所有元素之和会小于$n^2$，所以$\dfrac{s}{n^2}$即为答案。

## B. Quality vs Quantity

排个序，蓝色从小优先放，红色从大优先放，然后最优的情况就是蓝色元素的个数刚好比红色元素的个数大一。

枚举所有情况看是否可能即可。

## C. Factorials and Powers of Two

首先，如果只用$2^d$，就是二进制嘛，可以将答案初始化为$popcount(x)$。

然后，还能用阶乘，阶乘增大速度非常快，$10^{12}$以内的阶乘只有13个。

可以直接$O(2^{13})$暴力枚举阶乘的所有使用情况，对于每一种情况会剩下一个数，这个数只用$2^d$，那就是再加上popcount。

## D. Weight the Tree

注意到，相邻的两个节点不可能同时为good，这个直接能想到树形DP经典板子题，那就是树形DP呗。~~（赛后直接想到的~~

其实就是每个节点选和不选都有一个对应的收益，然后选了一个节点就不能选他的父节点，然后就是DFS跑一下树形DP就能得到每个节点选和不选，其子树内的最大收益。

然后要输出方案嘛，既然子树的收益都算出来了就走收益最大的路呗，再DFS一次跑出方案。

## E. Power Board

这题代码量挺少的，就是思路比较难想。

### 观察1

1是非常特殊的一个值，只会再第一行出现且第一行全是1。

后续可以只考虑大于等于2的数。

### 观察2

定义数$x$是好的，当且仅当他不能写成$y^c,c>1$的形式，$r(x) = \{x^i | 1 \le i \le m\}$，$R(x) = \cup_{1 \le x^i \le n} r(x^i)$，$|S|$表示集合$S$**去重**之后的大小。

可以证明对于两个不相等的好的数$x, y$，$R(x) \cap R(y) = \empty$。

由此，所求的集合就可以用多个$R(x)$并起来得到。

### 观察3

按照定义把$R(x)$列出来就能看出来，$|R(x)| = | \{ i \times j | 1 \le i \le k，1 \le j \le m\} |$，其中$k$是令$x^c \le n$成立的最大的c。

可以看出来，$R(x)$的大小与$x$的取值并无关系，而只与$ $k$和$m$有关系，且$k$的取值是$O(\log n)$级别的。

## 做法

假设$f(k, m)$是观察2中$R(x)$的大小，那么可以枚举$k$的所有可能取值，用$O(m \log n)$的时间暴力算出$f(k, m)$的所有可能取值。

这里$m \log n$最大在$10^7$量级，再带个log就铁定超时，实测hash也会超时。可以开个bool数组或者bitset标记某个数是否出现过，然后算有多少个不同的数。

然后就枚举$x$，如果$x$是好的就算出$k$然后给答案加上$f(k, m)$，然后标记后面的$x^c$为不好的；否则就跳过。

这样就可以在$O(n + m\log n)$的时间内解决问题。

## F. Playing Around the Table

abandon.

## 写在最后

今晚在公司加班的时候看了眼CF，发现学弟一波爆发上红，羡慕死了。然而我加班加得人都快废了，这场DE其实都不难，但是自闭卡D卡到死直接掉到蓝名。

现在每天的时间都不一定够我刷CF的题，做的话还怕晚上会睡不着，比如现在，也就是每天LC签到骗自己。现在周六的场也不敢打了毕竟周日还要上班。

焯，下一份工作一定找不加班的。
