#include "utils.hpp"

using namespace std;


class Solution {
public:
    
//    f(x) = x^2 - a;
//     f(x) = 0   
//     f'(x) = 2*x
    
    // 牛顿迭代公式
    // x1 = x - f(x)/f'(x)
         
    int mySqrt(int a) {
        double x = 1.;
        while (true) {
            double y = x*x - a;
            double x1 = x-y/(2*x);
            if (static_cast<int>(x1)==static_cast<int>(x)) return x;
            x = x1;
        }
    }
};