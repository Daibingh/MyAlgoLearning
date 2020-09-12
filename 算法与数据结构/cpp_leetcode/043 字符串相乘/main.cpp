#include "utils.hpp"

using namespace std;

/*
 
            0   1   2    input index
        ----------------
            1   2   3    str1
            4   5   6    str2
        ---------------
            7   3   8
            ...
-----------------------        
0   1   2   3   4   5  output index

规律：
output len = len(str1)+len(str2)
str1[i] * str2[j] => output[i+j], output[i+j+1]

先用 vector<int> 存结果，最后转 str

*/

class Solution {
public:
    string multiply(string num1, string num2) {
        vector<int> res(num1.size()+num2.size(), 0);
        for (int i=num1.size()-1;i>=0;--i) {
            for (int j=num2.size()-1;j>=0;--j) {
                int idxL=i+j, idxR=i+j+1;
                res[idxR] += charProduct(num1[i], num2[j]);
                // cout<<sum<<endl;
                res[idxL] +=  res[idxR] / 10;
                res[idxR] %= 10;
            }
        }
        string resStr;
        for (const auto & t : res) {
            // cout<<t<<endl;
            if (!t && resStr.empty()) continue;
            resStr += static_cast<char>(t+'0');
        }
        if (resStr.empty()) return "0";
        return resStr;
    }
    
    int charProduct(char a, char b) {
        return (a-'0')*(b-'0');
    }
};