
#include "utils.hpp"
using namespace std;

/*
以 Unix 风格给出一个文件的绝对路径，你需要简化它。或者换句话说，将其转换为规范路径。

在 Unix 风格的文件系统中，一个点（.）表示当前目录本身；此外，两个点 （..） 表示将目录切换到上一级（指向父目录）；两者都可以是复杂相对路径的组成部分。更多信息请参阅：Linux / Unix中的绝对路径 vs 相对路径

请注意，返回的规范路径必须始终以斜杠 / 开头，并且两个目录名之间必须只有一个斜杠 /。最后一个目录名
-----------------------------------------------------------------------------------------
解法：
- 以 "/" 作为分隔符，将子串依次入栈
    - 如果 是 ".." 栈顶退栈
    - 如果是 "." 或 "" 忽略
    - 其它字符 入栈
- 最后 以 "/" 拼接起来
*/

class Solution {
public:
    string simplifyPath(string path) {
        vector<string> stk;
        int i=0,j=0;
        path += "/";
        while (i<path.size()) {
            j = path.find('/', i);  // string:: find(char, pos, len)
            string s = path.substr(i, j-i);
            if (s=="..") {
                if (!stk.empty()) stk.pop_back();  // ".." 栈顶弹出
            }
            else if (!s.empty() && s != ".")   // 对于非空子串和非 "." 子串，入栈
            {    
                stk.push_back(s);
            }
            i = j+1;
        }
        string res;
        for (const auto s : stk) res = res + "/" + s;
        if (res.empty()) return "/";
        return res;
    }
};

