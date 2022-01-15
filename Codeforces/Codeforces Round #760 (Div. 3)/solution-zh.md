# Codeforces Round #760 (Div. 3)

[比赛链接](http://codeforces.com/contest/1618)

## A. Polycarp and Sums of Subsequences

排个序，$a_0$和$a_1$必定是答案。

如果$a_0 + a_1 = a_2$，那么$a_3$是答案，否则$a_2$是答案。

## B. Missing Bigram

先初始化答案为第一个bigram。

对于后面的bigram，如果其首字符和答案的末尾相等，那么就可以将其尾字符加到答案末尾。

不然就说明中间缺了bigram，可以直接将其添加到答案末尾。如果没有出现这种情况，那么最后需要添加任一字符到答案末尾。

## C. Paint the Array

根据相邻元素要不同可以想到将原数组按下标奇偶性拆成两个数组，分别计算两个数组的gcd，这两个gcd就是备选的d。

是否可行可以线性check。

## D. Array and Operations

首先，有$n - 2k$个元素会完整的加到答案中，肯定是选最小的$n - 2k$个元素。这里先排个序。

然后就是后$2k$个元素，由于是下取整，所以让小的去除大的就可以得到0，所以只需要尽量避免用两个相等的数。让第$i$个元素作为分子，第$i + k$个元素作为分母就行了。

## E. Singers' Tour

易得：

$$
\sum_{i=1}^{n} a_i = \frac{\sum_{i = 1}^{n} b_i}{\sum_{i = 1}^{n} i} \\
b_{i} - b——{i - 1} = \sum_{j = 1}^{n} a_j - n \times a_i
$$

通过第一个式子可以算出$a$的和。然后结合第二个式子算出$a_2, a_3, \dots, a_n$，最后算出$a_1$。

