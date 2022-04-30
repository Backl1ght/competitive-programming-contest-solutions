# 2022 Google Kick Start Round B

## Infinity Area

易得操作的步数有限，直接模拟即可。

## Palindromic Factors

$O(\sqrt{n})$枚举因数即可。

## Unlock the Padlock

观察可得：每次一定是在一个区间的基础上再向左或者向右扩展一个元素，然后将区间内的元素值都搞成新元素的值。

然后就是区间DP了。记$dp_{l, r, 0/1}$表示区间$[l, r]$，且区间内元素值等于$a_l/a_r$。然后$[l, r]$可以由$[l, r - 1]$和$[l + 1, r]$转移得到。

时间复杂度为$O(n^3)$。

## Hamiltonian Tour

数据量对于Hamiltonian回路问题过大，不太可做，应该是构造的问题。

对于每一个$B_{i, j}$，其内部可以有一个Hamiltonian回路。

考虑合并两个Hamiltonian回路，由于$B_{i, j}$的大小是2乘2的，所以两个$B$中的元素一定可以合并成一个新的Hamiltonian回路，跑一个DFS不断合并相邻元素即可。

注意图可能不连通。