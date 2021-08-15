#include "utils.hpp"

using namespace std;

/*
区间频率计算：哈希 记录 值到索引的映射，统计索引个数
*/

class RangeFreqQuery {
    unordered_map<int, vector<int>> mp;
public:
    RangeFreqQuery(vector<int>& arr) {
        for (int i = 0; i < arr.size(); ++i) 
            mp[arr[i]].emplace_back(i);
    }
    
    int query(int left, int right, int value) {
        if (!mp.count(value))
            return 0;
        
        auto &v = mp[value];
        auto r = upper_bound(v.begin(), v.end(), right);
        auto l = upper_bound(v.begin(), v.end(), left - 1);
        return r - l;
    }
};
