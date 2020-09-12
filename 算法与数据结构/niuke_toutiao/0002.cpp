#include <bits/stdc++.h>
 
/*
给定一个数组序列, 需要求选出一个区间, 使得该区间是所有区间中经过如下计算的值最大的一个：

区间中的最小数 * 区间所有数的和最后程序输出经过计算后的最大值即可，不需要输出具体的区间。如给定序列  [6 2 1]则根据上述公式, 可得到所有可以选定各个区间的计算值:

 

[6] = 6 * 6 = 36;

[2] = 2 * 2 = 4;

[1] = 1 * 1 = 1;

[6,2] = 2 * 8 = 16;

[2,1] = 1 * 3 = 3;

[6, 2, 1] = 1 * 9 = 9;

 

从上述计算可见选定区间 [6] ，计算值为 36， 则程序输出为 36。

区间内的所有数字都在[0, 100]的范围内;
----------------------------------------
分析：
- 利用单调栈(递增)

*/


using namespace std;

int main() {
    freopen("算法与数据结构/niuke_toutiao/data.in", "r", stdin);
    int n;
    cin>>n;
    vector<int> nums(n);
    vector<int> cusum(n);
    for(int i=0;i<n;i++)
        cin>>nums[i];
    cusum[0]=nums[0];
    for(int i=1;i<n;i++)
        cusum[i]=cusum[i-1]+nums[i];
    nums.push_back(0);
    stack<int> stk;
    int i=0;
    int ans=0;
    while(i<nums.size())
    {
        if(stk.empty()||nums[i]>=nums[stk.top()])
            stk.push(i++);
        else
        {
            int h=stk.top();
            stk.pop();
            int st=(stk.empty())?cusum[i-1]:(cusum[i-1]-cusum[stk.top()]);
            ans=max(ans,nums[h]*st);
        }
    }
    cout<<ans<<endl;
    return 0;
}