
// freopen("playground/data.in", "r", stdin);

// #include <ctype.h>
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <math.h>
#include <bits/stdc++.h>

using namespace std;


int main() {
    
    vector<pair<int, int>> v({{1,1},{2,4}});
    unordered_map<int, int> m(v.begin(), v.end());

    for (const auto & t : m) {
        cout<<t.first<<", "<<t.second<<endl;
    }

    return 0;
}