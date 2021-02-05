
// freopen("playground/data.in", "r", stdin);

#include <bits/stdc++.h>

using namespace std;

// inline bool isEven(int x) { return !(x&1); }

vector<int> solve(vector<int>& arr, vector<char>& P) {
    vector<int> res(P.size());
    for (int i=0;i<P.size();++i) {
        // cout<<i<<", "<<P[i]<<endl;
        if (P[i]=='M') {
            bool f = false;
            int fz = INT_MAX;
            for (int j=0;j<arr.size();++j) {
                // cout<<j<<", "<<arr[j]<<endl;
                if (arr[j]==0) {
                    fz = min(j, fz);
                }
                else if (arr[j]==1) {
                    res[i] = j;
                    ++arr[j];
                    f = true;
                    break;
                }
                
            }
            if (!f) {
                res[i] = fz;
                ++arr[fz];
            }
        }
        else {
            bool f = false;
            int fo = INT_MAX;
            for (int j=0;j<arr.size();++j) {
                if (arr[j]==1) {
                    fo = min(fo, j);
                }
                else if (arr[j]==0) {
                    res[i] = j;
                    ++arr[j];
                    f = true;
                    break;
                }
                
            }
            
            if (!f) {
                res[i] = fo;
                ++arr[fo];
            }
        }
    }
    return res;
}

int main() {
    // freopen("playground/data.in", "r", stdin);
    int T;
    cin>>T;
    while (T--) {
        int N;
        cin>>N;
        vector<int> arr(N);
        string str;
        cin>>str;
        for (int i=0;i<N;++i) {
            arr[i] = str[i]-'0';
        }
        int M;
        cin>>M;
        vector<char> P(M);
        for (auto & t : P) {
            cin>>t;
        }
        
        // for (auto & t : P) {
        //     cout<<t;
        // }

        auto res = solve(arr, P);
        for (const auto & t : res) {
            cout<<t+1<<endl;
        }
    }
    return 0;
}