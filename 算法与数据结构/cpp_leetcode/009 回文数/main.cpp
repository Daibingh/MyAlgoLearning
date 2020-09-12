#include "../utils.hpp"

using namespace std;

/*
- 给出三种方法
*/

class Solution {
public:
    // 转字符串
    bool isPalindrome3(int x) {
        string s = to_string(x);
        for (auto l=s.begin(), r=s.end()-1; l<=r; ++l,--r) {
            if (*l!=*r) return false;
        }
        return true;
    }

    // 不转字符串
    bool isPalindrome2(int x) {
        if (x<0 || (x>0 && x%10==0)) return false;
        int sum = 0;
        int bak = x;
        while (x!=0)
        {   
            int m = x%10;
            if (sum > INT_MAX/10 || (sum==INT_MAX && m>7)) return false;  // 溢出肯定不是回文数
            sum = sum*10 + m;
            x /= 10;
        }
        cout<<sum<<endl;
        if (sum==bak) return true;
        return false;
    }

    // 只计算到中间
    bool isPalindrome(int x) {
        if (x<0 || (x>0 && x%10==0)) return false;
        int sum = 0;
        int bak = x;
        while (x>sum)
        {   
            int m = x%10;
            sum = sum*10 + m;
            x /= 10;
        }
        cout<<sum<<endl;
        return (x==sum) || x== sum/10;
    }
};

int main() {
   cout<< Solution().isPalindrome(12321)<<endl;
}