#include <bits/stdc++.h>
#include "utils.hpp"

using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n, 0));
        int cnt = 1;
        int L=0, R=n-1, U=0, D=n-1;
        while (cnt<=n*n) {
            for (int i=L;i<=R;++i) {
                res[U][i] = cnt++;
            }
            ++U;
            for (int i=U;i<=D;++i) {
                res[i][R] = cnt++;
            }
            --R;
            for (int i=R;i>=L;--i) {
                res[D][i] = cnt++;
            }
            --D;
            for (int i=D;i>=U;--i) {
                res[i][L] = cnt++;
            }
            ++L;           
        }
        return res;
    }
};

int main() {

}