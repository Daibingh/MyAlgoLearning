#include <bits/stdc++.h>
#include "utils.hpp"

using namespace std;


// 回溯法超时
class Solution {
public:
    string res;
    string getPermutation(int n, int k) {
        bool * vis = new bool[n+1]();
        res = "";
        int cnt = 0;
        backtracking(n, k, vis, cnt);
        return res;
    }
    
    void backtracking(int n, int k, bool *vis, int& cnt, string str="" , int len=0) {
        if (len==n) {
            cnt++;
            // cout<<str<<", "<<cnt<<endl;
            if (cnt==k) res = str;  // 结果通过成员变量返回
            return;
        } 
        
        for(int i=1;i<=n;++i) {
            if (vis[i]) continue;  // vis 访问过的标记
            vis[i] = 1;
            backtracking(n, k, vis, cnt, str + (char)(i+'0'), len+1);
            if (cnt>=k) return;  // 回溯，立刻检查终止条件
            vis[i] = 0;
        }
    }
};

// 找规律
class Solution2 {
public:
    string getPermutation(int n, int k) {
        vector<int> M(n,1);  // 1,1,2,3,6 ( 0!~(n-1)! )
        vector<int> num(n, 1);  // 1,2,3,4
        for (int i=1;i<n;++i) {
            M[i] = M[i-1]*i;
            num[i] = i+1;
        }
                
        string res = "";
        --k;
        for (int i=0;i<n;++i) {
            int t = k / M[n-i-1];  // 第一个数的变化的周期是 (n-1)!, 即数 (n-1)! 个数才改变一次
            k = k % M[n-i-1];
            res += static_cast<char>(num[t]+'0');
            num.erase(num.begin()+t);  // 用完之后删除
        }
        
        return res;
    }
};

int main() {

}