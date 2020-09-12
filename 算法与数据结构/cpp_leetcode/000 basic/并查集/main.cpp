#include "utils.hpp"
using namespace std;

// 并查集解法，动态连通性
class UF {
    
public:
    vector<int> parent;
    vector<int> size;
    int cnt;
    
    
    UF(int n) {
        parent = vector<int>(n);
        size = vector<int>(n,1);
        cnt = n;
        for (int i=0;i<n;++i) parent[i] = i;  // 初始化 parent 为自己
    }
    
    // 查询 x 的根，同时作路径压缩
    int find(int x) {
        while (parent[x]!=x) {
            parent[x] = parent[ parent[x] ];  // 将 x 提升到它 爷爷 下面
            x = parent[x];
        }
        return x;
    }
    
    
    void union_(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx==ry) return;
        
        if (size[rx]<size[ry]) {
            parent[rx] = ry;  // 注意这里不是 直接吧 x 挂到 ry 上，而是 rx -> ry
            size[ry] += size[rx];
        }
        else {
            parent[ry] = rx;
            size[rx] += size[ry];
        }
        --cnt;  // 每次合并一个，联通分量个数减一
    }
    
};