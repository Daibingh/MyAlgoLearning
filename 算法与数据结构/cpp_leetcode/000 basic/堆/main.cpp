#include "utils.hpp"

using namespace std;

// 小顶堆
struct Heap
{
    vector<int> arr;

    explicit Heap(int n) {
        arr.resize(n+1);
        heapSize = 0;
    }

    explicit Heap(const vector<int> data) {
        arr.resize(data.size()+1);
        for (int i=0;i<data.size();++i) arr[i+1] = data[i];
        heapSize = data.size();
        buildHeap();
    }

    int size() const {
        return heapSize;
    }

    // 从 最后一个元素的父节点开始，自下而上，进行下滤
    void buildHeap() {
        for (int i = heapSize / 2; i>0; --i) {
            filterDown(i);
        }
    }

    // 下滤
    void filterDown(int idx) {
        int chd = 2*idx;
        int tmp = arr[idx];
        while (chd < heapSize+1) {
            if (chd < heapSize && arr[chd] > arr[chd+1]) ++chd;
            if (tmp > arr[chd]) {
                arr[idx] = arr[chd];
                idx = chd;
                chd = 2*idx;
            }
            else break;
        }
        arr[idx] = tmp;
    }

    int top() const {
        return arr[1];
    }

    void insert(int val) {
        assert (heapSize < arr.size());
        int parent = heapSize / 2;
        int cur = ++heapSize;
        while (parent > 0 && val < arr[parent])  // 上滤
        {
            arr[cur] = arr[parent];
            cur = parent;
            parent = cur / 2;
        }
        arr[cur] = val;
    }

    void pop() {
        assert (heapSize>0);
        arr[1] = arr[heapSize--];
        filterDown(1);
    }

    int heapSize;
};

int main() {
    vector<int> a{4,6,2,5,2,6,7,3};
    // Heap heap(a);
    Heap heap(100);
    for (auto & t: a) heap.insert(t);

    while (heap.size()) {
        cout<<heap.top()<<endl;
        heap.pop();
    }

    // print_vec(heap.arr);
}