#include <bits/stdc++.h>

using namespace std;

/*
输入一个整数 n ，求1～n这n个整数的十进制表示中1出现的次数。

例如，输入12，1～12这些整数中包含1 的数字有1、10、11和12，1一共出现了5次。

--------------------------
res = sum ( 所有位上出现 1 的个数 )
从 低位到 高位 扫描, 根据当前位上的取值, 分情况累加
42x1
  ^

*/


class Solution {
public:
    int countDigitOne(int n) {
        long m = 1;
        int res  = 0;
        int high = n/10,  cur = n%10, low = 0;
        while (high !=0 || cur!=0) {
            if (cur ==0) res += high*m;     // 42-0-1:    ( 00->41 ) x (0->9)                
            else if (cur==1) res += high*m + (low + 1);  // 42-1-1  ( 00->41 ) x (0->9) + (42) x (0->1)
            else res += (high+1)*m;  // 42-3-1:  (00->42) x (0->9)
            low += cur*m;
            cur = high % 10;
            high /=10;
            m *= 10;
        }
        return res;
    }
};