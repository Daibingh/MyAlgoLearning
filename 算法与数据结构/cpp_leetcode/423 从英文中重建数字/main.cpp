#include "utils.hpp"

using namespace std;

/*

给定一个非空字符串，其中包含字母顺序打乱的英文单词表示的数字0-9。按升序输出原始的数字。

注意:

输入只包含小写英文字母。
输入保证合法并可以转换为原始的数字，这意味着像 "abc" 或 "zerone" 的输入是不允许的。
输入字符串的长度小于 50,000。
示例 1:

输入: "owoztneoer"

输出: "012" (zeroonetwo)
示例 2:

输入: "fviefuro"

输出: "45" (fourfive)

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reconstruct-original-digits-from-english
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

*/


// 通用暴力解法，超时
class Solution {

    vector<string> num = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    bool helper(unordered_map<char, int> charCnt, int st, int cnt, string& res) {
        
        for (int i=st;i<10;++i) {
        	auto bak = charCnt;
            if (cnt>0 && contains(charCnt, i)) {
                res += static_cast<char>(i+'0');
                cnt -= num[i].size();
                // cout<<res<<", "<<cnt<<endl;
                if (!helper(charCnt, i, cnt, res)) {
                    res.pop_back();
                    cnt += num[i].size();
                    charCnt = bak;
                }
                else return true;
            }
        }
        // 底层返回条件
       if (cnt==0) return true;
       else return false;
    }

    bool contains(unordered_map<char, int>& charCnt, int idx) {
        unordered_map<char, int> bak = charCnt;
        for (const auto & c : num[idx]) {
            if (bak[c] <= 0) {
                return false;
            }
            --bak[c];
        }
        charCnt = bak;
        return true;
    }

public:
    string originalDigits(string s) {
        unordered_map<char, int> charCnt;
        int cnt = s.size();
        for (const auto & c : s) {
            ++charCnt[c];
        }
        string res;
        helper(charCnt, 0, cnt,  res);
        return res;
    }
};


// 利用规律，特殊字符
class Solution2 {
public:
    string originalDigits(string s) {
        unordered_map<char, int> charCnt;
        for (const auto & c : s) {
            ++charCnt[c];
        }
        vector<int> res(10);
        res[0] = charCnt['z'];
        res[2] = charCnt['w'];
        res[4] = charCnt['u'];
        res[6] = charCnt['x'];
        res[8] = charCnt['g'];
        res[3] = charCnt['h'] - res[8];
        res[5] = charCnt['f'] - res[4];
        res[7] = charCnt['s'] - res[6];
        // nine, one
        res[1] = charCnt['o'] - res[0] - res[2] - res[4];
        res[9] = charCnt['i'] - res[5] - res[6] - res[8];

        string str;
        for (int i=0;i<10;++i) {
            str += string(res[i], i+'0');
        }
        return str;
    }
};

int main() {
	string s = "zeroonetwothreefourfivesixseveneightnine";
	// s = "onetowthree";
	auto res = Solution().originalDigits(s);
	cout<<res<<endl;
}
