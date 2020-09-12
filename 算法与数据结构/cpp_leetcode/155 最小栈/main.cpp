#include "utils.hpp"

using namespace std;

/*
设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。

push(x) —— 将元素 x 推入栈中。
pop() —— 删除栈顶的元素。
top() —— 获取栈顶元素。
getMin() —— 检索栈中的最小元素。

*/

// 利用辅助栈
// stk1: |2,1,3,4
// stk1: |2,1,1,1
class MinStack {

private:
    stack<int> stk1;  // 数据栈
    stack<int> stk2;  // 辅助栈
public:
    /** initialize your data structure here. */
    MinStack() {
        stk2.push(INT_MAX);  // 先放入一个大数，充当哨兵
    }
    
    void push(int x) {
        stk1.push(x);
        stk2.push(min(stk2.top(), x));  // 入栈时辅助栈保证栈顶是最小元, 个数要同步
    }
    
    void pop() {
        stk1.pop();  // 出栈时， 两个栈是同步的
        stk2.pop();
    }
    
    int top() {
        return stk1.top();
    }
    
    int getMin() {
        return stk2.top();
    }
};
