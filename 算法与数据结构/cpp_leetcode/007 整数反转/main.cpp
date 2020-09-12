#include "../utils.hpp"

using namespace std;

/*
- 考察整数位数分离和组合
- 关键在于溢出的预判
- O(n), o(1)
*/

class Solution {
public:
    int reverse(int x) {
        int res = 0;
        while (x!=0) {
            int m = x%10;  // 从右往左取位数
            if (res>INT_MAX/10 || ( res==INT_MAX/10 && m > 7 )) return 0;
            if (res<INT_MIN/10 || ( res==INT_MAX/10 && m < -8 )) return 0;
            res = res * 10 + m;  // 123 = ((0*10+1)*10+2)*10+3， 这里有可能导致溢出
            x/=10;
        }
        return res;
    }
};


int main() {
    int n = -1234;
    auto res = Solution().reverse(n);
    cout<<res<<endl;
}