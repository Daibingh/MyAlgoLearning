#include "utils.hpp"

using namespace std;


/*
给定 pushed 和 popped 两个序列，每个序列中的 值都不重复，只有当它们可能是在最初空栈上进行的推入 push 和弹出 pop 操作序列的结果时，返回 true；否则，返回 false 。
------------------------------------------
分析：
- 模拟进栈出栈过程；将 A 序列依次进栈，只要栈顶与 B 的 front 相等就出栈，同时 B 删除头。最后栈空说明符合
- 相似问题：火车进站问题
*/

class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> S;
        int j = 0;
        for (int i=0;i<pushed.size();++i) {
            S.push(pushed[i]);
            while (!S.empty() && S.top() == popped[j]) {
                S.pop();
                ++j;
            }
        }
        return S.empty();
    }


    // 回溯法求所有出栈序列，注意回溯之后要恢复现场（stk, seq 的状态）
    void allValidPopSeqHelper(vector<int>& a, int i, stack<int>& stk, vector<int>& seq, vector<vector<int>>& res) {
        // 遍历到底
        if (seq.size()==a.size()) {
            res.push_back(seq);
        }

        // 做选择 1: 继续入栈
        if (i<a.size()) {
            stk.push(a[i]);
            allValidPopSeqHelper(a, i+1, stk, seq, res);
            stk.pop();  // 恢复现场
        }

        // 做选择 2: 栈顶出栈
        if (!stk.empty()) {
            seq.push_back(stk.top());
            stk.pop();
            allValidPopSeqHelper(a, i, stk, seq, res);
            stk.push(seq.back());  // 恢复现场
            seq.pop_back();  // 恢复现场

        }
    }

    vector<vector<int>> allValidPopSeq(vector<int> a) {
        vector<vector<int>> res;
        vector<int> seq;
        stack<int> stk;
        allValidPopSeqHelper(a, 0, stk, seq, res);
        return res;
    }
};


int main() {

    auto res = Solution().allValidPopSeq({1,2,3});
    for (auto & t : res) print_vec(t);
}