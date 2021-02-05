#include <bits/stdc++.h>

using namespace std;

/*
给定一个化学式formula（作为字符串），返回每种原子的数量。

原子总是以一个大写字母开始，接着跟随0个或任意个小写字母，表示原子的名字。

如果数量大于 1，原子后会跟着数字表示原子的数量。如果数量等于 1 则不会跟数字。例如，H2O 和 H2O2 是可行的，但 H1O2 这个表达是不可行的。

两个化学式连在一起是新的化学式。例如 H2O2He3Mg4 也是化学式。

一个括号中的化学式和数字（可选择性添加）也是化学式。例如 (H2O2) 和 (H2O2)3 是化学式。

给定一个化学式，输出所有原子的数量。格式为：第一个（按字典序）原子的名子，跟着它的数量（如果数量大于 1），然后是第二个原子的名字（按字典序），跟着它的数量（如果数量大于 1），以此类推。
示例 1:

输入: 
formula = "H2O"
输出: "H2O"
解释: 
原子的数量是 {'H': 2, 'O': 1}。
示例 2:

输入: 
formula = "Mg(OH)2"
输出: "H2MgO2"
解释: 
原子的数量是 {'H': 2, 'Mg': 1, 'O': 2}。
示例 3:

输入: 
formula = "K4(ON(SO3)2)2"
输出: "K4N2O14S4"
解释: 
原子的数量是 {'K': 4, 'N': 2, 'O': 14, 'S': 4}。

*/

// 利用栈 和 hash表
class Solution {
public:
    string countOfAtoms(string formula) {
        map<string, int> atoCnt;
        int n = formula.size();
        int num_left = 0;
        vector<pair<string, int>> stk;
        for (int i=0;i<n;) {
            char c = formula[i];
            if (isupper(c) && stk.empty()) {  // 栈空：不在括号之内，扫描计数
                int st = i;
                ++i;
                while (i<n && islower(formula[i])) ++i;
                string atoName = formula.substr(st, i-st);
                if (i<n && isdigit(formula[i])) {
                    int st2 = i;
                    while (i<n && isdigit(formula[i])) ++i;
                    int num = atoi(formula.c_str()+st2);
                    atoCnt[atoName] += num;
                }
                else {
                    atoCnt[atoName] += 1;
                }
            }
            else if (c=='(') {  // 左括号入栈
                stk.push_back({"(", 0});
                ++i;
                ++num_left;
            }
            else if (c!=')') {  // 在括号范围内，计数保存在栈中
                int st = i;
                ++i;
                while (i<n && islower(formula[i])) ++i;
                string atoName = formula.substr(st, i-st);
                if (i<n && isdigit(formula[i])) {
                    int st2 = i;
                    while (i<n && isdigit(formula[i])) ++i;
                    int num = atoi(formula.c_str()+st2);
                    stk.push_back({atoName, num});
                }
                else {
                    stk.push_back({atoName, 1});
                }
            }
            else if (c==')') {  // 右括号开始结算栈中的计数
                ++i;
                int num = 1;
                if (i<n && isdigit(formula[i])) {
                    int st = i;
                    while (i<n && isdigit(formula[i])) ++i;
                    num = atoi(formula.c_str()+st);
                }

                if (num_left==1) {  // 碰到最后一个右括号，结算并出栈
                    while (stk.back().first!="(") {
                        atoCnt[stk.back().first] += num * stk.back().second;
                        stk.pop_back();
                    }
                    stk.pop_back();
                    --num_left;
                } 
                else {  // 如果是内存括号，只做更新计数，先不出栈
                    for (int j=stk.size()-1;j>=0;--j) {
                        if (stk[j].first=="(") {
                            stk.erase(stk.begin()+j);
                            --num_left;
                            break;
                        }
                        stk[j].second *= num;
                    }
                }
            }
        }
        string res;
        for (auto & m : atoCnt) {
            res += m.first;
            if (m.second>1) res += to_string(m.second);
        }
        return res;
    }
};
