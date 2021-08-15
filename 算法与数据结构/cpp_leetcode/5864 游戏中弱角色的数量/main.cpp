#include "utils.hpp"

using namespace std;

/*
你正在参加一个多角色游戏，每个角色都有两个主要属性：攻击 和 防御 。给你一个二维整数数组 properties ，其中 properties[i] = [attacki, defensei] 表示游戏中第 i 个角色的属性。

如果存在一个其他角色的攻击和防御等级 都严格高于 该角色的攻击和防御等级，则认为该角色为 弱角色 。更正式地，如果认为角色 i 弱于 存在的另一个角色 j ，那么 attackj > attacki 且 defensej > defensei 。

返回 弱角色 的数量。
======================================================
分析：关键在于排序的方法！

- 给二维数组排序
- 攻击力大的在前面
- 如果攻击力想等得则防御力小的在前面

*/


class Solution {
public:
    int numberOfWeakCharacters(vector<vector<int>>& prop) {
        int n = prop.size();
        sort(prop.begin(), prop.end(), [](const vector<int>& a, const vector<int>& b){ return a[0]==b[0] ? a[1]<b[1] : a[0]>b[0] ;});
        int res  = 0;
        int maxVal = 0;
        for (int i=0;i<n;++i) {
            if (maxVal > prop[i][1]) {
                ++res;
            } else {
                maxVal = prop[i][1];
            }
        }
        return res;
    }
};