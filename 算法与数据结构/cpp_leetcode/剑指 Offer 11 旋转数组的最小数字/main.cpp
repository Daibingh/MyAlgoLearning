#include <bits/stdc++.h>
using namespace std;

/*
把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。例如，数组 [3,4,5,1,2] 为 [1,2,3,4,5] 的一个旋转，该数组的最小值为1。  

示例 1：

输入：[3,4,5,1,2]
输出：1
*/


// 二分法，关键在于修改 L, R
class Solution {
public:
    int minArray(vector<int>& a) {
    	int L = 0, R = a.size()-1;
    	while (L<R) {
            // cout<<L<<", "<<R<<endl;
    		int mid = L + (R-L) /2;
    		if ( a[mid]<a[R] ) {
    			R = mid;    //  当 [mid]<[R]，mid 的位置    xxx|yyy  有可能在转折点上，或转折点右侧，为了避免左右指针在转折点一侧，此处不能是 R=mid-1
    		}                                          //     ^^
    		else if (a[mid]>a[R] ) {
    			L = mid +1;
    		} 
            else {
                --R;           // 这里也很关键，当 [mid]==[R]，不能决定取那边搜索，只能缩短右侧边界
            }
    	}
    	return a[L];
    }
};