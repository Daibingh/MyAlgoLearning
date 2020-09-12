#include "utils.hpp"

using namespace std;

/*
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。

现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？
-------------------------------------------------------------
解法：
- 动态规划 
- 可以进行状态压缩, 因为 dp table 每个元素仅仅利用它的上侧和左侧的值，可将 dp table 压缩为一维
*/

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));  // 外面填充一圈障碍物
        for (int i=0;i<m;++i) {
            for (int j=0;j<n;++j) {
                if (obstacleGrid[i][j]) continue;  // base case
                if (i==0 && j==0) dp[1][1] = 1;   // base case
                else dp[i+1][j+1] = dp[i][j+1] + dp[i+1][j];     
            }
        }
        return dp.back().back();
    }
};


class Solution2 {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int n = obstacleGrid.size(), m = obstacleGrid.at(0).size();
        vector <int> f(m);

        f[0] = (obstacleGrid[0][0] == 0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (obstacleGrid[i][j] == 1) {
                    f[j] = 0;
                    continue;
                }
                if (j - 1 >= 0 && obstacleGrid[i][j - 1] == 0) {
                    f[j] += f[j - 1];
                }
            }
        }

        return f.back();
    }
};

int main() {

}