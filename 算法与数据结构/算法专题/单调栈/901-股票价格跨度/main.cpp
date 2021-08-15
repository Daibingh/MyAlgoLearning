#include <bits/stdc++.h>

using namespace std;


class StockSpanner {
    stack<pair<int, int>> stk;  //｛index, value｝
    int cnt;
public:
    StockSpanner() {
        cnt  = 0;
    }
    
    int next(int price) {
        while (!stk.empty() && price >= stk.top().second) {
            stk.pop();
        }
        int res = cnt - (stk.empty() ? -1 : stk.top().first);
        stk.push({cnt++, price});
        return res;
    }
};


/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */