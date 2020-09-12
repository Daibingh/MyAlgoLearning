#include <bits/stdc++.h>
using namespace std;


/*
地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。
一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），
也不能进入行坐标和列坐标的数位之和大于k的格子。例如，当k为18时，机器人能够进入方格 [35, 37] ，
因为3+5+3+7=18。但它不能进入方格 [35, 38]，因为3+5+3+8=19。请问该机器人能够到达多少个格子？
*/

class Solution {
	int m, n;
public:
    int movingCount(int m, int n, int k) {
        vector<vector<int>> vis(m, vector<int>(n, 0));
        int cnt = 0;
        this->m=m;
        this->n=n;
        return dfs(vis, 0,0,k);  // 从右上角开始遍历
    }

    int dfs(vector<vector<int>>& vis, int y, int x, int k) {
        if ( y<0 || y>=m || x<0|| x>=n || vis[y][x]) return 0;
        vis[y][x] = 1;
        if (!check(y, x, k)) return 0;
        return 1 + dfs(vis, y+1, x, k) + dfs(vis, y, x+1, k);
    }

    static bool check(int y, int x, int k) {
    	return helper(y)+helper(x) <= k;
    }

    static int helper(int x) {
    	int ret = 0;
    	while (x) {
    		ret += x % 10;
    		x /= 10;
    	}
    	return ret;
    }
};
