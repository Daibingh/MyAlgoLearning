#include "utils.hpp"

using namespace std;


/*

hash 冲突的处理方法：
- 链地址法，挂链表
- 开放定址法，探测

hash 函数：
- 除留余数法
- 直接定址
- 平方取中

*/

// 哈希表实现，开放地址，线性探测，有问题！！！ 删除处理，探索回绕
class HashTable {

    const int M = 1361;

    vector<pair<int,int>> bucket;
    int cnt;

public:
    void insert(int k, int v) {
        int idx = hash(k);
        while (bucket[idx].first!=-1 && bucket[idx].first!=k) ++idx;
        if (bucket[idx].first!=k) ++cnt;
        bucket[idx].first = k;
        bucket[idx].second = v;
    }

    int get(int k) {
        int idx = hash(k);
        while (bucket[idx].first!=k && bucket[idx].first!=-1) ++idx;
        return bucket[idx].second;
    }

    void del(int k) {
        int idx = hash(k);
        while (bucket[idx].first!=k && bucket[idx].first!=-1) ++idx;
        if (bucket[idx].first==k) --cnt;
        bucket[idx].first = -1;
    }

    void print() const {

    }

    int size() const {
        return cnt;
    }

    int hash(int k) {
        return k % M;
    }

    HashTable() {
        cnt = 0;
        bucket = vector<pair<int,int>>(M, make_pair(-1,-1));
    }
};

int main() {
    HashTable h;
    h.insert(1,3);
    h.insert(4,1);
    h.insert(2,5);
    h.insert(1,6);
    cout<<h.get(1)<<endl;
    cout<<h.get(2)<<endl;
    cout<<h.get(4)<<endl;
    cout<<h.get(0)<<endl;
    cout<<h.size()<<endl;
    h.del(1);
    h.del(1);
    h.insert(1,3);
    cout<<h.size()<<endl;
}