#include "utils.hpp"

using namespace std;


// 递归 dfs
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int res = 0;
        for (int i=0;i<m;++i) {
            for (int j=0;j<n;++j) {
                if (grid[i][j]) res = std::max(dfs(grid,i,j,1), res);
            }
        }
        return res;
    }
    
    int dfs(vector<vector<int>>& grid, int i, int j, int cnt) {
        grid[i][j] = 0;
        if (j<grid[0].size()-1 && grid[i][j+1]) cnt = dfs(grid,i,j+1,cnt+1);
        if (i<grid.size()-1 && grid[i+1][j]) cnt = dfs(grid,i+1,j,cnt+1);
        if (i>0 && grid[i-1][j]) cnt = dfs(grid,i-1,j,cnt+1);
        if (j>0 && grid[i][j-1]) cnt = dfs(grid,i,j-1,cnt+1);
        return cnt;
    }
};


// bfs 
class Solution2 {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        queue<pair<int, int>> que;
        int m = grid.size();
        int n = grid[0].size();
        int res = 0;
        for (int i=0;i<m;++i) {
            for (int j=0;j<n;++j) {
                if (!grid[i][j]) continue;
                int cnt = 0;
                que.push({i,j});  // 一开始先放进去一个
                grid[i][j] = 0;
                while (!que.empty()) {
                    int ii = que.front().first;
                    int jj = que.front().second;
                    ++cnt;                  // 出队列访问（计数）
                    que.pop();

                    // 访问改点的四周
                    if (ii<m-1 && grid[ii+1][jj]) {
                        que.push({ii+1,jj});
                        grid[ii+1][jj] = 0;
                    }
                    if (ii>0 && grid[ii-1][jj]) {
                        que.push({ii-1,jj});
                        grid[ii-1][jj] = 0;
                    }
                    if (jj<n-1 && grid[ii][jj+1]) {
                        que.push({ii,jj+1});
                        grid[ii][jj+1] = 0;
                    }
                    if (jj>0 && grid[ii][jj-1]) {
                        que.push({ii,jj-1});
                        grid[ii][jj-1] = 0;
                    }
                }
                
                res = std::max(res, cnt);
                
            }
            
        }
        return res;
        
    }
};