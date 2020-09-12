#include <bits/stdc++.h>
 
using namespace std;

#define endl '\n'

/*
P为给定的二维平面整数点集。定义 P 中某点x，如果x满足 P 中任意点都不在 x 的右上方区域内（横纵坐标都大于x），则称其为“最大的”。
求出所有“最大的”点的集合。（所有点的横坐标和纵坐标都不重复, 坐标轴范围在[0, 1e9) 内）
-----------------------------------------
分析：
- 先按照一个轴进行排序，然后从大到小遍历，维护另一个轴的最大值

*/

struct Point
{
    int x,y;
    Point() {}
};
 
int main() {
    freopen("算法与数据结构/niuke_toutiao/data.in", "r", stdin);
    int n;
    while (cin>>n) {
        vector<Point> arr(n);
        for (auto& p : arr) {
            cin>>p.x;
            cin>>p.y;
        }
        std::sort(arr.begin(), arr.end(), [](const Point& p1, const Point& p2){return p1.y>p2.y;} );
        int max_x = arr[0].x;
        cout<<arr[0].x<<" "<<arr[0].y<<endl;
        for (int i=1;i<arr.size();++i) {
            if (arr[i].x > max_x) {
                cout<<arr[i].x<<" "<<arr[i].y<<endl;
                max_x = arr[i].x;
            }
        }
    }
}
