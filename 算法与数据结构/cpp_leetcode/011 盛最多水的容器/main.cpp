#include "../utils.hpp"

using namespace std;

/*
- 双指针法
*/

class Solution {
public:
    int maxArea(vector<int>& height) {
        auto l = height.begin();
        auto r = height.end()-1;
        int res = 0;
        while (l<r)
        {
            res = std::max(res, (int)(r-l)*std::min(*l,*r));
            if (*l<*r) ++l;  // 小的一侧就移动指针
            else --r;
        }
        return res;
    }
};

int main() {
    vector<int> v{1,8,6,2,5,4,8,3,7};
    cout<<Solution().maxArea(v)<<endl;;
}