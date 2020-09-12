#include "utils.hpp"
using namespace std;

/*
给定一个Excel表格中的列名称，返回其相应的列序号。

例如，

    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28 
    ...

*/

class Solution {
public:
    int titleToNumber(string s) {
        int res = 0;
        for (auto & c : s) {
            res = res * 26 + (c-'A') + 1;
        }
        return res;
    }
};