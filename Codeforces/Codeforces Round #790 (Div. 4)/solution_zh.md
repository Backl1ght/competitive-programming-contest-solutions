# Codeforces Round #790 (Div. 4)

## A. Lucky?

简单模拟。

## B. Equal Candies

记$sum$为元素和，$mi$为最小值，则答案$ans = sum - n * mi$。

## C. Most Similar Words

直接暴力。

## D. X-Sum

直接暴力。

## E. Eating Queries

贪心先用大的肯定更优，直接降序排序之后算个前缀和，之后每个询问就可以借助二分$O(\log n)$回答。

## F. Longest Strike

将$a$中出现次数大于等于$k$次的元素存到$b$中，然后答案就是$b$中最长的连续子数组了，这个就是循环一遍的事情。

## G. White-Black Balanced Subtrees

简单DFS。

## H2. Maximum Crossings (Hard Version)

对于$a_i \ne a_j$，则这两者的选择相互不影响答案。

如果同时有多个$i$使得$a_i = x$，那么肯定是让更小的$i$选择更靠右的点会更优。具体实现的话就是将下面那条线的$1$段细分成$n$段，然后选择的时候优先从后面开始选。

假设上面第$i$段选择了下面第$b_i$段，那么答案就是$b_i$中的逆序对数，这个就是经典问题了。