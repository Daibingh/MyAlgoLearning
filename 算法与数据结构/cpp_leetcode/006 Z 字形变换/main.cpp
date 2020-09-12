#include "../utils.hpp"

using namespace std;

/*
- 找规律的题，通过字符的分布周期，确定所在的行
- 时 O(n), 空 O(n)
*/


class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows<=1) return s;
        vector<string> resc(numRows, "");
        int perd = 2 * numRows -2;  // 周期
        for (auto i=0;i<s.size();++i) {
            int m = i % perd;
            int n = m < numRows ? m : perd - m;  // 确定第几行
            resc[n] += s[i];
        }
        string res;
        for (auto& s: resc) {
            res += s;
        }
        return res;
    }
};


int main() {
    string s = "LEETCODEISHIRING";
    int n = 4;
    auto res = Solution().convert(s, n);
    cout<<res<<endl;
}