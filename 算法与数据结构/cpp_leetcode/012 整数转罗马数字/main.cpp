#include "utils.hpp"

using namespace std;

/*
- 第二种写法更优
*/

class Solution {
public:
    string intToRoman(int num) {
        unordered_map<int, string> strMap = {{1, "I"},{5, "V"}, 
        {10, "X"}, {50, "L"}, {100, "C"}, {500, "D"}, {1000, "M"}, 
        {4, "IV"}, {40, "XL"}, {400, "CD"}, {9, "IX"}, {90, "XC"}, {900, "CM"}};
        vector<int> w{1000,900,500,400,100,90,50,40,10,9,5,4,1};
        string res;
        int m;
        for (auto& t: w) {
            if (t>num) continue;
            m = num / t;  // 除法
            num %= t;
            printf("%d, %s, %d\n", m, strMap[t].c_str(), num);
            for (auto i=0;i<m;++i) res += strMap[t];
            if (num==0) break;
        }
        return res;
    }
};

class Solution2
{
public:
    string intToRoman(int num)
    {
        string result;
        vector<int> store = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        vector<string> strs = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        int storeSize = int(store.size());
        //贪心法
        for (int i = 0; i < storeSize; i++)
        {
            while (num >= store[i])
            {
                result.append(strs[i]);  // 减法
                num -= store[i];
            }
            if (num==0) break;
        }
        return result;
    }
};

// 作者：pinku-2
// 链接：https://leetcode-cn.com/problems/integer-to-roman/solution/zheng-shu-zhuan-luo-ma-shu-zi-cshi-xian-liang-chon/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

int main() {
    cout<<Solution2().intToRoman(3999)<<endl;
}