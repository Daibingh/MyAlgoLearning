#include "utils.hpp"
using namespace std;

/*

Given n, how many structurally unique BST's (binary search trees) that store values 1 ... n?

Example:

Input: 3
Output: 5
Explanation:
Given n = 3, there are a total of 5 unique BST's:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
--------------------------------------
动态规划，递推方程：f[n] = \sum_{i=1}^{n} { f[i-1] * f[n-i] }
1...n, 以任意 i 属于 [1,n] 为根，其左右两侧都是一个二叉搜索树，它们可能的个数分别是 f[i-1], f[n-i] , 所以以 i 为根的个数可以表示成
f[i-1]*f[n-i]

*/


class Solution {
public:
    int numTrees(int n) {
        vector<int> f(n+1, 0);
        f[0]=f[1] =1;
        for (int i=2;i<=n;++i) {
            for (int j=1;j<=i;++j) {
                f[i] += f[j-1] * f[i-j];  // 1,2,..., j ,...,i ; (j-1) j (i-j) 
            }
        }
        return f[n];
    }
};