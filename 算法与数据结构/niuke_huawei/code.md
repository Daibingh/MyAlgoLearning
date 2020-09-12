## 001 最小公倍数

```c
#include <bits/stdc++.h>

using namespace std;

// 求最大公约数
int help(int a, int b) {
    if (a<b) return help(b, a);
    int tmp = a%b;
    if (tmp==0) return b;
    else return help(b, tmp);
}

int solve(int a, int b) {
    int tmp = help(a,b);
    return a*b/tmp;
}


int main() {
    int a,b;
    while(scanf("%d %d",&a, &b) != EOF)
        printf("%d",solve(a, b));
    return 0;

}
```

分析：

- 利用辗转相除法求最大公约数，以及 `最小公倍数=两数之积除以最大公约数` 
- **反复用除数除以余数，最后整除的除数就是最大公约数**
- 递归实现

## 002 求立方根

```c
#include <bits/stdc++.h>

using namespace std;

const double eps = 0.01;

// 二分法求解
double fun(double l, double r, double x) {
    double mid = (l+r)/2.;
    if (fabs(mid-r)<eps) return mid;
    if (mid*mid*mid>x) return fun(l, mid, x);
    else return fun(mid, r, x);
}

double solve(double x) {
    if (x>0) return fun(0, x, x);
    else return fun(x, 0, x);
}

int main() {
    double x;
    while ( scanf("%lf", &x) != EOF ) {
        printf("%.1lf\n", solve(x));
    }
    
}
```

分析：

- 求方程的根常用两种方法：二分法，牛顿法
- 牛顿迭代公式：对于 `f(x)=0` , `x` 迭代公式为 $x=x-\frac{f(x)}{f'(x)}$ 

## 003 字符串倒序输出

```c
#include <bits/stdc++.h>

using namespace std;

int main() {
    string str;
    while(getline(cin, str)) {
        for (auto it=str.rbegin();it!=str.rend();++it)
            cout<<*it;
        cout<<'\n';
    }
}
```

注：

- 也可用 `std::reverse(myvector.begin(),myvector.end());`
- 获取一行字符串用 `getline` 方便

## 004 字符分组

```c
#include <bits/stdc++.h>

using namespace std;

void fun(string str) {
    while (str.size()>8)
    {
        cout<<str.substr(0, 8)<<endl;
        str = str.substr(8);
    }
    int res_count = 8-str.size();
    for (int i=0;i<str.size();++i) cout<<str[i];
    for (int i=0;i<res_count;++i) cout<<'0';
    cout<<endl;
}

int main() {
    string str;
    int count = 0;
    while (cin>>count) {
        cin.get(); // 跳到下一行否则, getline 返回空
        while ( count-->0 ) {
            getline(cin, str);
            fun(str);
        }
    }
}
```

注：

- cin 以空白为分隔符
- scanf, %d==>int, %ld==>long, %f==>float, %lf==>double
- getline() 获取一行字符串
- string.substr(pos, len)  截取字符串

## 005 最长递增子序列长度

```c
#include <bits/stdc++.h>

using namespace std;

int main() {
    int num;
    int h;
    while(cin>>num) {
        int res = 0;  // 对于每个 case 都要置零
        vector<int> dp(num, 1);
        vector<int> arr(num, 0);
        for (int i=0;i<num;++i) {
            cin>>h;
            arr[i] = h;
            for (int j=0;j<i;++j) {
                if (h>arr[j]) {
                    dp[i] = std::max(dp[i], dp[j]+1);  // 更新 dp[i]
                }
            }
            res = std::max(res, dp[i]);  // 更新最长的值
        }
        cout<<res<<endl;
    }
}
```

分析：

- 动态规划 dp[i] 表示以 i 为结尾的最长递增子序列的长度，每次读入数据 arr[i]，都要更新 dp[i]
- 程序中容易出错的地方：
  - 循环变量忘记自增
  - 变量忘记初始化，或重置零

## 006 字符统计并排序

```c
#include <bits/stdc++.h>

using namespace std;

bool comp(const pair<char, int> p1, const pair<char, int> p2)
{
    return p1.second>p2.second;
}

int main()
{
    string str;
    while (getline(cin, str))
    {
        vector<pair<char, int>> count(255);  // 构造计数桶, 本身安装 ASCII 有序
        for (auto it=str.begin();it!=str.end();++it)
        {
            count[*it].first = *it;
            ++count[*it].second;
        }
        std::stable_sort(count.begin(), count.end(), comp);  // 稳定排序，基于统计个数排序
        for (auto it=count.begin(); it!=count.end();++it)
        {
            if (it->second==0) break;
            cout<<it->first;
        }
        cout<<endl;
    }
}
```

分析：

- 计数桶也可以用 `std::map` , 定义 `map<char, int> m` 统计完后，`vector<char, int> vec(m.begin(), m.end())`

## 007 数组排序

```c
#include <bits/stdc++.h>

using namespace std;


int main()
{
    int num;
    while (cin>>num)
    {
        vector<int> arr(num);
        for (auto& a:arr)
        {
            cin>>a;
        }
        int flag;
        cin>>flag;
        if (!flag)
        {
            std::sort(arr.begin(), arr.end());
        }
        else
        {
            std::sort(arr.rbegin(), arr.rend());
        }
        for (auto& a:arr) {
            cout<<a<<" ";
        }
        cout<<endl;
    }
}
```

## 008 自守数

```c
#include <bits/stdc++.h> 

using namespace std;

bool isAns(int val) {
    string str1 = to_string(val);
    string str2 = to_string(val*val);
    str2 = str2.substr(str2.size()-str1.size());
    return str2==str1;
    
}

int main() {
    int n;
    while (cin>>n) {
        if (n<1) cout<<1<<endl;
        else if (n<5) cout<<2<<endl;
        else if (n<6) cout<<3<<endl;
        
        int cnt = 0;
        int val= 6;
        while (val<n) {
            if (isAns(val)) ++cnt;
            if (isAns(val-1)) ++cnt;
            if (isAns(val-5)) ++cnt;
            if (isAns(val-6)) ++cnt;
            val += 10;
        }
        cout<<cnt<<endl;
    }
    return 0;
}
```

分析：

- 比较尾数使用字符串比较
- 虽然 AC 但是应该有问题

## 009 自动售货机

```c
#include <bits/stdc++.h>

using namespace std;

int mon[4] = {1,2,5,10};
int mon_num[4] = {0};
string goods_name[6] = {"A1", "A2", "A3", "A4", "A5", "A6"};
int goods_price[6] = {2,3,4,5,8,6};
int goods_num[6] = {0};
int pay_mon = 0;

int init(string cmd) {
    cmd = cmd.substr(0, cmd.find(';'));
    stringstream ss(cmd);
    ss>>goods_num[0];
    ss.ignore(1, '-');
    ss>>goods_num[1];
    ss.ignore(1, '-');
    ss>>goods_num[2];
    ss.ignore(1, '-');
    ss>>goods_num[3];
    ss.ignore(1, '-');
    ss>>goods_num[4];
    ss.ignore(1, '-');
    ss>>goods_num[5];
    
    ss>>mon_num[0];
    ss.ignore(1, '-');
    ss>>mon_num[1];
    ss.ignore(1, '-');
    ss>>mon_num[2];
    ss.ignore(1, '-');
    ss>>mon_num[3];
    
    cout<<"S001:Initialization is successful"<<endl;
    
    return 0;
}

int sum_goods() {
    int sum = 0;
    for (int i=0;i<6;++i) {
        sum += goods_num[i];
    }
    return sum;
}

int payCoin(string cmd) {
    cmd = cmd.substr(0, cmd.find(';'));
    stringstream ss(cmd);
    int coin;
    ss>>coin;
    
    // cerr<<"--------"<<coin<<endl;
    
    if (coin!=1 && coin!=2 && coin!=5 && coin!=10) {
        cout<<"E002:Denomination error"<<endl;
    } else if (mon_num[0]+2*mon_num[1]<coin && coin!=1 && coin!=2) {
        cout<<"E003:Change is not enough, pay fail"<<endl;
    } else if (coin>10) {
        cout<<"E004:Pay the balance is beyond the scope biggest"<<endl;
    } else if (sum_goods()==0) {
        cout<<"“E005:All the goods sold out"<<endl;
    } else {
        pay_mon += coin;
        if (coin==1) mon_num[0]++;
        else if (coin==2) mon_num[1]++;
        else if (coin==5) mon_num[2]++;
        else if(coin==10) mon_num[3]++;
        cout<<"S002:Pay success,balance="<<pay_mon<<endl;
        return 0;
    }
    return -1;
}

int buyGoods(string cmd) {
    string buy_name = cmd.substr(0, cmd.find(';'));
    int buy_label = buy_name[1]-'0';
    if (buy_name!=goods_name[0] && buy_name!=goods_name[1] && buy_name!=goods_name[2] && buy_name!=goods_name[3] && buy_name!=goods_name[4] && buy_name!=goods_name[5]) {
        cout<<"E006:Goods does not exist"<<endl;
        return -1;
    } else if (goods_num[buy_label-1]==0) {
        cout <<"E007:The goods sold out"<<endl;
        return -1;
    } else if (pay_mon<goods_price[buy_label-1]) {
        cout<<"E008:Lack of balance"<<endl;
        return -1;
    } else {
       pay_mon-=goods_price[buy_label-1];
       cout<<"S003:Buy success,balance="<<pay_mon<<endl;
        
        return 0;
    }
}

int returnCoin() {
    if (pay_mon==0) {
        cout<<"E009:Work failure";
        return -1;
    }
    int ret_count[] = {0,0,0,0};
    for (int i=3;i>=0;) {
        if (pay_mon>=mon[i] && mon_num[i]>0) {   // 找零
            ++ret_count[i];
            pay_mon-=mon[i];
            --mon_num[i];
        } else --i;
    }
    
    for (int i=0;i<4;++i) {
        printf("%d yuan coin number=%d\n", mon[i], ret_count[i]);
    }
}

int query(string cmd) {
    int n = cmd[0]-'0';
    if (n==0) {
        for (int i=0;i<6;++i) {
            printf("%s %d %d\n", goods_name[i].c_str(), goods_price[i], goods_num[i]);
        }
    } else if (n==1) {
        for (int i=0;i<4;++i) {
            printf("%d yuan coin number=%d\n", mon[i], mon_num[i]);
        }
    } else {
        cout<<"E010:Parameter error";
        return -1;
    }
    return 0;
}

int main() {

    freopen("playground/data.in", "r", stdin);

    string cmd;
    while (getline(cin, cmd)) {
        for (int i=0;i<cmd.size();++i) {
            if (cmd[i]=='r') init(cmd.substr(i+2));
            else if (cmd[i]=='p') payCoin(cmd.substr(i+2));
            else if (cmd[i]=='b') buyGoods(cmd.substr(i+2));
            else if (cmd[i]=='c') returnCoin();
            else if (cmd[i]=='q') query(cmd.substr(i+2));
        }
    }
}
```

注：

- 关注找零的实现，贪心思想，和转罗马数字类似
- string 转 整数，可以 借助 stringstream ss(str); ss>>num; 或者 使用 int atoi (const char * str);, double atof (const char* str);
- steam.ignore(n, char) 忽略知道 char 的字符（包含char）
- 尽量使用 vector, 可以直接使用相关算法

## 010 表示数字

```c
#include <bits/stdc++.h>

using namespace std;

bool isNum(char c) {
    return c>='0' && c<='9';
}

int main() {
    string str;
    while (getline(cin, str)) {
        string res;
        bool f = false;   // 使用标志位，标记当前是否进入数字区域
        for (auto c: str) {
            if (!f && isNum(c)) {
                res += "*";
                res += c;
                f = true;
            } else if (f&&!isNum(c)) {
                res += "*";
                res += c;
                f = false;
            } else res += c;
        }
        if (isNum(str.back())) res += "*";  // 最后一个数字单独处理
        cout<<res<<endl;
    }
}
```

补充：

- 字符串处理操作

## 011 人民币转换

```c
#include <bits/stdc++.h>

using namespace std;

string S[] = {"元", "拾" ,"佰", "仟", "万", "拾", "佰", "仟"};  // 映射单位
string N[] = {"零", "壹", "贰", "叁", "肆", "伍", "陆", "柒", "捌", "玖"};  // 映射数字
string M[] = {"角", "分"}; // 映射单位

int main() {
    string str;
    while (getline(cin, str)) {
        string res1, res2;  // 整数部分，小数部分
        int pos = str.find('.');
        if (pos==-1) pos = str.size();
        bool z = false;  // 标记是否进入 “连续零区域”
        
        // 先求解整数部分，从小数点往两侧遍历
        for (int i=pos-1;i>=0;--i) {
            if (str[i]=='0' && !z) {  // 如果遇到零并且前一个不是零
                res1 = "零" + res1;
                z = true;  // 标记已经遇到零
            } 
            else if (str[i]!='0' && z) {  // 如果遇到非零，上一次遇到零，则解除零状态
                z = false;
            }
            if (z) continue;  // 如果当前位于连续零区域，不需要拼接 单位
            res1 = S[pos-1-i] + res1;  // 拼接单位
            if (S[pos-1-i]!="拾" || i!=0)  // 考虑特殊情况，15, 15xxxx, 不需要拼接 "壹" 
                res1 = N[str[i]-'0'] + res1;  // 拼接数字
        }
        // 求解小数部分
        for (int i=pos+1;i<str.size();++i) {
            if (str[i]!='0') {
                res2 = res2 + N[str[i]-'0'];
                res2 = res2 + M[i-pos-1];
            }
            
        }
        if (res1=="零") res1 = "";  // 特殊情况 0.15 
        if (res2.empty()) res2 = "整"; // 特殊情况 15.00
        res1 = "人民币"+res1+res2;
        cout<<res1<<endl;
    }
}
```

分析：

- 有点复杂，特殊情况较多

## 012 计票

```c
#include <bits/stdc++.h>

using namespace std;

int main() {
    int num;
    while (cin>>num) {
        vector<string> names(num);  // 使用 vector 记录顺序
        unordered_set<string> name_set;  // 使用 unordered_set 用于后面查询
        for (int i=0;i<num;++i) {
            cin>>names[i];
            name_set.insert(names[i]);  // set 插入是 insert
        }
        int num2;
        cin>>num2;
        int invalid_count = 0;
        unordered_map<string, int> count;
        for (int i=0;i<num2;++i) {
            string str;
            cin>>str;
            ++count[str];
            if (name_set.find(str)==name_set.end()) invalid_count++;
        }
        for (int i=0;i<num;++i) {
            printf("%s : %d\n", names[i].c_str(), count[names[i]]);
        }
        cout<<"Invalid : "<<invalid_count<<endl;
    }
}
```

## 013 数组两组之和相等

```c
#include <bits/stdc++.h>

using namespace std;

bool helper(int sum3, int sum5, vector<int> vec) {
    if (vec.empty() && sum3==sum5) return true;
    else if (vec.empty()) return false;
    else {
        int val = vec.back();
        vec.pop_back();
        return helper(sum3+val, sum5, vec) || helper(sum3, sum5+val, vec);  // 暴力递归搜索，枚举所有可能
    }
}

int main() {
    int num;
    while (cin>>num) {
        int sum5=0, sum3=0;
        vector<int> vec;
        for (int i=0;i<num;++i) {
            int val;
            cin>>val;
            if (val%5==0) sum5+=val;
            else if (val%3==0) sum3+=val;
            else vec.push_back(val);
        }
        if (helper(sum3, sum5, vec)) cout<<"true"<<endl;
        else cout<<"false"<<endl;
    }
}
```

分析：

- 先将5的倍数分为一组，3的倍数在另一组，其余元素为待分配的元素
- 采用暴力递归分配方式

## 014 在字符串中找出连续最长的数字串

```c
#include <bits/stdc++.h>

using namespace std;


int main() {
    string str;
    while (getline(cin, str)) {
        int max_len = 0;
        vector<int> pos;  // 存起点
        int p = 0;  // 慢指针
        int l = 0;  // 快指针
        while (p<str.size()) {
            while (!isdigit(str[p]) && p<str.size()) ++p;  // 慢指针定位到子串起点
            l = p;
            while (isdigit(str[l]) && l<str.size()) ++l;  // 快指针定位到子串终点
            if (l-p>max_len) {
                max_len = l-p;
                pos.clear();
                pos.push_back(p);
            } else if (l-p==max_len) {
                pos.push_back(p);
            } 
            p = l;  // 更新慢指针
        }
        for (auto& t: pos) {
            cout<<str.substr(t, max_len);
        }
        cout<<","<<max_len<<endl;
    }
}
```

分析：

- 快慢指针法
- 用 vector 存子串起点

## 015 棋盘格子路径

```c
#include <bits/stdc++.h>

using namespace std;

int fun(int m, int n) {
    if (m==0 || n==0) return 1;  // 一旦遇到边界，只有一条路
    return fun(m-1, n) + fun(m, n-1);
}

int main() {
    int n, m;
    while (cin>>n) {
        cin>>m;
        cout<<fun(m ,n)<<endl;
    }
}

/////////////////////////////动态规划//////////////////////////////
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    while (cin>>n) {
        cin>>m;
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for (int i=0;i<=m;++i) {
            for (int j=0;j<=n;++j) {
                if (i==0 || j==0) {
                    dp[i][j] = 1;  // 边界值
                    continue;
                }
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        cout<<dp[m][n]<<endl;
    }
}
```

分析：

- 抽象为 (m,n) -> (0,0)
- 递归求解或动态规划

## 016 IP 地址合法性

```c
#include <bits/stdc++.h>

using namespace std;

bool isValid(string str) {
    for (auto& c: str) {
        if (!isdigit(c)) return false;
    }
    int num = atoi(str.c_str());
    if (num>=0 && num <=255) return true;
    return false;
}

int main() {
    string str;
    while (getline(cin, str)) {
        vector<int> pos;
        int i =0;
        for (auto& c: str) {
            if (c=='.') {
                pos.push_back(i);
            }
            i++;
        }
        if (pos.size()!=3) {
            cout<<"NO"<<endl; continue;
        }
        if (!isValid(str.substr(0, pos[0]))) {
             cout<<"NO"<<endl; continue;
        }
        if (!isValid(str.substr(pos[0]+1, pos[1]-pos[0]-1))) {
             cout<<"NO"<<endl; continue;
        }
        if (!isValid(str.substr(pos[1]+1, pos[2]-pos[1]-1))) {
             cout<<"NO"<<endl; continue;
        }
        if (!isValid(str.substr(pos[2]+1))) {
             cout<<"NO"<<endl; continue;
        }
        cout<<"YES"<<endl;
    }
}
```

## 017 24 点

```c
#include <bits/stdc++.h>

using namespace std;

vector<string> op = {"+","-","*","/"};
unordered_map<string, int> M = {{"A",1},
                               {"2",2},
                               {"3",3},
                               {"4",4},
                               {"5",5},
                               {"6",6},
                               {"7",7},
                               {"8",8},
                               {"9",9},
                               {"10",10},
                               {"J",11},
                               {"Q",12},
                               {"K",13} };


bool check(vector<string> path) {
    int res = M[path[0]];
    for (auto i: vector<int>{1,3,5}) {
        if (path[i]=="+") res += M[path[i+1]];
        if (path[i]=="-") res -= M[path[i+1]];
        if (path[i]=="*") res *= M[path[i+1]];
        if (path[i]=="/") res /= M[path[i+1]];
    }
    return res == 24;
}


void solve(vector<string> names) {
     vector<int> flag(4, 0);
     vector<string> path;
     for (int i=0;i<4;++i) {
         flag[i] = 1;
         path.push_back(names[i]);
         for (int i2=0;i2<4;++i2) {
             path.push_back(op[i2]);
             for (int i3=0;i3<4;i3++) {
                 if (flag[i3]) continue;
                 flag[i3] = 1;
                 path.push_back(names[i3]);
                 for (int i4=0;i4<4;++i4) {
                     path.push_back(op[i4]);
                     for (int i5=0;i5<4;i5++) {
                         if (flag[i5]) continue;
                         flag[i5] = 1;
                         path.push_back(names[i5]);
                         for (int i6=0;i6<4;++i6) {
                             path.push_back(op[i6]);
                             for (int i7=0;i7<4;i7++) {
                                 if (flag[i7]) continue;
                                 path.push_back(names[i7]);
                                 if (check(path)) {
                                     for (auto& c:path) cout<<c;
                                     cout<<endl;
                                     return;
                                 }
                                 path.pop_back();
                             }
                             path.pop_back();
                         }
                         flag[i5] = 0;
                         path.pop_back();
                     }
                     path.pop_back();
                 }
                 flag[i3]= 0;
                 path.pop_back();
             }
             path.pop_back();
         }
         flag[i] = 0;
         path.pop_back();
     }
    
    cout<<"NONE"<<endl;
}


int main() {
    string str;
    while (getline(cin, str)) {
        vector<string> names(4);
        stringstream ss(str);
        bool f = false;
        for (int i=0;i<4;++i) {
            string tmp;
            ss>>tmp;
            if (tmp=="joker" || tmp=="JOKER") {
                cout<<"ERROR"<<endl;
                f=true;
                break;
            }
            names[i] = tmp;
        }
        if (f) continue;
        solve(names);
    }
}
```

分析：

- 暴力循环排序枚举，7 层 for，递归不是很好些
- 时间紧迫，怎么好些怎么来
- 代码有问题！注意数据类型应该用 double

## 018 扑克牌大小

```c
#include <bits/stdtr1c++.h>

using namespace std;

string S = "345678910JQKA2jokerJOKER";  // 记录牌大小顺序，通过 find 返回值比较牌面大小

int main() {
    string str;
    while (getline(cin, str)) {
        int pos = str.find('-');
        string str1 = str.substr(0, pos);
        string str2 = str.substr(pos+1);
        int c1 = std::count(str1.begin(), str1.end(), ' ')+1;  // 牌数
        int c2 = std::count(str2.begin(), str2.end(), ' ')+1;
        if (str1=="joker JOKER" || str2=="joker JOKER") cout<<"joker JOKER"<<endl;
        else if (c1==4 && c2!=4) {
            cout<<str1<<endl;
        } else if (c2==4 && c1!=4) {
            cout<<str2<<endl;
        } else if (c1!=c2) {
            cout<<"ERROR"<<endl;
        } else {
            str1 += " ";
            str2 += " ";
            string p1 = str1.substr(0, str1.find(' '));
            string p2 = str2.substr(0, str2.find(' '));
            int d1 = S.find(p1);
            int d2 = S.find(p2);
            if (d1>d2) cout<<str1<<endl;
            else cout<<str2<<endl;
        }
    }
}
```

分析：

- 比较思路

  - 出现双王，输出双王
  - 出现一个王炸，输出王炸
  - 牌数不等 ERROR
  - 比较第一个牌大小

- `std::count` 统计字符数

- 分割字符串实现 split 

  ```c
  string str = "123 456 78";
  
  str += " ";  // 末尾要加一个分隔符
  int pos =  str.find(" ");
  vector<string> vec;
  while (pos!=-1) {
      string tmp = str.substr(0, pos);
      vec.push_back(tmp);
      str = str.substr(pos+1);
      pos =  str.find(" ");
  }
  ```

  ## 019 二进制连续 1 的个数

```c
#include <bits/stdc++.h>

using namespace std;

int main() {
    uint32_t n;
    while (cin>>n) {
        uint32_t T = 1;  // 尺子
        int s=0, p=0;
        int max_n = 0;
        while (T) {
            while ((T&n) == 0 && T) {++s; T = T<<1;}  // (T&n) == 0 一定加括号！！！
            p = s;
            while ((T&n) != 0 && T) { ++p; T = T<<1;}
            if (p-s > max_n) max_n = p-s;
            s = p;
        }
        cout<<max_n<<endl;
    }
}
```

分析：

- 采用快慢指针法
- 注意位运算的优先级

## 019 最长回文子串

```c
#include <bits/stdc++.h> 

using namespace std;


int main() {
    string str;
    while (getline(cin, str)) {
        int n = str.size();
        if (n==0) continue;
        vector<vector<int>> dp(n, vector<int>(n, 0));
        int max_len = 1;
        for (int i=0;i<n;++i) {
            for (int j=0;j<=i;++j) {
                if (i==j) dp[j][i] = 1;  // 单个字符 a
                else if ((i-j)==1) {  // 两个字符 aa, ab
                    dp[j][i] = (str[i]==str[j]);
                } else {
                    dp[j][i] = (str[i]==str[j]) && dp[j+1][i-1];
                }
                if (dp[j][i] && (i-j+1) > max_len) {
                    max_len = (i-j+1);
                }
            }
        }
        cout<<max_len<<endl;
    }
}
```

分析:

- 一定要注意 (i, j) 搜索的顺序，j 趋近于 i, i 趋近于 n

## 020 埃及分数

```c
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n,m;
    while (scanf("%d/%d", &n,&m)!=EOF) {   // scanf 一定是 判断 EOF, 不要和 cin 混了
        vector<int> res;
        int x = m/n;
        while ((m%n) != 0) {
            x++;
            res.push_back(x);
            n = n*x-m;
            m = m*x;
            x = m/n;
        }
        res.push_back(x);
        for (int i=0;i<res.size()-1;++i) {
            cout<<1<<"/"<<res[i]<<"+";
        }
        cout<<1<<"/"<<res.back()<<endl;
    }
}
```

分析：

- 基于贪心思想

## 021 字符串匹配

```c
#include <bits/stdc++.h>

using namespace std;

int main() {
    string str1, str2;
    while (cin>>str1>>str2) {
        unordered_map<char, int> C;
        for (auto& c: str1) C[c]=0;
        for (auto& c: str2) {
            if (C.find(c)!=C.end()) {
                C[c] = 1;
            }
        }
        bool f=0;
        for (auto& m: C) {
            if (m.second) continue;
            cout<<"false"<<endl;
            f=1;
            break;
        }
        if (!f) cout<<"true"<<endl;
    }
}
```

分析：

- 采用 map 计数
- 也可以分桶计数

## 022 数组合并

```c
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n1 ,n2;
    while (cin>>n1) {
        vector<int> vec;
        for (int i=0;i<n1;++i) {
            int tmp;
            cin>>tmp;
            vec.push_back(tmp);
        }
        cin>>n2;
        for (int i=0;i<n2;++i) {
            int tmp;
            cin>>tmp;
            vec.push_back(tmp);
        }
        std::sort(vec.begin(), vec.end());
        vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
        for (auto& t: vec) {
            cout<<t;
        }
        cout<<endl;
    }
}
```

分析：

- 掌握 `std::unique` 和 `std::erase` 

## 023 求编辑距离

```c
#include <bits/stdc++.h>

using namespace std;

int findMin(int a, int b, int c) {
    return std::min(a, std::min(b,c) );
}

int main() {
    string s1,s2;
    while (getline(cin, s1)) {
        getline(cin, s2);
        s1.insert(0, 1, ' ');  // 前面插入空格，便于初始化
        s2.insert(0, 1, ' ');
        
        vector<vector<int>> dp(s1.size(), vector<int>(s2.size(), 0));
        
        for (int i=0;i<s2.size();++i) {  // 初始（边界）条件
            dp[0][i] = i;
        }
        
        for (int i=0;i<s1.size();++i) {   // 初始（边界）条件
            dp[i][0] = i;
        }
        
        for (int i=1;i<s1.size();++i) {
            for (int j=1;j<s2.size();++j) {
                if (s1[i]==s2[j])  {  // s1[i]==s2[j], dp[i][j] = dp[i-1][j-1]
                    dp[i][j] = dp[i-1][j-1];
                } else {  // s1[i]!=s2[j], 分三种情况: 1) 删除[i]; 2) 删除[j]; 3) 交换[i][j], 取这三种情况最小值
                    dp[i][j] = findMin(dp[i][j-1], dp[i-1][j], dp[i-1][j-1]) + 1;  
                }
            }
        }
        cout<<dp.back().back()<<endl;
    }
}
```

- `str.insert(pos, str)` , `str.insert(pos,  n, char)`

- 解法：动态规划

  <center><img src="https://raw.githubusercontent.com/Daibingh/MyTempFile/master/59ee0531f77249dfb651bc725223c103.png" width="600px"></center>

## 024 字符串求和

```c
#include <bits/stdc++.h>

using namespace std;

void fun(string s1, string s2) {
    if (s1.size()<s2.size()) {
        fun(s2, s1);
        return;
    }
    
    s2 = string(s1.size()-s2.size(), '0') + s2;  // 补齐
    string res;
    int carr = 0;
    for (int i=s1.size()-1;i>=0;--i) {
        int n1 = s1[i]-'0';
        int n2 = s2[i]-'0';
        int sum = n1 + n2 + carr;
        carr = sum/10;
        res = to_string(sum%10) + res;
    }
    if (carr!=0) res = '1' + res;
    cout<<res<<endl;
}

int main() {
    string s1, s2;
    while (cin>>s1>>s2) {
        fun(s1, s2);
    }
}
```

## 025 火车进站出站问题

```c
#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <algorithm>
 
using namespace std;

vector<vector<int>> resCon;

bool comp(const vector<int>& v1, const vector<int> v2) {
    for (int i=0;i<v1.size();++i) {
        if (v1[i]==v2[i]) continue;
        return v1[i]<v2[i];
    }
    return true;
}

 
void dispatch(queue<int> input,stack<int> current,vector<int> output)
{
	//判断输入队列中是否还有火车
	bool hasInput=true;
 
	//判断火车站里是否还有火车
	bool hasCurrent=true;
 
	if(input.size()==0)
		hasInput=false;
 
	if(current.size()==0)
		hasCurrent=false;
 
	//如果没有输入并且当前火车站中也有没火车
	if(!hasInput&&!hasCurrent)
	{
 
		//存储结果
        resCon.push_back(output);
		return ;	
	}
 
	//火车站中有火车要出栈
	if(hasCurrent)
	{
		stack<int> currentTmp=current;
		vector<int> outputTmp=output;
		outputTmp.push_back(currentTmp.top());
		currentTmp.pop();
		dispatch(input,currentTmp,outputTmp);
 
	}
 
	//火车站中有火车要入栈
	if(hasInput)
	{
		queue<int> inputTmp=input;
		stack<int> currentTmp=current;
		currentTmp.push(inputTmp.front());
		inputTmp.pop();
		dispatch(inputTmp,currentTmp,output);
	}
}
 
int main()
{
	int nums=0;
	//处理输入
	while(cin>>nums)
	{
        resCon.clear();
		queue<int> input;//存放输入火车的队列
		stack<int> current;//存在火车站中火车的栈
		vector<int> output;//输出火车的序列
 
		//从标准输入中读取入队的火车标号
		for(int i=1;i<=nums;i++)
		{
			int tmp;
			cin>>tmp;
			input.push(tmp);
		}
 
		//调用分配函数
		dispatch(input,current,output);
        
        std::sort(resCon.begin(), resCon.end(), comp);  // 字典序排列
        for (auto& v: resCon) {
            for (int i=0;i<nums-1;++i) {
                cout<<v[i]<<" ";
            }
            cout<<v.back()<<endl;
        }
	}
	return 0;
}

//////////////////////////////////解法二/////////////////////////////////////////
#include<iostream>
#include<stack>
#include<algorithm>
using namespace std;
bool isOutNum(int *push,int *pop,int len)//判断pop是不是push的出栈序列
{
    if(push==NULL || pop==NULL ||len<=0)
        return false;
    stack<int> Stack;
    int i=0,j=0;
    for(i=0;i<len;i++)//依次把push中的数入栈
    {
        Stack.push(push[i]);
        while(j<len && Stack.size()!=0 && pop[j]==Stack.top())//依次判断pop序列每个值是否与栈顶相等
        {
            Stack.pop();
            j++;
        }
    }
    return Stack.empty();
}
int main()
{
    int N;
    while(cin>>N)
    {
        int *pushNum=new int [N];
        int *popNum=new int [N];
        for(int i=0;i<N;i++)
        {
            cin>>pushNum[i];
            popNum[i]=pushNum[i];
        }
        sort(popNum,popNum+N);
        do
        {
            if(isOutNum(pushNum,popNum,N))//如果该排列正确，则输出
            {
                for(int i=0;i<N-1;i++)
                    cout<<popNum[i]<<" ";
                cout<<popNum[N-1]<<endl;
            }
        }
        while(next_permutation(popNum,popNum+N));//获取下一个排列       
    }
    return 0;
}
```

分析：

- 解法一：模拟进站出站，递归+排序
- 解法二：利用全排列，删除不满足条件的序列
  - 判断一个全排列是否满足出站顺序：
    - 火车进站一个 stack.push(..)
    - 判断 stack.top() ==? queue.front() ， 相等 stack.pop(), queue.pop_front() ; 否则继续入栈 stack.push(..) 
    - 重复，直到进站序列压入完毕，stack 空说明顺序满足要求
- `std::next_permutation(..)` 获取下一个全排列
- `std::stack` 
  - push() 入
  - pop() 出
  - top() 获取栈顶
- `std::queue`
  - push()
  - pop()
  - front()

## 026 最长公共子串

```c
#include <bits/stdc++.h>

using namespace std;


int solve(string s1, string s2) {
    if (s1.size()>s2.size()) return solve(s2, s1);
    int n =0;
    for (int i=0;i<s1.size();++i) {
        for (int j=i+1;j<=s1.size();++j) {
            if (s2.find(s1.substr(i,j-i)) != -1) {
                n = std::max(n, j-i);
            }
        }
    }
    return n;
}

int main() {
    string str1, str2;
    while (getline(cin, str1)) {
        getline(cin, str2);
        int n = solve(str1, str2);
        cout<<n<<endl;
    }
}

/////////////////////////////动态规划////////////////////////////////
#include <bits/stdc++.h>

using namespace std;


int solve(string s1, string s2) {
    vector<vector<int>> dp(s1.size(), vector<int>(s2.size(), 0));
    int n = 0;
    for (int i=0;i<s2.size();++i) {
        if (s1[0]==s2[i]) dp[0][i] = 1;  // 处理边缘
    }
    for (int i=0;i<s1.size();++i) {   // 处理边缘
        if (s2[0]==s1[i]) dp[i][0] = 1;
    }
    for (int i=1;i<s1.size();++i) {
        for (int j=1;j<s2.size();++j) {
            if (s1[i]==s2[j]) {
                dp[i][j] = dp[i-1][j-1]+1;
                n = std::max(n, dp[i][j]);
            }
        }
    }
    return n;
}

int main() {
    string str1, str2;
    while (getline(cin, str1)) {
        getline(cin, str2);
        int n = solve(str1, str2);
        cout<<n<<endl;
    }
}
```

分析：

- 解法一：暴力查找，find, substr
- 解法二：动态规划 `dp[i][j]` 表示以 s1[i], s2[j] 结尾的两个子串的最长公共子串的长度; 初始条件的处理，可以多填充一行一列，与编辑距离、最长递增子序列 问题类似

## 027 参数解析

```c
#include <bits/stdc++.h>

using namespace std;

int main() {
    string str;
    while (getline(cin, str)) {
        str += " ";  // 一定要补一个分隔符在末尾
        vector<string> res;
        while (!str.empty()) {
            if (str[0]=='"') {   // 如果当前首字母是引号，
                str = str.substr(1);  // 跳过引号
                int pos = str.find('"');  // 找下一个引号
                res.push_back(str.substr(0, pos));  // 提取结果
                str = str.substr(pos+1);  // 剩下的字符串
            } else if (str[0]==' ') {  // 如果当前首字母是空格，跳过空格
                 str = str.substr(1);
            } else {                     // 否则是一个参数的开头
                int pos = str.find(' ');  // 找下一个空格
                res.push_back(str.substr(0, pos));  // 提取结果
                str = str.substr(pos+1);  // 剩下的字符串
            }
        }
        cout<<res.size()<<endl;
        for (auto& t:res) {
            cout<<t<<endl;
        }
        
    }
}
```

分析：

- 利用 find substr

## 028 判断一年第几天

```c
#include <bits/stdc++.h>

using namespace std;

bool isRunYear(int y) {
    return (y%4==0 && y%100!=0) || y%400==0;
}

int monDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main() {
    int year, mon, day;
    while (cin>>year>>mon>>day) {
        int n = 0;
        for (int i=1;i<mon;++i) {
            n += monDays[i];
        }
        n += day;
        if (isRunYear(year) && mon>2) {
            n+=1;
        }
        cout<<n<<endl;
    }
}
```

分析：

- 闰年判断方法：能被 4 整数且不能被 100 整除；或者能被 400 整除

## 029 百钱百鸡

```c
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n = 0;
    while (cin>>n) {
        n = 100;
        for (int i=0;i<n/5 && i<=n;++i) {
            for (int j=0;j<(n-5*i)/3 && j<=n-i;++j) {
                int k = n-5*i-3*j;
                if (i+j+3*k==n)
                    cout<<i<<" "<<j<<" "<<3*k<<endl;
            }
        }
    }
    
    return 0;
}
```

分析：

- 用枚举法解方程组
- 看清题目要求，没有输入

## 030 字符串匹配 * ？

```c
#include <bits/stdc++.h>

using namespace std;

int main() {
    
    string str, pat;
    while (getline(cin, pat)) {
        getline(cin, str);
        if (pat.empty() && !str.empty()) {
            cout<<"false"<<endl;
            continue;
        }
        if (str.empty() && pat!="*") {
            cout<<"false"<<endl;
        }
       vector<vector<int>> dp(pat.size(), vector<int>(str.size(), 0));
       if (pat[0]=='?' || pat[0] == str[0] ) dp[0][0] = 1;   // 边界处理
       if ( pat[0]=='*' ) for (int i=0;i<str.size();++i) dp[0][i] = 1;  // 边界处理
       for (int i=1;i<pat.size();++i) {
           for (int j=1;j<str.size();++j) {
                if (pat[i]!='*') {
                    dp[i][j] = (dp[i-1][j-1]) && (pat[i]==str[j] || pat[i]=='?');
                } else {
                    dp[i][j] = dp[i-1][j-1] || dp[i-1][j];
                }
           }
       }
        
        if (dp.back().back()) cout<<"true"<<endl;
        else cout<<"false"<<endl;
        
    }
    return 0;
}
```

分析

- 动态规划比较难的是**确定初始条件**，有两种处理方法
  - 填充 dp
  - 边界值单独考虑

- 其次就是确定**搜索方向**

## 031 单调栈：找到每个元素后面比它大的第一个数，要求时间复杂度为O(N)

```c
int main() {
	vector<int> a{3,2,1,4,0,8};
    stack<int> s;
    vector<int> res(a.size(), -1);
    for (int i=0;i<a.size();++i) {
        while (!s.empty() && a[s.top()] < a[i])  // 出栈条件，找到栈中部分元素的解，将该部分出栈
        {
            res[s.top()] = a[i];
            s.pop();
        }
        s.push(i);  // 满足单调性，入栈
    }

    print_vec(res);
    return 0;
}
```

- 维护一个单调递减的单调栈，满足递减就入栈，不满足说明找到栈顶元素的解，然后不断出站找出栈中元素的解，直到该元素又满足单调性，进栈，如此循环。

## 032 矩阵相乘

```c
#include <bits/stdc++.h>

using namespace std;

int main() {
    int x, y, z;
    while (cin>>x>>y>>z) {
        vector<vector<int>> A(x, vector<int>(y, 0));
        vector<vector<int>> B(y, vector<int>(z, 0));
        vector<vector<int>> C(x, vector<int>(z, 0));
        for (auto& row : A) {
            for (auto& i : row) {
                cin>>i;
            }
        }
        for (auto& row : B) {
            for (auto& i : row) {
                cin>>i;
            }
        }
        for (int i=0;i<x;++i) {
            for (int j=0;j<z;++j) {
                for (int k=0;k<y;++k) {
                    C[i][j] += A[i][k]*B[k][j];
                }
            }
        }
        for (auto& row : C)
        {
            for (auto& v: row)
            {
                cout<<v<<" ";
            }
            cout<<endl;
        }
            
    }
}
```

## 033 24 点游戏

```c
#include <bits/stdc++.h>

using namespace std;

char op[] = {'+', '-', '*', '/'};

double charOp(double a, double b, char op) {
    if (op=='+') return a+b;
    else if (op=='-') return a-b;
    else if (op=='*') return a*b;
    else return a/b;
}

bool solve(const vector<double> nums) {  // 运算符用循环枚举
    for (int i=0;i<4;++i) {
        double res2 = charOp(nums[0],nums[1],op[i]);
        for (int j=0;j<4;++j) {
            double res3 = charOp(res2,nums[2],op[j]);
            for (int k=0;k<4;++k) {
                double res4 = charOp(res3,nums[3],op[k]);
                if (res4==24) {
                    return true;
                }
            }
        }
    }
    return false;
}


int main() {
    vector<double> nums(4);
    bool f = 0;
    while (cin>>nums[0]>>nums[1]>>nums[2]>>nums[3]) {
        for (int i=0;i<24;++i) {
            if (solve(nums)) {
                cout<<"true"<<endl;
                f = 1;
                break;
            }
            std::next_permutation(nums.begin(), nums.end());   // 数字枚举用全排列解决
        }
        if (!f) cout<<"false"<<endl;
    }
    return 0;
}

///////////////////////////////////递归////////////////////////////////////

#include<iostream>
#include<vector>
using namespace std;
bool is24(vector<double> a, int tot, double result)
{
    if(a.empty())
    {
        return result==tot;
    }
    for(int i=0; i<a.size() ;i++)
    {
        vector<double> b(a);
        b.erase(b.begin()+i);  // 将访问过的数删除
        if(is24(b,tot,result+a[i])
           || is24(b,tot,result-a[i])
           || is24(b,tot,result*a[i])
           || is24(b,tot,result/a[i]))
            return true;
    }
    return false;
}
int main()
{
    vector<double> a(4,0);
    while(cin >> a[0] >> a[1] >> a[2] >> a[3])
    {
        if(is24(a,24,0))
            cout<<"true"<<endl;
        else cout<<"false"<<endl;
    }
}
```

- 运算数据类型应该 double, 否则无法通过！！！
- 循环或递归注意变量**恢复现场**，避免某个变量造成累积影响

## 034 命令匹配

```c
#include <bits/stdc++.h>

using namespace std;


string cmd[6][2] = {{"reset", ""},
               {"reset", "board"},
               {"board", "add"},
               {"board", "delet"},
               {"reboot", "backplane"},
               {"backplane","abort"}};

char* info[6] = {"reset what",
                "board fault",
                "where to add",
                "no board at all",
                "impossible",
                "install first"};
int cmd_len[6] = {1,2,2,2,2,2};

void solve(const string str) {
    int pos = str.find(' ');
    if (pos!=-1) {
        string s1 = str.substr(0,pos);
        string s2 = str.substr(pos+1);
        int match=0, num_match=0;
        for (int i=1;i<6;++i) {
            if (cmd[i][0].find(s1)!=-1 && cmd[i][1].find(s2)!=-1) {
                match = i;
                ++num_match;
            }
            if (num_match>1) {
                cout<<"unkown command"<<endl;
                return;
            }
        }
        if (num_match==1) {
            cout<<info[match]<<endl;
        } else {
            cout<<"unkown command"<<endl;
        }
        
    } else {
        if (cmd[0][0].find(str)!=-1) {
            cout<<"reset what"<<endl;
        } else {
            cout<<"unkown command"<<endl;
        }
    }
}


int main() {
    string str;
    while (getline(cin, str)) {
        solve(str);
    }
    return 0;
}
```

## 035 最长公共子串，输出内容

```c
#include <bits/stdc++.h>

using namespace std;

string findLargeSubStr(const string s1, const string s2) {
    if (s1.size()>s2.size()) return findLargeSubStr(s2,s1);
    if (s1.empty() || s2.empty()) return "";
    int max_len = 0;
    string res;
    vector<vector<int>> dp(s1.size(), vector<int>(s2.size(), 0));
    for (int i=0;i<s2.size();++i) {  // 边界值
        if (s1[0]==s2[i]) dp[0][i] = 1;
    }
    for (int i=0;i<s1.size();++i) {  // 边界值
        if (s1[i]==s2[0]) dp[i][0] = 1;
    }
    for (int i=1;i<s1.size();++i) {
        for (int j=1;j<s2.size();++j) {
            if (s1[i]==s2[j]) {
                dp[i][j] = dp[i-1][j-1]+1;
                if (dp[i][j] > max_len ) {
                    max_len =  dp[i][j];
                    res = s1.substr(i-max_len+1, max_len);
                }
            }
        }
    }
    return res;
}

int main() {
    
    string s1, s2;
    
    while (cin>>s1>>s2) {
        string res = findLargeSubStr(s1, s2);
        cout<<res<<endl;
    }
    
    return 0;
}
```

## 036 MP3 U D

```c
#include <bits/stdc++.h>

using namespace std;

int n, curr, s, e;  // 个数，当前光标，窗口起点，终点


void update(char c) {
    if (c=='U') {
        if (curr>s) {
            --curr;
        } else if (s==1) {
            curr = n;
            s = std::max(n-3, 1);
            e = n;
        } else {
            --curr;
            --s;
            --e;
        }
    } else if (c=='D') {
        if (curr<e) {
            ++curr;
        } else if (e==n) {
            curr = 1;
            s = 1;
            e = std::min(4, n);
        } else {
            ++curr;
            ++s;
            ++e;
        }
    }
}

int main() {
    
    string cmd;
    
    while (cin>>n>>cmd) {
        s = 1;
        e = std::min(4, n);
        curr = 1;
        for (auto& t : cmd) {
            update(t);
        }
        for (int i=s;i<=e;++i) {
            cout<<i<<" ";
        }
        cout<<endl;
        cout<<curr<<endl;
    }
    
    return 0;
}
```

## 037 DNA 序列

```c
#include <bits/stdc++.h>

using namespace std;


int main() {
    string str;
    int n;
    while(cin>>str>>n) {
        double r = 0.;
        string res;
        for (int i=0;i<=str.size()-n;++i) {
            int count = 0;
            for (int j=i;j<i+n;++j) {
                if (str[j]=='C' || str[j]=='G') {
                    ++count;
                }
                if (count/(double)n>r) {
                    r = count/(double)n;
                    res = str.substr(i,n);
                }
            }
        }
        cout<<res<<endl;
    }
}
```

分析：

- 本题不适合用动态规划，它的状态转移方程太简单了，只利用前一个状态，实际上用一个 count 变量就代替了

## 038 分苹果

```c
#include <bits/stdc++.h>

using namespace std;

int cnt = 0;

void solve(int m, int n, int last=0) {
    if (n==0) {
       if (m==0) ++cnt;
        return;
    }
    for (int i=last;i<=m;++i) {
        solve(m-i, n-1, i);
    }
}

int main() {
    int m , n;
    while(cin>>m>>n) {
        cnt = 0;
        solve(m, n);
        cout<<cnt<<endl;
    }
}
```

分析：

- 为了保证不不出现重复计数，可以在枚举时保证单调不减

## 039 素数之和

```c
#include <bits/stdc++.h>

using namespace std;

bool isPrime(int n) {  // 判断素数
    if (n==1) return false;
    for (int i=2;i<=sqrt(n);++i) {
        if (n%i==0) return false;
    }
    return true;
}

int main() {
    int n;
    while (cin>>n) {
        for (int i=0;i<n/2;++i) {
            if (isPrime(n/2-i) && isPrime(n/2+i)) {
                cout<<n/2-i<<endl;
                cout<<n/2+i<<endl;
                break;
            }
        }
    }
}
```

## 040 字符出现一次

```c
#include <bits/stdc++.h>

using namespace std;

int main() {
    string str;
    while (cin>>str) {
        unordered_map<char, uint32_t> charCnt;
        for (auto& c : str) {
            ++charCnt[c];
        }
        bool has = 0;
        for (auto& c : str) {
            if (charCnt[c]==1) {
                cout<<c<<endl;
                has = 1;
                break;
            }
        }
        if (!has) cout<<-1<<endl;
    }
}
```

分析：

- 还可以利用 str.find(c)==str.rfind(c) 判断是否出现一次

## 041 K 个最小数

```c
// 最大堆


#include<bits/stdc++.h>

using namespace std;
 
void Heap_K_Number(vector<int>& temp,int N,int k)
{
    if(k>N) return;
    //将前K个元素（下标为0~k-1）导入vector容器中，下面要制作堆
    vector<int> heap(temp.begin(),temp.begin()+k);
    //初始化最大堆
    make_heap(heap.begin(),heap.end());
     
    //从K+1个元素（下标就是k~N-1）
    for(int i=k;i<N;i++)
    {
        if(temp[i]<heap[0])//比堆顶元素小 ，调整堆
        {
            pop_heap(heap.begin(),heap.end());
            heap.pop_back();
             
            heap.push_back(temp[i]);
            push_heap(heap.begin(),heap.end());
        }
    }
     
    //输出堆
    for(int i=0;i<k-1;i++)
        cout<<heap[i]<<" ";
    cout<<heap[k-1]<<endl;
}
 
int main()
{
    int n,k,temp;
    vector<int> vec;
    while(cin>>n>>k)
    {
        for(int i=0;i<n;i++)
        {
            cin>>temp;
            vec.push_back(temp);
        }
        Heap_K_Number(vec,n,k);
    }
}
```

分析：

- 要输出数组的 k 个最小数，可以全排序，但是不高效，更好的方法是采用 **最大(小)堆**
- 可以借助 STL 中的 `make_heap`, `push_heap`, `pop_heap` 函数 ; 容器适配器 `priority_queue` 也是基于此
- push_heap 将最后的元素归位；pop_heap 将最大的元素移到最后，同时调整前面顺序

## 042 字符串加减

```c
#include <bits/stdc++.h>

using namespace std;

string addStr(string s1, string s2) { // 处理 s1 + s2
    if (s1.size()<s2.size()) {
        return addStr(s2, s1);
    }
    s2 = string(s1.size()-s2.size(), '0') + s2;
    string res = "";
    auto it1 = s1.rbegin();
    auto it2 = s2.rbegin();
    int carr = 0;
    for (;it1<s1.rend();++it1,++it2) {
        int n1 = *it1 - '0';
        int n2 = *it2 - '0';
        int sum = n1 + n2 + carr;
        carr = sum / 10;
        res = (char)(sum % 10 + '0') + res;
    }
    if (carr) {
        res = '1' + res;
    }
    int i = 0;
    for (;i<res.size();++i) {
        if (res[i]!='0') break;
    }
    return res.substr(i);
}

string substractStr(string s1, string s2, int sign=0) {  // 处理 s1 - s2
    if (s1.size()<s2.size() || s1<s2) return substractStr(s2, s1, -1); // 保证大数减小数
    size_t max_size = std::max(s1.size(), s2.size());
    s1 = string(max_size-s1.size(), '0') + s1;
    s2 = string(max_size-s2.size(), '0') + s2;
    string res = "";
    auto it1 = s1.rbegin();
    auto it2 = s2.rbegin();
    int carr = 0;
    for (;it1<s1.rend();++it1,++it2) {
        int n1 = *it1 - '0';
        int n2 = *it2 - '0';
        if (n1+carr>=n2) {
            int n = n1-n2+carr;
            carr = 0;
            res = (char)(n+'0') + res;
        } else {
            int n = n1+carr+10-n2;
            carr = -1;
            res = (char)(n+'0') + res;
        }
    }
    int i = 0;
    for (;i<res.size();++i) {
        if (res[i]!='0') break;
    }
    res = res.substr(i);
    if (sign<0) res = '-' + res;
    return res;
}

int main() {
    string s1, s2;
    while (cin>>s1>>s2) {
        string res;
        if (s1[0]!='-' && s2[0]!='-')  // 同号 +
            res = addStr(s1, s2);
        else if (s1[0]=='-' && s2[0]=='-') {  // 同号 -
            res = '-' + addStr(s1.substr(1), s2.substr(1));
        } else if (s1[0]=='-') {  // (-s1)+s2
            res = substractStr( s2, s1.substr(1));
        } else if (s2[0]=='-') {  // s1+(-s2)
            res = substractStr( s1,  s2.substr(1));
        }
        cout<<res<<endl;
    }
}
```

## 043 完全数

```c
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    while (cin>>n) {
        if (n==1) {
            cout<<0<<endl;
            continue;
        }
        int cnt = 0;
        for (int i=2;i<=n;++i) {
            int sum = 1;
            for (int j=2;j<=sqrt(i);++j) {
                if (i%j==0) {
                    sum += j;
                    sum += i/j;
                }
            }
            if (sum == i) {
                ++cnt;
               // cout<<i<<endl;
            }
        }
        cout<<cnt<<endl;
    }
}
```

## 044 表达式求值

```c
#include <bits/stdc++.h>

using namespace std;

unordered_map<char, int> prop = {{'+',1},
                                 {'-',1},
                                 {'*',2},
                                 {'/',2}};

stack<char> sig;
stack<int> num;

void calc(char op) {
    int n2 = num.top();
    num.pop();
    int n1 = num.top();
    num.pop();
    if (op=='+') num.push(n1+n2);
    else if (op=='-') num.push(n1-n2);
    else if (op=='*') num.push(n1*n2);
    else if (op=='/') num.push(n1/n2);
    
}

int main() {
    string str;
    while (cin>>str) {
        vector<string> vec;
        int i=0,j=0;
        while (i<str.size()) {
            while (isdigit(str[j]) && j<str.size()) ++j; 
            if (j>i) vec.push_back(str.substr(i,j-i));
            i = j;
            while (!isdigit(str[j]) && j<str.size()) {
                vec.push_back(str.substr(j, 1));
                ++j; 
            }
            i=j;
        }
        
        stack<char>().swap(sig);
        stack<int>().swap(num);
        
        for (int i=0;i<vec.size();++i) {
            if (isdigit(vec[i][0])) num.push(atoi(vec[i].c_str()));
            else if (vec[i]=="(") {
                sig.push('(');
            }
            else if (vec[i]==")") {
                 while (sig.top()!='(') {
                     calc(sig.top());
                     sig.pop();
                 }
                sig.pop();
            }
            else {
                while (!sig.empty() && prop[vec[i][0]]<=prop[sig.top()] && sig.top()!='(') {
                    calc(sig.top());
                    sig.pop();
                }
                sig.push(vec[i][0]);
            }
        }
        while (!sig.empty()) {
            calc(sig.top());
            sig.pop();
        }
        cout<<num.top()<<endl;
    }
}
```

分析：

- 思想：将中缀表达式转后缀表示式
- 算法
  
  - 遇到 数字 进数字栈
  - 遇到 "(" 进符号栈
  - 遇到 ")" 符号栈出栈，直到遇到 "(", 同时每出栈一个符号，从数字栈弹出两个数字作运算，再将结果入栈
  - 遇到其它运算符号，将符号栈出栈（同时从数字栈弹出两个数字作运算，再将结果入栈），直到栈顶元素优先级**低于**该符号，然后该符号入栈
  - 扫描完表达式后，将符号栈依次弹出，做运算
  - 最终结果在数字栈
  
  

## 045 杨辉三角

```c
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    while (cin>>n) {
        if (n<2) {
            cout<<"-1"<<endl;
            continue;
        }
        vector<vector<int>> arr(n, vector<int>(2*n-1, 0));
        arr[0][0] = 1;
        for (int i=1;i<n;++i) {
            arr[i][0] = 1;
            arr[i][1] = 1+arr[i-1][1];
            for (int j=2;j<2*n-1;++j) {
                arr[i][j] = arr[i-1][j-1] + arr[i-1][j-2] + arr[i-1][j];  // 递推公式
            }
        }
        bool has = 0;
        for (int i=0;i<=n;++i) {
            if (!(arr[n-1][i] & 1)) {
                cout<<i+1<<endl;
                has = 1;
                break;
            }
        }
        if (!has) cout<<"-1"<<endl;
    }
}
```

## 046 换汽水

- 贪心算法

## 047 约瑟夫环

```c
#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("playground/data.in", "r", stdin);
    int n;
    while (cin>>n) {
        list<int> L;
        for (int i=0;i<n;++i) L.push_back(i);
        int curr = 0;
        while (L.size()>1) {
            curr = (curr+2)%L.size();  // 取摸获得下一个该删除的索引
            L.erase(std::next(L.begin(), curr));
        }
        cout<<L.front()<<endl;
    }
}
```

- 使用 std::list
- 注意：list::iterator 不支持 operator+，所以 L.begin() + curr 编译出错，vector 是支持的，换成 std::next(it, offset)

## 048 解数独

```c
// freopen("playground/data.in", "r", stdin);

#include <bits/stdc++.h>

using namespace std;

bool isValid(const vector<vector<int>>& B, int i, int j, int val) {
    for (int k=0;k<9;++k) {
        if (B[i][k]==val) return false;
        if (B[k][j]==val) return false;
        if ( B[3*(i/3) + k/3][3*(j/3) + k%3] == val) return false; 
    }
    return true;
}

bool solve(vector<vector<int>>& B) {
    for (int i=0;i<9;++i) {
        for (int j=0;j<9;++j) {
            if (B[i][j]!=0) continue;
            for (int k=1;k<10;++k) {
                if (isValid(B, i, j, k)) {
                    B[i][j] = k;
                    if (solve(B)) return true;
                    else B[i][j] = 0;
                }
            }
            return false;
        }
    }
    return true;
}

int main() {
   freopen("playground/data.in", "r", stdin);
   
   while (!cin.eof()) {
       vector<vector<int>> B(9, vector<int>(9));
       for (auto & v : B) {
           for (auto & t : v) {
               cin>>t;
           }
       }
       solve(B);
       for (auto & v : B) {
           for (auto & t : v) {
               cout<<t<<" ";
           }
           cout<<endl;
       }
   }
         
}
```

## 049 链表

```c
#include <bits/stdc++.h>

using namespace std;

struct ListNode
{
    int val;
    ListNode* next;
    
    ListNode() {}
    ListNode(int val): val(val) {}
};

int main()  {
    int n;
    while (cin>>n) {
        ListNode* head = new ListNode;
        ListNode* curr = head;
        
        for (int i=0;i<n;++i) {
            int m;
            cin>>m;
            curr->next = new ListNode(m);
            curr = curr->next;
        }
        
        int t;
        cin>>t;
        if (t>n || t<=0) {
            cout<<0<<endl;
            continue;
        }
        
        curr = head;
        for (int i=0;i<=n-t;++i) {
            curr = curr->next;
        }
        cout<<curr->val<<endl;
    }
}
```

## 050 四则运算

```c
#include <bits/stdc++.h>

using namespace std;

stack<char> ops;
stack<int> res;

unordered_map<char, int> M = {{'+', 1},
                              {'-', 1},
                              {'*', 2},
                              {'/', 2}};

void calc(char op) {
    int b = res.top();
    res.pop();
    int a = res.top();
    res.pop();
    if (op=='+') res.push( a+b );
    else if (op=='-') res.push(a-b);
    else if (op=='*') res.push( a*b );
    else if (op=='/') res.push(a/b);
}

int main() {
    string str;
    while (getline(cin, str)) {
        for (auto& c : str) {
            if (c=='[' || c=='{') c = '(';
            else if (c==']' || c=='}') c = ')';
            
        }
        
        // 2-(-4-5) -> 2-(0-4-5)
        for (int i=0;i<str.size()-1;++i) {
            if (str[i]=='(' && str[i+1]=='-') {
                str.insert(i+1, 1, '0');
            }
        }
        
        //cout<<str<<endl;
        
        stack<char>().swap(ops);
        stack<int>().swap(res);
        
        for (int i=0;i<str.size();) {
            if (str[i]=='(') {  // 先判断是否是"(", 是直接入符号栈
                ops.push('(');
                ++i;
            }
            else if (str[i]==')') {  // 如果是 ")", 出栈并计算，知道遇到 "("
                while (ops.top()!='(') {
                    calc(ops.top());
                    ops.pop();
                }
                ops.pop(); // 弹出 "("
                ++i;
            }
            else if ( M.find(str[i]) != M.end() ) {  // 运算符处理
                while (!ops.empty() && M[ops.top()]>=M[str[i]] && ops.top()!='(') {
                    calc(ops.top());
                    ops.pop();
                }
                ops.push(str[i]);
                ++i;
            }
            else if (isdigit(str[i])) {  // 数字处理
                int n = 0;
                while ( i<str.size() && isdigit(str[i]) ) {
                    n = 10*n + str[i]-'0';
                    ++i;
                }
                res.push(n);
               // cout<<n<<endl;
            }
        }
        
        while (!ops.empty()) {
            calc(ops.top());
            ops.pop();
        }
        
        cout<<res.top()<<endl;
    }
    
    return 0;
}
```

## 051 多线程交替打印

```c
// freopen("playground/data.in", "r", stdin);

#include <bits/stdc++.h>
#include <thread>
#include <future>

using namespace std;


std::mutex mtx1, mtx2, mtx3, mtx4;
std::atomic_bool finish(false);


void fun1(int n) {
    for (int i=0;i<n;++i) {
        mtx1.lock();
        cout<<"A";
        mtx2.unlock();
    }
    finish = true;    
}

void fun2() {
    while (!finish) {
        mtx2.lock();
        cout<<"B";
        mtx3.unlock();
    }
}

void fun3() {
    while (!finish) {
        mtx3.lock();
        cout<<"C";
        mtx4.unlock();
    }
}

void fun4() {
    while (!finish) {
        mtx4.lock();
        cout<<"D";
        mtx1.unlock();
    }
}

void init() {
    mtx2.lock();
    mtx3.lock();
    mtx4.lock();
}

int main() {
    //freopen("playground/data.in", "r", stdin);
    int n;
    while (cin>>n) {

        init();        
        
        thread td2 = thread(fun2);
        thread td3 = thread(fun3);
        thread td4 = thread(fun4); 
        thread td1 = thread(fun1, n);
        
        td1.join();
        td2.join();
        td3.join();
        td4.join();
    }
    return 0;
}

```

分析：

- 循环相互唤醒

## 052 矩阵乘法次数

```c
#include <bits/stdc++.h>

using namespace std;


int main() {
    int n;
    while (cin>>n) {
        unordered_map<char, pair<int,int>> M;
        for (int i=0;i<n;++i) {
            int a,b;
            cin>>a>>b;
            M['A'+i] = make_pair(a, b);
        }
        string str;
        cin>>str;
        string str2="";
        for (int i=0;i<str.size()-1;++i) {
            str2 += str[i];
            if (str[i]!='(' && str[i+1]!=')' || str[i]==')' && str[i+1]!=')') {
                str2 += '*';
            }
        }
        str2 += str.back();
        
        //cout<<str2<<endl;
        
        stack<pair<int,int>> stack_p;
        stack<char> stack_c;
        int res = 0;
        int cnt1=0,cnt2=0;
        for (int i=0;i<str2.size();++i) {
            if (str2[i]=='(') {
                stack_c.push('(');
                ++cnt1;
            }
            else if (str2[i]==')') {
                if (++cnt2>cnt1) continue;  // ")" 有多于 "(" 的情况
                while (stack_c.top()!='(') {
                   stack_c.pop();
                    pair<int,int> p2 = stack_p.top();
                    stack_p.pop();
                    pair<int,int> p1 = stack_p.top();
                    stack_p.pop();
                    res += p1.first*p1.second*p2.second;
                    stack_p.push(make_pair(p1.first,p2.second));
                }
                stack_c.pop();
            }
            else if (str2[i]=='*') {
                while (!stack_c.empty() && stack_c.top()!='(') {
                    stack_c.pop();
                    pair<int,int> p2 = stack_p.top();
                    stack_p.pop();
                    pair<int,int> p1 = stack_p.top();
                    stack_p.pop();
                    res += p1.first*p1.second*p2.second;
                    stack_p.push(make_pair(p1.first,p2.second));
                }
                stack_c.push('*');
            }
            else {
                stack_p.push(M[str2[i]]);
            }
        }
        while (!stack_c.empty()) {
            stack_c.pop();
            pair<int,int> p2 = stack_p.top();
            stack_p.pop();
            pair<int,int> p1 = stack_p.top();
            stack_p.pop();
            res += p1.first*p1.second*p2.second;
        }
        cout<<res<<endl;
    }
}
```

分析：

- 类比四则运算

## 053 链表插入删除

```c
#include <bits/stdc++.h>

using namespace std;

struct Node
{
    int val;
    Node* next;
    Node():val(0), next(NULL) {}
    Node(int v):val(v), next(NULL) {}
};


int main() {
    int n;
    while (cin>>n) {
        int m;
        cin>>m;
        Node* head = new Node(m);
        for (int i=0;i<n-1;++i) {
            int a,b;
            cin>>a>>b;
            Node* curr = head;
            while (curr!=NULL) {
                if (curr->val==b) {
                    Node* tmp = new Node(a);
                    tmp->next = curr->next;
                    curr->next = tmp;
                    break;
                }
                curr = curr->next;
            }
        }
        int d;
        cin>>d;
        Node* curr = new Node;
        curr->next = head;
        while (curr->next!=NULL) {
            if (curr->next->val==d) {
                Node* tmp = curr->next;
                curr->next = curr->next->next;
                delete tmp;
                break;
            }
            curr = curr->next;
        }
        curr = head;
        while (curr!=NULL) {
            cout<<curr->val<<" ";
            curr = curr->next;
        }
        cout<<endl;
    }
}
```

分析：

- 节点删除时需要使用**哑节点**（特别是删除头部时）
- 经典：删除单向链表的倒数第 N 个节点，双指针法，同时使用哑节点

