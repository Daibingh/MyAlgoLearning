#include "../utils.hpp"

using namespace std;

/**
- 难点在于时间复杂度要求，要充分利用中位数的特点和两个数组的排好序的特点
- 想法是，将 nums1（较短序列）进行二分切割，并假定**其切割位置左侧序列构成总体序列的前半部分**，则另一部分可以由 nums2 前一部分组成，nums2 的切割位置可以推算出来，然后根据 lmax1, rmin1, lmax2, rmin2 的大小关系进行验证，若 $lmax1 < rmin2 \ \ and \ \ lmax2 < rmin1$ 则 $median = ( max(lmax1, lmax2) + min(rmin1, rmin2) ) \ \ / \ \ 2.0$, 否则，继续对 nums1 进行二分
- 在实现过程中，为了便于进行索引的计算，对数组进行“虚拟填充”
- O(log(m + n)), O(1)
*/

class Solution {
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int n = nums1.size();
		int m = nums2.size();

		if (n > m)  //保证数组1一定最短
		{
			return findMedianSortedArrays(nums2, nums1);
		}

		// Ci 为第i个数组的割,比如C1为2时表示第1个数组只有2个元素。LMaxi为第i个数组割后的左元素。RMini为第i个数组割后的右元素。
		int LMax1, LMax2, RMin1, RMin2, c1, c2, lo = 0, hi = 2 * n;  //我们目前是虚拟加了'#'所以数组1是2*n长度

		while (lo <= hi)   //二分
		{
			c1 = (lo + hi) / 2;  //c1是二分的结果
			c2 = m + n - c1;

			LMax1 = (c1 == 0) ? INT_MIN : nums1[(c1 - 1) / 2];
			RMin1 = (c1 == 2 * n) ? INT_MAX : nums1[c1 / 2];
			LMax2 = (c2 == 0) ? INT_MIN : nums2[(c2 - 1) / 2];
			RMin2 = (c2 == 2 * m) ? INT_MAX : nums2[c2 / 2];

			if (LMax1 > RMin2)
				hi = c1 - 1;
			else if (LMax2 > RMin1)
				lo = c1 + 1;
			else
				break;
		}
		return (max(LMax1, LMax2) + min(RMin1, RMin2)) / 2.0;
	}
};


// 另一种写法
class Solution2 {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        
        int n1 = nums1.size();
        int n2 = nums2.size();
        if (n1 > n2) return findMedianSortedArrays(nums2, nums1);
        
        // m1 : 左侧个数来自 nums1
        // m2 : 左侧个数来自 nums2
        int l = 0, r = n1-1;
        int k = (n1+n2+1)/2;
        while (l<=r) {
            int m1 = l + (r-l)/2;   // [0, m1-1] + [m1, ...]
            int m2 = k - m1;        // [0, m2-1] + [m2, ...]
            if (nums1[m1] < nums2[m2-1]) {  // 增加来自 nums1 的个数
                l = m1 + 1;
            }
            else {
                r = m1-1;
            }
        }
        int m1 = l, m2 = k - l;
        int c1 = max( m1<=0 ? INT_MIN : nums1[m1-1],
                      m2<=0 ? INT_MIN : nums2[m2-1] ); 
        if ((n1+n2)&1) return c1;
        int c2 =  min( m1>=n1 ? INT_MAX : nums1[m1],
                      m2>=n2 ? INT_MAX : nums2[m2] ); 
        return (c1+c2) / 2. ;
    }
};


int main(int argc, char *argv[])
{
	vector<int> nums1{ 2,3, 5 };
	vector<int> nums2{ 1,4,7, 9 };
	
	Solution solution;
	double ret = solution.findMedianSortedArrays(nums1, nums2);
    cout<<ret<<endl;
	return 0;
}
