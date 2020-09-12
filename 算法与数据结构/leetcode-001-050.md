

```python
import numpy as np
from IPython.display import display, HTML

def print_(a):
    display(a)
```

- https://leetcode-cn.com/problemset/all/

## 001 two sum

要求：数组 a 中值各不相同，给定一个 target, 找出使得数组中两个数之和等于 target 的索引 


```python
def two_sum(a, target):
    d = {}
    res = (-1,-1)
    if len(a)<2:
        return res
    for i,v in enumerate(a):
        t = target - v
        if t in d:
            res = (d[t], i)
            break
        d[v] = i
    return res

a = [0, 1, 2, 4, 6, 7, 4, 9]
res = two_sum(a, 11)
res
```




    (3, 5)



分析：
- 使用的数据结构：dict
- 时间复杂度：$O(n)$
- 空间复杂度：$O(n)$

## 002 add two numbers

要求：现有两个链表，分别表示两个整数的各个数位的数字，从个位开始，求两个整数的和，并返回链表。


```python
class Node:
    
    def __init__(self, data):
        self.next = None
        self.data = data

class LinkedList:
    
    def __init__(self):
        self.head = None
        self.tail = None
    
    def add_node(self, data):
        node = Node(data)
        if self.head is None:
            self.head = node
            self.tail = node
        else:
            self.tail.next = node
            self.tail = node
    
    def __str__(self):
        temp = self.head
        s=''
        while temp is not None:
            s += '{}->'.format(temp.data)
            temp = temp.next
        return s[:-2]

l1 = LinkedList()
l2 = LinkedList()

l1.add_node(1)
l1.add_node(7)
l1.add_node(2)
l1.add_node(2)

l2.add_node(2)
l2.add_node(4)
l2.add_node(9)


print(l1)
print(l2)


def add_two_num(l1, l2):
    res = LinkedList()
    t1, t2 = l1.head, l2.head
    sum = 0
    zero_node = Node(0)
    while t1 or t2:
        t1 = t1 if t1 else zero_node
        t2 = t2 if t2 else zero_node
        sum = t1.data + t2.data + sum
        res.add_node(sum%10)
        sum //= 10
        t1, t2 = t1.next, t2.next
    if sum == 1:
        res.add_node(1)
    return res

res = add_two_num(l1, l2)
print(res)
```

    1->7->2->2
    2->4->9
    3->1->2->3


分析：
- 时间复杂度是 $O(n)$
- 关键是链表的创建和使用

## 003 longest substring without repeating characters

要求：给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。


```python
def longest_substring(s):
    j, n = 0, 0  # j: 新的不重复子串起始位置；n: 子串长度
    d = {}  # 过去看过的字符串字典, key->character; value->index
    for i, ss in enumerate(list(s)):
        if ss in d:
            n = max(n, i-j)  # 有重复才更新子串长度
            j = max(j, d[ss]+1)  # 有重复才更新子串起始位置
        d[ss] = i  # 将看过的字符添加的字典中
        print('i:',i)
        print('j:',j)
        print('n:',n)
        print(d)
    n = max(len(s)-j, n)  # 因为是有重复才更新，最后可能少更新一次，所以再更新一遍
    return n


# def fun(s):
#     st = {}
#     i, ans = 0, 0
#     for j in range(len(s)):
#         if s[j] in st:
#             i = max(st[s[j]], i)
#         ans = max(ans, j - i + 1)
#         st[s[j]] = j + 1
#     return ans

s = "aacdbbb"

longest_substring(s)
```

    i: 0
    j: 0
    n: 0
    {'a': 0}
    i: 1
    j: 1
    n: 1
    {'a': 1}
    i: 2
    j: 1
    n: 1
    {'a': 1, 'c': 2}
    i: 3
    j: 1
    n: 1
    {'a': 1, 'c': 2, 'd': 3}
    i: 4
    j: 1
    n: 1
    {'a': 1, 'c': 2, 'd': 3, 'b': 4}
    i: 5
    j: 5
    n: 4
    {'a': 1, 'c': 2, 'd': 3, 'b': 5}
    i: 6
    j: 6
    n: 4
    {'a': 1, 'c': 2, 'd': 3, 'b': 6}





    4



分析：
- 因为需要多次进行查找操作，所以采用**字典**
- 时间复杂度 $O(n)$

## 004 寻找两个有序数组的中位数

要求：
- 给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。
- 请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。
- 你可以假设 nums1 和 nums2 不会同时为空。


```python
import numpy as np

def fun(nums1, nums2):
    N1 = len(nums1)
    N2 = len(nums2)
    
    if N1 > N2:  # 保证 nums1 的长度小于 nums2 的长度
        return fun(nums2, nums1)
    
    lo, hi = 0, 2*N1  # 二分 nums1 时的首位两个位置索引
    while lo<=hi:
        c1 = (lo+hi)//2  # nums1 切割的位置的索引
        c2 = N1+N2-c1  # 推算出 nums2 切割的位置的索引
#         print('c1:', c1)
#         print('c2:', c2)
#         print('lo:', lo)
#         print('hi:', hi)
        lmax1 = -np.inf if c1==0 else nums1[(c1-1)//2]  # nums1 切割左侧最大值
        rmin1 = np.inf if c1==2*N1 else nums1[c1//2]  # nums1 切割右侧侧最小值
        lmax2 = -np.inf if c2==0 else nums2[(c2-1)//2]  # nums2 切割左侧最大值
        rmin2 = np.inf if c2==2*N2 else nums2[c2//2]  # nums2 切割右侧最小值
#         print('lmax1:', lmax1)
#         print('rmin1:', rmin1)
#         print('lmax2:', lmax2)
#         print('rmin2:', rmin2)
#         print('-----------------------------------')

        if lmax1 > rmin2:  # 若两个切割位置合理，则应满足 左侧 < 右侧，否则，应该继续二分切割
            hi = c1-1
        elif lmax2 > rmin1:
            lo = c1+1
        else:
            break
    return (max(lmax1, lmax2)+min(rmin1, rmin2)) / 2.0

a = [3,4]
b = [1]
fun(a,b)
```




    3.0



分析：
- 难点在于时间复杂度要求，要充分利用中位数的特点和两个数组的排好序的特点
- 想法是，将 nums1（较短序列）进行二分切割，并假定**其切割位置左侧序列构成总体序列的前半部分**，则另一部分可以由 nums2 前一部分组成，nums2 的切割位置可以推算出来，然后根据 lmax1, rmin1, lmax2, rmin2 的大小关系进行验证，若 $lmax1 < rmin2 \ \ and \ \ lmax2 < rmin1$ 则 $median = ( max(lmax1, lmax2) + min(rmin1, rmin2) ) \ \ / \ \ 2.0$, 否则，继续对 nums1 进行二分
- 在实现过程中，为了便于进行索引的计算，对数组进行“虚拟填充”
- [解析参考](https://leetcode-cn.com/problems/median-of-two-sorted-arrays/solution/4-xun-zhao-liang-ge-you-xu-shu-zu-de-zhong-wei-shu/)


```python
# 二分法查找

a = list(range(10))
target = 6

def binary_search_arr(a, t):
    lo, hi = 0, len(a)-1
    res = -1
    while lo<=hi:
        c = (lo+hi)//2
        print('[{}, {}] - {}'.format(lo, hi, c))
        print('--------------------------------')
        if a[c] < t:
            lo = c + 1
        elif a[c] > t:
            hi = c - 1
        else:
            print('find at', c)
            res = c
            break
    if res == -1:
        print('not find')
    return res
    
binary_search_arr(a, target)
    
```

    [0, 9] - 4
    --------------------------------
    [5, 9] - 7
    --------------------------------
    [5, 6] - 5
    --------------------------------
    [6, 6] - 6
    --------------------------------
    find at 6





    6



关于二分法：
- 二分查找算法有两种，连续二分和离散二分
- 离散二分如上例所示，对数组索引进行二分
- 连续二分比如二分法求方程的近似根，是对一连续区间进行二分

## 005 最长回文子串

要求：给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。


```python
import numpy as np

def fun(s):
    n = len(s)
    if n == 0:
        return ''
    dp = np.zeros((n,n), dtype=bool)
    res = ''
    for k in range(n):
        for i, j in zip(range(n-k), range(k,n)):
            con = s[i]==s[j] and (j-i<=2 or dp[i+1, j-1])   
            if con:
                dp[i,j]=True
                res = s[i:j+1] if (j-i+1)>len(res) else res
    return res

res=fun("abcba")
res
```




    'abcba'



分析：
- 本题用**动态规划求解**，因为一个回文字符串的中心子串也必然是回文字符串，而这个子串又可以用来判断更大的字符串，因此，这是个**有重叠的子问题的问题**，所以想到用动态规划求解
- 用动态规划求解要考虑以下几个问题：
    - 选择状态变量
    - 建立解表
    - 确定解的递推方程
    - 确定求解顺序
- 本题建立一个 $n \times n$ 的二维 bool 数组 $dp$, $dp[i,j]$ 表示子串 $s[i:j+1]$ 是否是回文字符串；求解顺序是 $(0,0),(1,1),...,(n-1, n-1),(0,1),(1,2),...,(n-2, n-1),(0,2),(1,3), ...$ 从主对角线依次斜向上

## 006 Z 字形变换

要求：将一个给定字符串根据给定的行数，以从上往下、从左到右进行 Z 字形排列。


```python
class Solution:
    def convert(self, s: str, numRows: int) -> str:
        if numRows <=1:
            return s
        l = ['' for i in range(numRows)]
        c = (2*numRows-2)
        for i, ss in enumerate(s):  
            y = i % c
            m = y if y<numRows else c-y
#             print(i,m)
            l[m]+=ss
        return ''.join(l)

s = 'LEETCODEISHIRING'
n = 4
Solution().convert(s, n)
```




    'LDREOEIIECIHNTSG'



分析：
- 遍历一遍，只要找出原来字符串在 “Z” 字形排列的哪一行就行
- 时间复杂度 $O(n)$

## 007 整数反转

给出一个 32 位的有符号整数，你需要将这个整数中每位上的数字进行反转，反转后溢出返回 0。


```python
class Solution:
    def reverse(self, x: int) -> int:
        if x>=0:
            res = int(str(x)[::-1])
        else:
            res = - int(str(-x)[::-1])
        if res>(2**31-1) or res<-2**31:
            res = 0
        return res

Solution().reverse(1563847412)
```




    0



## 008 字符串转换整数(atoi)

要求：请你来实现一个 atoi 函数，使其能将字符串转换成整数。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/string-to-integer-atoi


```python
class Solution:
    def myAtoi(self, str: str) -> int:
        str = str.strip()
        if len(str) == 0:
            return 0
        flg = 1
        res = 0
        count = 0
        cand = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
        if str[0] not in (['-','+'] + cand):
            return 0
        if len(str) == 1 and str[0] in ['-', '+']:
            return 0
        if str[0] == '-':
            flg = -1
            str = str[1:]
        elif str[0] == '+':
            flg = 1
            str = str[1:]
        for s in str:
            if '0'<=s<='9':
                res = res*10 + int(s)
                count += 1
            else:
                break
        if count==0:
            return 0
        if flg>0:
            res = min(res, 2**31-1)
        else:
            res = min(res, 2**31)
        return flg*res

Solution().myAtoi("  314.159sdf")
```




    314



分析：
- 复杂在对题意的全面理解和思维缜密性
- ord() 字符转 ASCII，字符也可以比较大小（根据 ASCII）


```python
cand = ['-', '+'] + [str(i) for i in range(10)]
print('d' in cand)

print(ord('0'))
cand
```

    False
    48





    ['-', '+', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9']



## 009 回文数

要求：判断一个整数是否是回文数。回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。


```python
class Solution:
    def isPalindrome(self, x: int) -> bool:
        s = str(x)
        return s == s[::-1]
```

## 010 正则表达式匹配

给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。


```python
import numpy as np

# 递归法
class Solution1(object):
    def isMatch(self, text, pattern):
        if not pattern:
            return not text

        first_match = bool(text) and pattern[0] in {text[0], '.'}

        if len(pattern) >= 2 and pattern[1] == '*':
            return (self.isMatch(text, pattern[2:]) or
                    first_match and self.isMatch(text[1:], pattern))
        else:
            return first_match and self.isMatch(text[1:], pattern[1:])

# # 动态规划
# class Solution2(object):
#     def isMatch(self, text, pattern):
#         dp = [[False] * (len(pattern) + 1) for _ in range(len(text) + 1)]

#         dp[-1][-1] = True
#         for i in range(len(text), -1, -1):
#             for j in range(len(pattern) - 1, -1, -1):
#                 first_match = i < len(text) and pattern[j] in {text[i], '.'}
#                 if j+1 < len(pattern) and pattern[j+1] == '*':
#                     dp[i][j] = dp[i][j+2] or first_match and dp[i+1][j]
#                 else:
#                     dp[i][j] = first_match and dp[i+1][j+1]

#         return dp[0][0]

# 作者：LeetCode
# 链接：https://leetcode-cn.com/problems/regular-expression-matching/solution/zheng-ze-biao-da-shi-pi-pei-by-leetcode/
# 来源：力扣（LeetCode）
# 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。


class Solution2:
    def isMatch(self, s: str, p: str) -> bool:
        #if not s or not p:
            #return False
        s_len = len(s)
        p_len = len(p)
        dp = [[False] * (p_len + 1) for _ in range(s_len + 1)]
        #print(dp)
        dp[0][0] = True
        
        # 一种情况单独处理
        for i in range(p_len):
            if p[i] == "*" and dp[0][i - 1]:
                dp[0][i + 1] = True
        #print(dp)
        
        for i in range(s_len):
            for j in range(p_len):
                if p[j] in [s[i], "."]:
                    dp[i + 1][j + 1] = dp[i][j]
                elif p[j] == "*":
                    if p[j-1] not in [s[i], '.']:
                        dp[i + 1][j + 1] = dp[i + 1][j - 1]
                    else:
                        dp[i+1][j+1] = (dp[i][j+1] or dp[i+1][j] or dp[i+1][j-1])
        print_(dp)
        return dp[-1][-1]

# 作者：powcai
# 链接：https://leetcode-cn.com/problems/regular-expression-matching/solution/dong-tai-gui-hua-by-powcai/
# 来源：力扣（LeetCode）
# 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

p = 'c*a*b'
s = 'aab'
Solution2().isMatch(s,p)
```


    [[True, False, True, False, True, False],
     [False, False, False, True, True, False],
     [False, False, False, False, True, False],
     [False, False, False, False, False, True]]





    True



动态规划求解思路：
- 设一个二维 bool 数组 $dp$, $size=[len(s)+1, len(p)+1]$, 其中 $dp[i,j]$ 表示 s[:i] 和 p[:j] 是否匹配
- 自底向上开始遍历求解（填表）
- 解的转移方程：
    - $p[j] == s[i] \ \ or \ \ p[j] == '.': \ \ dp[i+1][j+1] = dp[i][j]$   eg. 'abc' vs 'abd' => 'ab' vs 'ab'
    - $p[j]=='*'$:
        - $p[j-1]!=s[i] : \ \ dp[i+1][j+1]=dp[i+1][j-1]$   eg. 'abc*' vs 'ab' => 'ab' vs 'ab'
        - $p[j-1]==s[i] or p[j-1]=='.'$, check
            - $dp[i][j+1]$  eg. 'abc*' vs 'abcc' => 'abc*' vs 'abc' (* 匹配多个)
            - $dp[i+1][j]$  eg. 'abc*' vs 'abc'  => 'abc' vs 'abc' (* 匹配一个)
            - $dp[i+1][j-1]$  eg. 'ab.*' vs 'ab' => 'abc' vs 'abc' (* 匹配零个)
- 一种单独处理的情况：eg. 'a*b*c*' vs 'x' => 'a*b*' vs '' => 'a*' vs '' => '' vs ''

## 011 盛最多水的容器

要求：给定 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0)。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/container-with-most-water
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。


```python
# 暴力搜索
class Solution:
    def maxArea(self, height):
        res = 0
        for i in range(0, len(height)-1):
            for j in range(i+1, len(height)):
                res = max(res, min(height[i], height[j])*(j-i))
        return res

# 双指针算法
class Solution2:
    def maxArea(self, h):
        res = 0
        l, r = 0, len(h)-1
        while l<r:
            res = max(res, min(h[l],h[r])*(r-l))
            if h[l]<h[r]:
                l += 1
            else:
                r -= 1
        return res
```

分析：
- 采用暴力搜索，时间复杂度为 $O(n^2)$
- 采用**双指针法**，时间复杂度为 $O(n)$

## 012 整数转罗马数字



```python
from collections import OrderedDict

class Solution:
    def intToRoman(self, num: int) -> str:
        d = {1000: 'M', 900: 'CM', 500: 'D', 400: 'CD', 100: 'C', 90: 'XC', 50: 'L', 40: 'XL', 10: 'X', 9: 'IX', 5: 'V',  4:'IV', 1: 'I'}
        d = OrderedDict(d)
#         print(d)
        res = ''
        for k, v in d.items():
            if num < k:
                continue
#             print(k,v)
            t, l = num // k, num % k
            res += v*t
            num = l
        return res

Solution().intToRoman(3999)
```




    'MMMCMXCIX'



分析：
- 看特殊问题能否一般化处理

## 013 罗马数字转整数



```python
class Solution:
    def romanToInt(self, s: str) -> int:
        d = {'M': 1000, 'CM': 900, 'D': 500, 'CD': 400, 'C': 100, 
             'XC': 90, 'L': 50, 'XL': 40, 'X': 10, 'IX': 9, 'V': 5, 
             'IV': 4, 'I': 1}
        sum = 0
        i = 0
        while i < len(s):
            try:
                sum += d[s[i:i+2]]
                i += 2
            except:
                sum += d[s[i]]
                i += 1
        return sum

Solution().romanToInt("MCMXCI")
```




    1991



分析：
- 解法一采用异常处理的方法，优先处理特殊情况
- 另一种解法是：对字符串从左到右扫描，如果当前字符代表的值不小于其右边，就加上该值；否则就减去该值。以此类推到最左边的数，最终得到的结果即是答案

## 014 最长公共前缀

要求：编写一个函数来查找字符串数组中的最长公共前缀。


```python
class Solution:
    def longestCommonPrefix(self, strs):
        res = ''
        try:
            for i in range(len(strs[0])):
                ch = strs[0][i]
                flg = True
                for s in strs[1:]:
                    if s[i]!=ch:
                        flg = False
                        break
                if flg:
                    res+=ch
                else:
                    break
        except:
            pass
        return res

strs = ['abcf', 'abcde', 'ab']
Solution().longestCommonPrefix(strs)
```




    'ab'



分析：
- 采用异常捕获，省略额外的条件判断，以上方法采用的是字符串递增的策略
- 另一种策略是字符串递减的策略，以第一个字符串作为基准，和后续比较，看基准串是否是公共前缀，不是就去掉最后一个更新基准串，继续与后续比较

## 015 三数之和

给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？找出所有满足条件且不重复的三元组。

注意：答案中不可以包含重复的三元组。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/3sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。


```python
class Solution:
    def threeSum(self, nums):
        res = []
        nums = sorted(nums)  # 排序
        for i in range(len(nums)-1):
            if i>0 and nums[i]==nums[i-1]:  # 排除第一个数的重复
                continue
            head = i+1
            tail = len(nums)-1
            sum = -nums[i]
            while head<tail:
                s = nums[head]+nums[tail]
                if s==sum:
                    res.append([nums[i], nums[head], nums[tail]])
                    head+=1
                    tail-=1
                    while head<tail and nums[head]==nums[head-1]: head+=1
                    while head<tail and nums[tail]==nums[tail+1]: tail-=1
                elif s<sum:
                    head+=1
                    while head<tail and nums[head]==nums[head-1]: head+=1
                else:
                    tail-=1
                    while head<tail and nums[tail]==nums[tail+1]: tail-=1
                        
        return res 

nums = [1,2,-2,-1] #[-2,0,0,2,2] #[-1,0,1,2,-1,-4]
Solution().threeSum(nums)
```




    []



分析：
- 算法采用 **排序+双指针**
- 首先固定第一个数，转换为 “两数之和” 问题，用双指针遍历排好序的剩余数组
- 要注意的地方是 **去重**

## 016 最接近的三数之和

给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，使得它们的和与 target 最接近。返回这三个数的和。假定每组输入只存在唯一答案。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/3sum-closest
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。


```python
class Solution:
    def threeSumClosest(self, nums, target):
        nums.sort()  # 排序 
        res = sum(nums[:3])
        dis = abs(target-res)
        for i in range(len(nums)-1):
            if i>0 and nums[i]==nums[i-1]:  # 去重
                continue
            head = i+1
            tail = len(nums)-1
            while head<tail:
                s = nums[i]+nums[head]+nums[tail]
                if abs(target-s) < dis:
                    res = s
                    dis = abs(target-s)
                if s < target:
                    head +=1
                elif s > target:
                    tail -=1
                else:
                    return target
        return res
            

nums = [1,1,-1,-1,3]
Solution().threeSumClosest(nums, -1)
```

    0 1 4
    0 1 3





    -1



分析：
- 解法与上题类似：**排序+双指针**，记录遍历以来最近的和
- 本题也要采用去重策略
- 当出现三数之和等于 target, 直接 return target

## 017 电话号码的字母组合

给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。

给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。


```python
class Solution:
    def letterCombinations(self, digits):
        d = {'2': 'abc',
             '3': 'def',
             '4': 'ghi',
             '5': 'jkl',
             '6': 'mno',
             '7': 'pqrs',
             '8': 'tuv',
             '9': 'wxyz'
        }
#         print(d)
        if len(digits)==0:
            return []
        elif len(digits)==1:
            return list(d[digits])
        else:
            l1 = list(d[digits[0]])
            ls = self.letterCombinations(digits[1:])
            return [a+b for a in l1 for b in ls]
        
        

digits = '2345'
Solution().letterCombinations(digits)
```




    ['adgj',
     'adgk',
     'adgl',
     'adhj',
     'adhk',
     'adhl',
     'adij',
     'adik',
     'adil',
     'aegj',
     'aegk',
     'aegl',
     'aehj',
     'aehk',
     'aehl',
     'aeij',
     'aeik',
     'aeil',
     'afgj',
     'afgk',
     'afgl',
     'afhj',
     'afhk',
     'afhl',
     'afij',
     'afik',
     'afil',
     'bdgj',
     'bdgk',
     'bdgl',
     'bdhj',
     'bdhk',
     'bdhl',
     'bdij',
     'bdik',
     'bdil',
     'begj',
     'begk',
     'begl',
     'behj',
     'behk',
     'behl',
     'beij',
     'beik',
     'beil',
     'bfgj',
     'bfgk',
     'bfgl',
     'bfhj',
     'bfhk',
     'bfhl',
     'bfij',
     'bfik',
     'bfil',
     'cdgj',
     'cdgk',
     'cdgl',
     'cdhj',
     'cdhk',
     'cdhl',
     'cdij',
     'cdik',
     'cdil',
     'cegj',
     'cegk',
     'cegl',
     'cehj',
     'cehk',
     'cehl',
     'ceij',
     'ceik',
     'ceil',
     'cfgj',
     'cfgk',
     'cfgl',
     'cfhj',
     'cfhk',
     'cfhl',
     'cfij',
     'cfik',
     'cfil']



分析：
- 采用**递归求解**
- 用递归时，要考虑几个问题：
    - 递推公式
    - 递归出口

## 018 四数之和

给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/4sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。


```python
class Solution:
    def fourSum(self, nums, target):
        res = []
        nums.sort()
        for i in range(len(nums)-2):
            if i>0 and nums[i]==nums[i-1]:
                continue
            sum_3 = target - nums[i]
            for j in range(i+1, len(nums)-1):
                if j>i+1 and nums[j]==nums[j-1]:
                    continue
                sum_2 = sum_3 - nums[j]
                head = j+1
                tail = len(nums)-1
                while head<tail:
#                     print(i,j,head,tail)
                    s = nums[head]+nums[tail]
                    if s<sum_2:
                        head +=1
                    elif s>sum_2:
                        tail-=1
                    else:
                        res.append([nums[i], nums[j], nums[head], nums[tail]])
                        head+=1
                        tail-=1
                        while head<tail and nums[head]==nums[head-1]: head+=1
                        while head<tail and nums[tail]==nums[tail+1]: tail-=1
        return res
        
    

nums = [1, 0, -1, 0, -2, 2]
Solution().fourSum(nums, 2)
```

    0 1 2 5
    0 1 3 5
    0 1 4 5
    0 2 3 5
    0 2 4 5
    1 2 3 5
    1 2 4 5
    2 3 4 5





    [[-1, 0, 1, 2]]



分析：
- 算法主要基于三数之和，只不过又多了一层循环

## 019 删除链表的倒数第N个节点

给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。


```python
# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    def removeNthFromEnd(self, head: ListNode, n: int) -> ListNode:
        temp = head
        p = []
        newhead = head
        while temp is not None:
            p.append(temp)
            temp = temp.next
        if n==1:
            if len(p)==1:
                newhead = None
            else:
                p[-2].next=None
                newhead = head
        elif n==len(p):
            newhead = p[1]
        else:
            p[-n-1].next = p[-n+1]
            newhead = head
        return newhead

class Solution2:
    def removeNthFromEnd(self, head: ListNode, n: int) -> ListNode:
        p1 = p2 = head
        c = 0
        while p1 is not None:
            if c>n:
                p2=p2.next
            p1 = p1.next
            c +=1
#         print(p2.val)
#         print(c)
        if c==n:
            return p2.next
        p2.next = p2.next.next
        return head
        
    
    
def print_ListNode(head):
    temp = head
    res = ''
    while temp is not None:
#         print(temp.val)
        res += str(temp.val)+'->'
        temp = temp.next
    print(res[:-2])

head = ListNode(0)
temp = head
for i in range(1, 1):
    temp.next = ListNode(i)
    temp = temp.next

print_ListNode(head)
head = Solution2().removeNthFromEnd(head, 1)
print_ListNode(head)
```

    0


​    

分析：
- 由于是单向链表，在遍历之前并不知道链表中的元素个数，也无法倒序遍历，要定位倒数第 n 个元素，可以**用一个数组记录所有节点**
- 另一种占用内存更小的方法是用 **快慢指针**，用两个指针，first 和 second，first 比 second 先走 n 步，然后 两者再一同走，当 first 走到链表尾部时，second 刚好走到倒数第 n 个位置

## 020 有效的括号

给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。


```python
class Solution:
    def isValid(self, s: str) -> bool:
        d = {'(': ')', '{': '}', '[': ']'}
        stack = []
        res = True
        for c in s:
            if c in d: 
                stack.append(c)
            else:
                try:
                    top = stack.pop()
                except:
                    res = False
                    break
                if c!=d[top]:
                    res = False
                    break
        return res and len(stack)==0

Solution().isValid('[]()')
```




    True



分析：
- 使用的数据结构：**栈**
- 算法过程：从头扫描字符，出现左半边字符，就将其入栈，否则将栈顶字符出栈，比较和当前字符是否成对，成对继续，否则 return False；最后，如果栈中为空 return True

## 021 合并两个有序链表

将两个有序链表合并为一个新的有序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。


```python
# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


def print_ListNode(head):
    temp = head
    res = ''
    while temp is not None:
#         print(temp.val)
        res += str(temp.val)+'->'
        temp = temp.next
    print(res[:-2])         

# in-place 插队
class Solution:
    def mergeTwoLists(self, l1: ListNode, l2: ListNode):
        if l1 is None:
            return l2
        if l2 is None:
            return l1
        if l1.val>l2.val:
            return self.mergeTwoLists(l2, l1)
        t1,t2=l1,l2   
        while t2 is not None and t1 is not None:
#             print(t1.val,t2.val)
            while t2.val>t1.val:
                if t1.next is None or t2.val<=t1.next.val: break
                t1 = t1.next
#                 print(t1.val,t2.val)
#             print('---')
            temp = t2.next
            t2.next = t1.next
            t1.next = t2
            t2 = temp
            t1 = t1.next
    
        return l1
    
# out-place
class Solution2:
    def mergeTwoLists(self, l1: ListNode, l2: ListNode):
        dummy = ListNode(0)
        curr = dummy
        while l1 is not None and l2 is not None:
            if l1.val<l2.val:
                curr.next = ListNode(l1.val)
                curr = curr.next
                l1 = l1.next
            else:
                curr.next = ListNode(l2.val)
                curr = curr.next
                l2 = l2.next
        while l1 is not None:
            curr.next = ListNode(l1.val)
            curr = curr.next
            l1 = l1.next
        while l2 is not None:
            curr.next = ListNode(l2.val)
            curr = curr.next
            l2 = l2.next
        return dummy.next

# 递归解法：递归函数功能：返回排好序的链表的头结点    
class Solution3:
    def mergeTwoLists(self, l1: ListNode, l2: ListNode):
        if l1 is None:
            return l2
        if l2 is None:
            return l1
        if l1.val < l2.val:
            curr = ListNode(l1.val)
            curr.next = self.mergeTwoLists(l1.next, l2)  # 子问题分解，调用自身
        else:
            curr = ListNode(l2.val)
            curr.next = self.mergeTwoLists(l1, l2.next)  # 子问题分解，调用自身
        return curr
    
l1 = ListNode(0)
v1 = [1,3,6,8]
temp=l1
for i in v1:
    temp.next=ListNode(i)
    temp = temp.next

l2 = ListNode(0)
v2 =[2, 5,7]
temp=l2
for i in v2:
    temp.next=ListNode(i)
    temp = temp.next

    
print_ListNode(l1.next)
print_ListNode(l2.next)

l = Solution3().mergeTwoLists(l2.next, l1.next)
print_ListNode(l)
```

    1->3->6->8
    2->5->7
    1->2->3->5->6->7->8


分析：
- 采用双指针，插队的思想
- 也可以用递归实现
- 上面实现采用 in-place 操作，直接修改原来的链表；另一种是 out-place 操作，返回一个新的链表，这种占用空间大，但是实现起来更简单些

## 022 括号生成

给出 n 代表生成括号的对数，请你写出一个函数，使其能够生成所有可能的并且有效的括号组合。


```python
class Solution(object):
    def generateParenthesis(self, N):
        ans = []
        def backtrack(S = '', left = 0, right = 0):
            if len(S) == 2 * N:
                ans.append(S)
                return
            // 做选择    
            if left < N:
                backtrack(S+'(', left+1, right)
            if right < left:
                backtrack(S+')', left, right+1)

        backtrack()
        return ans

# 作者：LeetCode
# 链接：https://leetcode-cn.com/problems/generate-parentheses/solution/gua-hao-sheng-cheng-by-leetcode/
# 来源：力扣（LeetCode）
# 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

Solution().generateParenthesis(3)
```




    ['((()))', '(()())', '(())()', '()(())', '()()()']



- 补充：backtracking 解决求解组合问题


```python
def backtracking(s=''):
    if len(s)==N:
        print(s)
        return
    backtracking(s+'A')
    backtracking(s+'B')

N = 3
backtracking()
```

    AAA
    AAB
    ABA
    ABB
    BAA
    BAB
    BBA
    BBB


- **回溯算法（backtracking）** 是一种考虑约束条件的暴力搜索算法（枚举法）


```python
# 非递归版回溯法
class Solution(object):
    def generateParenthesis(self, N):
        nodes = [('', 0, 0)]
        res = []
        while nodes:
            print(nodes)
            n = nodes.pop()
            if n[1] == N:
                res.append(n[0]+')'*(n[1] - n[2]))
                continue
            if n[1] < N:
                nodes.append((n[0]+'(', n[1]+1, n[2]))
            if n[2] < n[1]:
                nodes.append((n[0]+')',n[1], n[2]+1))
        return res

# 作者：bmw
# 链接：https://leetcode-cn.com/problems/generate-parentheses/solution/fei-di-gui-ban-hui-su-chao-duan-dai-ma-by-bmw/
# 来源：力扣（LeetCode）
# 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

Solution().generateParenthesis(3)
```

    [('', 0, 0)]
    [('(', 1, 0)]
    [('((', 2, 0), ('()', 1, 1)]
    [('((', 2, 0), ('()(', 2, 1)]
    [('((', 2, 0), ('()((', 3, 1), ('()()', 2, 2)]
    [('((', 2, 0), ('()((', 3, 1), ('()()(', 3, 2)]
    [('((', 2, 0), ('()((', 3, 1)]
    [('((', 2, 0)]
    [('(((', 3, 0), ('(()', 2, 1)]
    [('(((', 3, 0), ('(()(', 3, 1), ('(())', 2, 2)]
    [('(((', 3, 0), ('(()(', 3, 1), ('(())(', 3, 2)]
    [('(((', 3, 0), ('(()(', 3, 1)]
    [('(((', 3, 0)]





    ['()()()', '()(())', '(())()', '(()())', '((()))']



## 023 合并K个排序链表

合并 k 个排序链表，返回合并后的排序链表。请分析和描述算法的复杂度。


```python
# Definition for singly-linked list.

import heapq 

def print_ListNode(head):
    temp = head
    res = ''
    while temp is not None:
#         print(temp.val)
        res += str(temp.val)+'->'
        temp = temp.next
    print(res[:-2])   

class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

# class Solution:
#     def mergeKLists(self, lists):
#         dummy = curr = ListNode(0)
#         heap = []
#         currs = [i for i in lists]
#         while any(currs):
#             for i, c in enumerate(currs):
#                 if c is not None:
#                     heapq.heappush(heap, c.val)
#                     currs[i] = c.next
#         while len(heap) > 0:
#             curr.next = ListNode(heapq.heappop(heap))
#             curr = curr.next
#         return dummy.next

# 优化版
class Solution:
    def mergeKLists(self, lists):
        dummy = curr = ListNode(0)
        heap = []
        for l in lists:
            if l is not None:
                heapq.heappush(heap, (l.val, id(l), l))  # <--如何使用最小堆保存对象！！！
        while len(heap) > 0:
            val, _, l = heapq.heappop(heap)
            curr.next = ListNode(val)
            curr = curr.next
            l = l.next
            if l is not None:
                heapq.heappush(heap, (l.val, id(l), l))
        return dummy.next
        
        
l1 = ListNode(0)
v1 = [1,3,6,8]
temp=l1
for i in v1:
    temp.next=ListNode(i)
    temp = temp.next

l2 = ListNode(0)
v2 =[2, 5,7]
temp=l2
for i in v2:
    temp.next=ListNode(i)
    temp = temp.next
    
print_ListNode(l1)
print_ListNode(l2)
l = Solution().mergeKLists([l1,l2])
print_ListNode(l)
```

    0->1->3->6->8
    0->2->5->7
    0->0->1->2->3->5->6->7->8


分析：
- 方案一：使用最小堆（优先队列）
- 方案二：使用**分治算法**。分治算法是将原问题分解为若干自相似的子问题，逐步减小问题规模来求解

---

- 分治算法找最大值示例


```python
def div_find(arr):
    def helper(l=0, h=len(arr)):
        c = (l + h) // 2
        if c==l: 
            return arr[l]
        a, b =  helper(l, c), helper(c, h)
        if a < b:
            return b
        else:
            return a
    return helper()
        
div_find([1,2,9,8,0,3])
```




    9



## 024 两两交换链表中的节点

给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。


```python
# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

# 递归实现
class Solution:
    def swapPairs(self, head: ListNode) -> ListNode:
        
        def helper(dummy):
            first = dummy.next
            if first is None:
                return None
            second = first.next
            if second is None:
                return first
            t = second.next
            second.next = first
            first.next = t
            dummy.next = second
            helper(first)
            return dummy.next
        
        dummy = ListNode(0)
        dummy.next = head
        newhead = helper(dummy)
        return newhead

# 递归的优化简化    
class Solution:
    def swapPairs(self, head: ListNode) -> ListNode:
        if head is None or head.next is None:
            return head
        second = head.next
        head.next = self.swapPairs(second.next)
        second.next = head
        return second
```

分析：
- 采用递归算法
- 以上两种递归算法实现，第一种“不彻底、不简洁”，第二种形式更加工整、简洁。
- 用递归要考虑清除几个问题：
    - 递归函数返回什么
    - 每一步递归调用做些什么，如何利用下一次递归返回的结果
    - 终止条件是什么

## 025 K 个一组翻转链表

给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。


```python
def print_ListNode(head):
    temp = head
    res = ''
    while temp is not None:
#         print(temp.val)
        res += str(temp.val)+'->'
        temp = temp.next
    print(res[:-2])   

class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

# 用栈实现
class Solution:
    def reverseKGroup(self, head: ListNode, k: int) -> ListNode:
        stack = []
        curr = head
        dummy = curr2 = ListNode(0)
        
        while curr is not None:
            while len(stack) < k and curr is not None:
                stack.append(curr)
                curr = curr.next
            if len(stack) < k:
                curr2.next = stack[0]
                break
            while len(stack) > 0:
                curr2.next = stack.pop()
                curr2 = curr2.next
            curr2.next = curr
            
        return dummy.next

# 递归实现
class Solution2:
    def reverseKGroup(self, head: ListNode, k: int) -> ListNode:
        if head is None or head.next is None: return head
        count = 0
        cur = head
        while cur is not None and count != k:
            cur = cur.next
            count += 1
        if count == k:
            cur = self.reverseKGroup(cur, k);  # 获取下一组翻转后的头节点
            while count > 0:  # 组内翻转
                temp = head.next
                head.next = cur
                cur = head
                head = temp
                count -= 1
            head = cur
        return head
    
l1 = ListNode(0)
v1 = list(range(1,6))
temp=l1
for i in v1:
    temp.next=ListNode(i)
    temp = temp.next
    
print_ListNode(l1.next)
l2 = Solution2().reverseKGroup(l1.next, 3)
print_ListNode(l2)
```

    1->2->3->4->5
    3->2->1->4->5


分析：
- 方法一：栈
- 方法二：递归
---
实现链表翻转


```python
dummy = cur = ListNode(0)
for i in range(1, 6):
    cur.next = ListNode(i)
    cur = cur.next
    
print_ListNode(dummy.next)

def reverse_linkedlist(head):
    last = None
    cur = head
    while cur is not None:
        temp = cur.next
        cur.next = last
        last = cur
        cur = temp
    return last

l2 = reverse_linkedlist(dummy.next)
print_ListNode(l2)        
```

    1->2->3->4->5
    5->4->3->2->1


## 026  删除排序数组中的重复项

给定一个排序数组，你需要在原地删除重复出现的元素，使得每个元素只出现一次，返回移除后数组的新长度。


```python
class Solution:
    def removeDuplicates(self, nums):
        i = 0
        while True:
            try:
                if nums[i] == nums[i+1]:
                    nums.pop(i+1)
                else:
                    i += 1
            except:
                break
        return i+1
```

分析：
- list.pop() 时间复杂度较高
- 可以采用**快慢指针法**，参考下题

## 027 移除元素

移除数组中值等于 val 的元素


```python
# 普通解法
class Solution:
    def removeElement(self, nums, val):
        i = 0
        while True:
            try:
                if nums[i] == val:
                    nums.pop(i)
                    continue
                i += 1
            except:
                break
        print(nums)
        return len(nums)
    
# 快慢指针

class Solution2:
    def removeElement(self, nums, val):
        i = j = len(nums)-1
        for j in range(len(nums)-1, -1, -1):
            if nums[j] == val:
                nums[j] = nums[i]
                i -= 1
            j -= 1
        return i - j
    
a = [1,2,3,2,4,2]
# Solution().removeElement(a, 4)
n = Solution2().removeElement([], 2)
print(a[:n])
```

    []


分析：
- 采用**快慢指针法**，i 为慢指针，j 为快指针，冲最后往前扫描数组，若 nums[j]==val, 则 nums[j] = nums[i]，即用不同的元素覆盖相同的元素

## 028 实现 strStr()

给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从0开始)。如果不存在，则返回  -1。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/implement-strstr
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。


```python
# 暴力搜索算法
class Solution(object):
    def strStr(self, s, p):
        """
        :type haystack: str
        :type needle: str
        :rtype: int
        """
        if len(p)==0:
            return 0
        for i in range(len(s)-len(p)+1):
            flg = True
            for j in range(len(p)):
#                 print(i,j)
                if s[i+j] == p[j]:
                    continue
                else:
                    flg = False
                    break
            if flg and j == len(p)-1:
                return i
        return -1
            

s = "aabaaabaaac"
p = "aabaaac"

Solution().strStr(s,p)
```




    4



**补充：KMP 算法**

采用暴力匹配算法会出现大量的重复匹配，而 KMP 算法巧妙利用**前缀表**，充分利用模式串自身的特点，减少了不必要的重复匹配。

<img src="kmp_prefix_table更新规则.png" width="500px">


```python
# 求前缀表

p = 'aabaaac'


# 原始版
# def crt_dp(p):
#     dp = [-1]*len(p)
#     if len(p) > 1: dp[1] = 0

#     for i in range(1, len(p)-1):
#         l = dp[i]
#         while l !=-1:
#             if p[i] == p[l]:
#                 dp[i+1] = l + 1
#                 break
#             l = dp[l]
#         if l == -1:
#             dp[i+1] = 0
#     return dp

# 优化版
def crt_dp(p):
    dp = [-1]*len(p)
    if len(p) > 1: dp[1] = 0
    l = 0
    i = 1
    while i < len(p)-1:
        if p[i] == p[l] or l == -1:
            l += 1
            dp[i+1] = l
            i += 1
        else:
            l = dp[l]
    return dp

crt_dp(p)
```




    [-1, 0, 1, 0, 1, 2, 2]




```python
# KMP 算法完整版

class Solution(object):
    
    def crt_dp(self, p):
        dp = [-1]*len(p)
        if len(p) > 1: dp[1] = 0
        l = 0
        i = 1
        while i < len(p)-1:
            if p[i] == p[l] or l == -1:
                l += 1
                dp[i+1] = l
                i += 1
            else:
                l = dp[l]
        return dp
    
    def strStr(self, s, p):
        if len(p)==0:
            return 0
        dp = self.crt_dp(p)
#         print(dp)
        j = i = 0
        while i < len(s) and (len(s)-i >= len(p)-j):
            if j == -1:
                i += 1
                j += 1
                continue
            if s[i] == p[j]:
                i += 1
                j += 1
            else:
                j = dp[j]
#             print(i, j)
            if j == len(p):
                return(i-len(p))
        return -1

    
s = "abaaaaabc"
p = "abdd"

s = "aabaaabaaac"
p = "aabaaac"
# s = ''
# p = ''

Solution().strStr(s, p)
```




    4



## 029 两数相除

给定两个整数，被除数 dividend 和除数 divisor。将两数相除，要求不使用乘法、除法和 mod 运算符。

返回被除数 dividend 除以除数 divisor 得到的商。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/divide-two-integers
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。


```python

# 暴力方法：超时
class Solution(object):
    def divide(self, a, b):
        """
        :type dividend: int
        :type divisor: int
        :rtype: int
        """
        if a == 0:
            return 0
        if a == -2147483648 and b == -1:
            return 2147483647
        if (a > 0 and b > 0) or (a < 0 and b < 0):
            flg = 1
        else:
            flg = -1
            
        a = abs(a)
        b = abs(b)
        c = 0
        a -= b
        while a >= 0:
            c += 1
            a -= b
        if flg > 0:
            return c
        else:
            return -c


# 除数倍增法
class Solution(object):
    def divide(self, a, b):
        """
        :type dividend: int
        :type divisor: int
        :rtype: int
        """
        if a == 0:
            return 0
        if a == -2147483648 and b == -1:
            return 2147483647
        if (a > 0 and b > 0) or (a < 0 and b < 0):
            flg = 1
        else:
            flg = -1
        a = abs(a)
        b = abs(b)
        
        if flg > 0:
            return self.div(a,b)
        else:
            return -self.div(a,b)
        
    def div(self, a, b):
        if a < b:
            return 0
        s = b
        mul = 1
        while s+s <= a:
            s += s
            mul += mul
        return mul + self.div(a-s, b)
        
Solution().divide(8,4)
```




    2



分析：

- 第二种方法采用“除数倍增法”，用除数的 $2^{n}$ 倍分解被除数，以类似滚雪球的思想最大可能减少计算量。
- 时间复杂度：$O(\mathrm{log}(n))$
- 空间复杂度：$O(\mathrm{log}(n))$

## 030 串联所有单词的子串

给定一个字符串 s 和一些长度相同的单词 words。找出 s 中恰好可以由 words 中所有单词串联形成的子串的起始位置。

注意子串要与 words 中的单词完全匹配，中间不能有其他字符，但不需要考虑 words 中单词串联的顺序。


来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/substring-with-concatenation-of-all-words
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。


```python
# 滑动窗口法
class Solution(object):
    def findSubstring(self, s, words):
        """
        :type s: str
        :type words: List[str]
        :rtype: List[int]
        """
        n_words = len(words)
        if n_words == 0 or len(s) == 0:
            return []
        len_word = len(words[0])
        word_dict = {}
        for w in words:
            word_dict[w] = word_dict.get(w,0) +1
#         print(word_dict)
        res = []
        for i in range(len(s)-len_word*n_words+1):
            count_dict = word_dict.copy()
            k = n_words
            j = i
            while k > 0:
                if s[j:j+len_word] not in count_dict or count_dict.get(s[j:j+len_word], 0) < 1:
                    break
                count_dict[s[j:j+len_word]] -= 1
                j += len_word
                k -= 1
            if k == 0:
                res.append(i)
        return res

s = "wordgoodgoodgoodbestword"
words = ["word","good","best","good"]
Solution().findSubstring(s, words)
```




    [8]



分析：

- 基本思想：滑窗扫描，充分利用 “word 长度相等” 这一条件
- 时间复杂度：$O(n^2)$
- 空间复杂度：$O(n)$

## 031 下一个排列

实现获取下一个排列的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。

如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。

必须原地修改，只允许使用额外常数空间。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/next-permutation
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。


```python
class Solution(object):
    def nextPermutation(self, nums):
        """
        :type nums: List[int]
        :rtype: None Do not return anything, modify nums in-place instead.
        """
        for i in range(len(nums)-2, -2, -1):
            if nums[i] < nums[i+1]:
                break
        if i == -1: 
            nums[:] = nums[::-1]
            return 
    
        j = i + 1
        for k in range(len(nums)-1, i, -1):
            if nums[k] > nums[i]:
                j = k
                break
        nums[i], nums[j] = nums[j], nums[i]
        nums[i+1:] = nums[i+1:][::-1]
        print(i,j)

nums = [2,3,1,3,3]
Solution().nextPermutation(nums)
print(nums)
```

    2 4
    [2, 3, 3, 1, 3]


分析：

- 该题是一个找规律的题目

算法：

<img src="https://cdn.mathpix.com/snip/images/Pf0qN9Tdbyv0eB-0pw6yeJusXIinTm9tkwqOMaAHOYc.original.fullsize.png" width="700px">

- 找 j 时 直接从后往前，找到比 $nums[i]$ 大的 break 就行，因为找到 i 之后只有两种情况：

<img src="https://cdn.mathpix.com/snip/images/PRHZ7ma7AwFZGhpTcJk0C9ufTc9s7sRTeRLoGjp9JKE.original.fullsize.png" width="400px">

## 032 最长有效括号

给定一个只包含 '(' 和 ')' 的字符串，找出最长的包含有效括号的子串的长度。


```python
# 0(n^2) 搜索策略，超时
class Solution(object):
    def longestValidParentheses(self, s):
        """
        :type s: str
        :rtype: int
        """
        max_len = 0
        for i in range(len(s)-1):
            stack = 0
            t = i
            for j in range(i, len(s)):
                if s[j] == '(':
                    stack += 1
                else:
                    stack -= 1
                if stack == 0:
                    t = j
                    if j-i+1 > max_len:
                        max_len = j-i+1
                elif stack < 0 or stack > (len(s)-i)//2:
                    break
        return max_len

# O(n) 算法
class Solution(object):
    def longestValidParentheses(self, s):
        """
        :type s: str
        :rtype: int
        """
        stack = []
        res = 0
        start = -1
        for i in range(len(s)):
            if s[i] == '(':
                stack.append(i)
            else:
                if len(stack) == 0:
                    start = i
                else:
                    stack.pop()
                    if len(stack) == 0:
                        res = max(res, i - start)
                    else:
                        res = max(res, i - stack[-1])
        return res
    
s = "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((()())))(())()())((((()())((())))((()))()())))()(()()()(()((()))()()()))()()()(()()((((())()(((()(((())((()))()((()(()))()())))))))))())()())(()()))((()()()()())))((()()((((()()))))(())())()()))))(())()(()))((((((()))(()()()()(())(()((()))(()(())(((()()))(()((((()((((()((((())(())))()(())))()))(()((((((((())()()((())((()())()))))())())()(((((()()(((((())()((()(((()))(()(()))(()(()())))())(()((((()((()(((((()()))((()(()((())()))))(()(()())((()((()((((())))(()())()))()())())()))))(())))(())()((())(()(()))))()())(((()(()(((((((((()(()()())))((()((()())())())(((((()(()))))()))()))))()())()(()(())))(()))))(()))(((()))))())))))(((())((())((((()((()))((())))()))(((()))())()))()()()((()()(()())(()))()()((()())))))())(()())(((())))))())(())()))()())())(()(()((())((()(()((())(()()()(()((()(((()(())()(((())))))()())))))(()((((()(()()))(((())(()))(()()))))(())()((()))()))()()))()((())(()())())())(()))(()()(())()(()((((()())(((())(()()())())(()()))())))(()((())(()()))))(()))((()()((((()())(()()))()())()())))()(()((((())())()(())()))()()(()(()))))))(((()()((()))(()((((()()((())))())())))()())))())))((())()()()))()((()((()))()()())))(())())(()(()(()(()))())()))(())((())()())(((()()(((())(()()))(()())(())))()))(((()()()())))())))(((()))())())())))(((()))()())())())))))()()()()(())))(()())))(()()())))()((((()()()((((()))()())))(()))()))))(()())()))(((((())()((())()))(()())()()()())()(((()(()(())))))(()(((()()))((((()()))()))(((())(()(()))()(())))()()(()))))()))))()())))()))((((((((()()())((()(()()()(((())())())))()()(())(())))()())()())))((()))((((())()()))(())(((())(()()(((((()()((()()(((()(()()(((())()))))()(()())(()((((()()())(((()))(())((())()))))())))))(()()()())))()))(())((()())()())()()))(())))((()))()()((()())()()))(()()(())()())(())))((()(((())))()))))((((()))((())())())()(())(()))((((((())()()(((((()))()())(((()(()(())()((()())))(((())(()(())))))(()(()(((()))(())((((())))((())((((((((()(((((()(())))((((((())(()((((()(())()()((())())())((((((((()))))(((())()))()()))(())(())()()())(()()((())(()))())(((())(()((())(())(())))))(()(()(()()(((()()()))())(()))(())())()(((()((())((()())()(((((()()(()))))(((())()()))(()(()(()(()((())))))))(())())()))()(()(()))))()()((((())()())(((())(()))((()())(()((())()()(())((((())))))(())())())(())(()()(()()))(((()((((())(((())))))(()()()()(((()((((())(()))((())()))()(((((((()(()())))((()()(()()((())()))()(())))((()()((((()()()))((())()))((())(((()(()()()(((()((())((())()())())))((()))))))))))(())()()(((()()())))(((()))(()))))(((()(()())(()))(())((()))(((()(()()(((((((()())((((()))((((()(()())())()(((()(()((()))))))))))()()(((()()((((((((((())))))((((())())((()(((()())()))()()(((((())(()())())(((()((())((((((())(((())(((()(()(((((((()(())()())(()))))(()(((()))))))()))(((())))(()(()())()))(()()(()(()((()())()(())((()()((()()()(()(()()))(((((())()(()())()((()())()))(((((()((())()((()((((()(((())())(()()(())()(())(()(())))))(()())((()((()()()())(()))(()))))))(()((())(())((())()())()()))(()((()))(()()))()())(())(()()(()))((())()((())((((((())()(()()(((((())(()())())())()()(()())))))()))()((())((((((()())((()))))))((()(()()(((((((())))))))((()))(())(((()(()(())()()()()(()(())()))))))())()))()(((((()(())(((()))((()))()))()()(()(()((())(()))))()())((()())))))))(()()(()()))()((()(())()((())(()()))())((()())())()()))))((((()()()))())(())()())))()))()))))()))((()(()())()))()))(((()()()()())))())()))((()()())((()())))(((()((()()())(())))()(())(()(()(())(()(((((()()()(((())()())(()((()())(()(((()(())((((()())()(())))(((((((()))))())())))(()))()()(((()())(()))()())(())()))()((())()((())((()((())()())(()()))(((((()()()((((((((()(()((()()((((((()())))((((((())))())(()(()((((()(()())())()()))()((())())(()((((()(((()())((())))))(()())(()()()(()))()())()()))((()((()())(())()()()((())()()))))())()))())))(()))(()))()))((())()((()((()))))))())(((()))))))()(((()((())))((()())())()))((()(()(()(()))((()()))())))(()())))())(()))(())(())))))()(())(()()))()))((())))(()))(()))))(())()())(()(()))())(()(())(())))(()))())(()())))())(()())((()))()()((()(()()()(((((()((()((())(()())(())))()))))))(((())())))()((((()))()((()))())()))()))(()(()((()()())()()(((()))())))))()((((()()))))()))())))()())))(((((()(())))())(((()))((()))(((()(())())()((()(((()))()())))))((((()))()(()((((((()(()()()())(())((()))()(()()))))))()(((())))(())()())))))((()))(())()))))(()(((()()((())(()))))(((((()))))())))()(())(()(()))()))()))(()((())(()((()())()(((()))))())(())()(())))((())(()(((()))(((((()))(()))())))(()((((((())()((((())())()))((())))))())(()(())())))))()()(((())()())))))()))()())))()(())())(())()()()(((())))(())(((()))(()(((()()))())((()))(((()()()()())()()))(()))))()()))))(((()()))))()()(()()))()()()())())()((())(((()())(((())(()((()(((()(()())()()()(()((())(()()(()()()))))))()((()))))()(()))()))(())()()())))()()(((()))((()()(((()())))((()()())((())))))()())()((())))())(()())()()()()((())((()()())((()()))())(())())()(()(((()))())(()))))(()()))(())))))))()())()((()())()()))()())))((()()(()())()(()))((())()))(((())))())))(((()()())())("
Solution().longestValidParentheses(s)
```




    2684



分析：

- 第二种方法充分利用 stack 数据结构，比较巧妙
- 也可以用动态规划求解

<img src="https://cdn.mathpix.com/snip/images/lV6AOksNr1wlLu5kvf-Kd-gfMmD1RWziNpOMT00cwoA.original.fullsize.png" width="650px">

## 033 搜索旋转排序数组

假设按照升序排序的数组在预先未知的某个点上进行了旋转。

( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。

搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回 -1 。

你可以假设数组中不存在重复的元素。

你的算法时间复杂度必须是 O(log n) 级别。


```python
class Solution(object):
    def search(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        if len(nums)==0:
            return -1
        left, right = 0, len(nums)-1
        while left + 1 < right:  # 这里不是 left<=right 是因为有一种情况 [3,1], 1, 提前退出另作判断
            mid = (right-left)//2 + left  # 或者 mid = (right + left) // 2
            print(left, right, mid)
            if nums[mid] == target:
                return mid
            if nums[left] < nums[mid]:
                if nums[left]<=target<=nums[mid]:
                    right = mid-1
                else:
                    left = mid+1
            else:
                if nums[mid]<=target<=nums[right]:
                    left = mid+1
                else:
                    right = mid-1
        if nums[left] == target:
            return left
        elif nums[right] == target:
            return right
        else:
            return -1

nums = [3,1]
Solution().search(nums, 1)
```




    1



分析：

- 本题用二分法查找，但是不同的是要增加许多判断条件，先判断出某一个半段是否单调，再判断 target 可能存在哪一个区间

## 34 在排序数组中查找元素的第一个和最后一个位置

给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。

你的算法时间复杂度必须是 O(log n) 级别。

如果数组中不存在目标值，返回 [-1, -1]。


```python
def find_left(nums, target):
    left, right = 0, len(nums)
    while left < right:
        mid = (right-left)//2+left
#         print(left,mid,right)
        if nums[mid]==target:
            right = mid
        elif nums[mid]<target:
            left = mid + 1
        elif nums[mid]>target:
            right = mid
    if left<len(nums) and nums[left]==target:  # left<len(nums) 用于防特例 [2,2], 3 
        return left
    else:
        return -1

def find_right(nums, target):
    left, right = 0, len(nums)
    while left < right:
        mid = (right-left)//2+left
#         print(left,mid,right)
        if nums[mid]==target:
            left = mid + 1
        elif nums[mid]<target:
            left = mid +1
        elif nums[mid]>target:
            right = mid
    if nums[left-1]==target:
        return left-1
    else:
        return -1


class Solution(object):
    def searchRange(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        if len(nums)==0:
            return [-1,-1]
        else:
            l = find_left(nums,target)
            r = find_right(nums, target)
            return [l,r]
        

nums = [2,2]
Solution().searchRange(nums, 3)
```




    [-1, -1]



分析：

再看**二分法查找**

二分法查找虽然思路简单，但是，实现过程中许多细节值得注意。**思路很简单，细节是魔鬼！**

根据题目要求，二分法查找分为以下几种情形：

- 普通二分法。在有序数组中看是否存在 target, 如果存在某个返回索引（如果存在多个 target, 返回其中之一即可），否则，返回 -1
- 左边界二分查找。如果存在多个 target，要求返回**最左侧边界索引**
- 右边界二分查找。如果存在多个 target，要求返回**最右侧边界索引**

实现细节注意的地方：

- 搜索区间是否包含右边界
- 循环终止条件 有没有 “=” 号
- `mid = (left+right) // 2` 为防止加法溢出，替换为 `mid = (right-left)//2 + left`
- 更新区间时 `left = mid` or `left = mid +1`
- 退出循环，边界条件判断

参考：

>https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/solution/er-fen-cha-zhao-suan-fa-xi-jie-xiang-jie-by-labula/

## 35  搜索插入位置

给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

你可以假设数组中无重复元素。



```python
class Solution(object):
    def searchInsert(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        if len(nums)==0:
            return 0
        left, right = 0, len(nums)-1
        while left<right:
            mid = (right-left)//2+left
            if nums[mid] == target:
                return mid
            elif nums[mid]<target:
                left = mid + 1
            elif nums[mid]>target:
                right = mid - 1
            print(left, mid, right)
        if nums[left]<target:
            return left+1
        elif nums[left]>=target:
            return left

nums = [0,1,2,4,5]
Solution().searchInsert(nums, 3)
```

    3 2 4
    3 3 2





    3



## 36 有效的数独

判断一个 9x9 的数独是否有效。只需要根据以下规则，验证已经填入的数字是否有效即可。


```python
class Solution(object):
    def isValidSudoku(self, board):
        """
        :type board: List[List[str]]
        :rtype: bool
        """
        for i in range(len(board)):
            row_set = set()
            col_set = set()
            cube_set = set()
            for j in range(len(board)):
                if board[i][j]!='.':
                    if board[i][j] in row_set: 
                        return False
                    else:
                        row_set.add(board[i][j])
                if board[j][i]!='.':
                    if board[j][i] in col_set: 
                        return False
                    else:
                        col_set.add(board[j][i])
                row_idx = 3*(i//3)
                col_idx = 3*(i%3)
                if board[row_idx+j//3][col_idx+j%3]!='.':
                    if board[row_idx+j//3][col_idx+j%3] in cube_set:
                        return False
                    else:
                        cube_set.add(board[row_idx+j//3][col_idx+j%3])
        return True

        
s = [
  ["5","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]

Solution().isValidSudoku(s)
```




    True



分析：

- 以上实现方式比较巧妙：在同一个循环中遍历行、列、和分块。特别是分开索引的计算十分巧妙，i=0 遍历第一个分块，i=2 遍历第二个分块，...
- 数据结构 hashset
- 时间复杂度：$O(n^2)$
- 空间复杂度：$O(n)$

以下算法是不在一个循环中遍历某个分块，牺牲空间复杂度，但是更容易理解


```python
class Solution(object):
    def isValidSudoku(self, board):
        """
        :type board: List[List[str]]
        :rtype: bool
        """
        cube = [[set() for j in range(3)] for i in range(3)]
        for i in range(len(board)):
            row_set = set()
            col_set = set()
            for j in range(len(board)):
                if board[i][j]!='.':
                    if board[i][j] in row_set: 
                        return False
                    else:
                        row_set.add(board[i][j])
                        
                    row_idx = i//3
                    col_idx = j//3
                    if board[i][j] in cube[row_idx][col_idx]:
                        return False
                    else:
                        cube[row_idx][col_idx].add(board[i][j])
                    
                if board[j][i]!='.':
                    if board[j][i] in col_set: 
                        return False
                    else:
                        col_set.add(board[j][i])
                
        return True

s = [
  ["5","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]

Solution().isValidSudoku(s)
```




    True



## 37 解数独

编写一个程序，通过已填充的空格来解决数独问题。


```python
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
   //freopen("playground/data.in", "r", stdin);
   
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
```




    [['5', '3', '4', '6', '7', '8', '9', '1', '2'],
     ['6', '7', '2', '1', '9', '5', '3', '4', '8'],
     ['1', '9', '8', '3', '4', '2', '5', '6', '7'],
     ['8', '5', '9', '7', '6', '1', '4', '2', '3'],
     ['4', '2', '6', '8', '5', '3', '7', '9', '1'],
     ['7', '1', '3', '9', '2', '4', '8', '5', '6'],
     ['9', '6', '1', '5', '3', '7', '2', '8', '4'],
     ['2', '8', '7', '4', '1', '9', '6', '3', '5'],
     ['3', '4', '5', '2', '8', '6', '1', '7', '9']]



分析：

- 算法：backtracking, 采用 DFS 搜索策略
- backtracking 常用于求解搜索遍历问题，常用递归来实现。比如括号生成求解所有合法的字符串，该题求某个可行解。
- 通过剪枝可以对算法进行优化

## 38 报数

报数序列是一个整数序列，按照其中的整数的顺序进行报数，得到下一个数。其前五项如下：

1.     1
2.     11
3.     21
4.     1211
5.     111221



```python
class Solution(object):
    def countAndSay(self, n):
        """
        :type n: int
        :rtype: str
        """
        s = '1'
        for i in range(1, n):
            c = s[0]
            count = 0
            s1 = ''
            for j in range(len(s)):
                if c==s[j]:
                    count +=1
                else:
                    s1 += "{}{}".format(count, c)
                    count = 1
                    c = s[j]
            s1 += "{}{}".format(count, c)
            s = s1
        return s
            
Solution().countAndSay(10)
```




    '13211311123113112211'



## 39 组合总和

给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的数字可以无限制重复被选取

说明：

- 所有数字（包括 target）都是正整数。
- 解集不能包含重复的组合。


```python
def helper(res, candidates, target, path, i):
    if target==0:
        res.append(path)
        return
    elif target<0:
        return 
    for j in range(i, len(candidates)):
        helper(res, candidates, target-candidates[j], path+[candidates[j]], j)

class Solution(object):
    def combinationSum(self, candidates, target):
        """
        :type candidates: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        res = []
        helper(res, candidates, target, [], 0)  # 入口调用
        return res

candidates = [2,3,6,7]
target = 7
res = Solution().combinationSum(candidates, target)
res
```




    [[2, 2, 3], [7]]



分析：

- 采用 backtracking 分治搜索
- 时间复杂度：$O(2^n)$
- 空间复杂度：$O(n)$

## 40 组合总和 II

给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的每个数字在每个组合中只能使用一次。

说明：

- 所有数字（包括目标数）都是正整数。
- 解集不能包含重复的组合。


```python
def helper(res, candidates, target, path, i):
    if target==0:
        res.append(path)
    elif target<0:
        return
    for j in range(i,len(candidates)):
        if j!=i and candidates[j]==candidates[j-1]: continue  # 去重！！！注意  j!=i , 比如 [1, 1, 2,...] 两个 1，要求上下级节点连续出现 1 保留，而同级节点出现 1 时，第二个要去重
        helper(res, candidates, target-candidates[j], path+[candidates[j]], j+1)  # 注意是 j+1

class Solution(object):
    def combinationSum2(self, candidates, target):
        """
        :type candidates: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        if len(candidates)==0:
            return []
        res = []
        candidates.sort()
        helper(res, candidates, target, [], 0)
        return res
    
candidates = [10,1,2,7,6,1,5]
target = 8
# candidates=[2,5,2,1,2]
# target = 5
res = Solution().combinationSum2(candidates, target)
res
```




    [[1, 1, 6], [1, 2, 5], [1, 7], [2, 6]]



分析：

- 思路与上题类似，但是，要注意数组可以出现重复元素，且组合中每个数只能用一次。
- 去重
    - 先排序
    - 去重注意：比如 $[1, 1, 2,...]$ 存在两个 1，要求上下级节点连续出现 1 保留，而同级节点出现 1 时，第二个要去重

## 41 缺失的第一个整数

给定一个未排序的整数数组，找出其中没有出现的最小的正整数。

你的算法的时间复杂度应为O(n)，并且只能使用常数级别的空间。


```python
# 带限制条件的桶排序的方法
class Solution(object):
    def firstMissingPositive(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums)==0: return 1
        for i in range(len(nums)):
            while nums[i]>0 and nums[i]<=len(nums) and nums[nums[i]-1]!=nums[i]:
                temp = nums[nums[i]-1]
                nums[nums[i]-1] = nums[i]
                nums[i] = temp
#                 print(nums)
            
        for i in range(len(nums)):
            if nums[i]!=i+1:
                return i+1
        return len(nums)+1
        

nums =  [1,2,0]
nums = [3,4,-1,1]
# nums = [7,8,9,11,12]
nums = [1]
Solution().firstMissingPositive(nums)
```




    2



分析：

- 桶排序的思想：遍历一次数组把大于等于 1 的和小于数组大小的值放到原数组对应位置，然后再遍历一次数组查当前下标是否和值对应，如果不对应那这个下标就是答案，否则遍历完都没出现那么答案就是数组长度加 1
- 举个例子 $nums = [4,5,-1,3,1]$

<center><img src="https://github.com/Daibingh/MyTempFile/blob/master/a0f5aaeda38347219886875a646a957b.png?raw=true" width="400px"></center>

## 42 接雨水

给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。


```python
# 双指针法
class Solution(object):
    def trap(self, height):
        """
        :type height: List[int]
        :rtype: int
        """
        left = 0
        right = len(height)-1
        leftMax = rightMax = 0
        res = 0
        while left <= right:
            if leftMax < rightMax:
                leftMax = max(leftMax, height[left])
                res += leftMax - height[left]
                left += 1
            else:
                rightMax = max(rightMax, height[right])
                res += rightMax - height[right]
                right -= 1
        return res
    
height = [0,1,0,2,1,0,1,3,2,1,2,1]
Solution().trap(height)
```




    6



分析：

- 此题最关键的一点是发现**每个柱子接到的雨水等于这个柱子左右两边最大值中较小者减去柱子本身的高度**，如果采用单指针，从左到右遍历，左侧最大值好确定，但是另一侧无法确定，因此，采用双指针，左右同时遍历

## 43 字符串相乘

给定两个以字符串形式表示的非负整数 num1 和 num2，返回 num1 和 num2 的乘积，它们的乘积也表示为字符串形式。
    
说明：
- num1 和 num2 的长度小于110。
- num1 和 num2 只包含数字 0-9。
- num1 和 num2 均不以零开头，除非是数字 0 本身。

不能使用任何标准库的大数类型（比如 BigInteger）或直接将输入转换为整数来处理。


```python
def char2int(c):
    return ord(c)-ord('0')

class Solution(object):
    def multiply(self, num1, num2):
        """
        :type num1: str
        :type num2: str
        :rtype: str
        """
        res = [0]*( len(num1)+len(num2) )
        for i in range(len(num1)-1, -1, -1):
            for j in range(len(num2)-1, -1, -1):
                prod = char2int(num1[i]) * char2int(num2[j])
                p1, p2 = i+j, i+j+1
                sum = res[p2] + prod
                res[p2] = sum % 10
                res[p1] += sum // 10  # 此时不用着急考虑该位的进位！
#                 print(res)   
        res_str = ''
        for i in range(len(res)):  # 排除前面的 '0'
            if res[i]==0 and len(res_str)==0: continue
            res_str += chr(res[i]+ord('0'))
        return res_str if len(res_str)>0 else '0'
        

num1 = "10"
num2 = "10"
Solution().multiply(num1, num2)
```




    '100'



- 分析机理，找规律，关键在于
    - 确定结果的位数
    - 确定 i 位 和 j 位 相乘之后结果的位置

<center><img src="https://github.com/Daibingh/MyTempFile/blob/master/leetcode_43_81966e6323704759a92b2039c5b399a8.png?raw=true" width="500px"></center>

## 44 通配符匹配

给定一个字符串 (s) 和一个字符模式 (p) ，实现一个支持 '?' 和 '*' 的通配符匹配。

'?' 可以匹配任何单个字符。
'*' 可以匹配任意字符串（包括空字符串）。


```python
class Solution(object):
    def isMatch(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """
        dp = [[False]*(len(p)+1) for _ in range(len(s)+1)]
        dp[0][0] = True  # 边界条件
        for i in range(len(p)):  # 边界条件：ab 与 **ab 单独处理
            if p[i] == '*':
                dp[0][i+1] = True
            else:
                break
        for i in range(len(s)):
            for j in range(len(p)):
                if p[j]!='*':
                    dp[i+1][j+1] = dp[i][j] and (p[j]==s[i] or p[j]=='?')
                else:
                    dp[i+1][j+1] = dp[i][j+1] or dp[i+1][j]
        return dp[-1][-1]

s = "acdcb"
p = "a*c?b"
# s = "adceb"
# p = "*a*b"
Solution().isMatch(s, p)
```




    False



分析：

- 动态规划求解
- 另一种解法

<center><img src="https://raw.githubusercontent.com/Daibingh/MyTempFile/master/leetcode_c4e6c41f01ea4fe881a8580f022a000d.png" width="600px"></center>

## 45 跳跃游戏 II


```python
# 贪心算法
class Solution(object):
    def jump(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        count = 0
        index = 0
        while index<len(nums)-1:
            opt_v, opt_c = 0, 0
            for i in range(1,nums[index]+1):
                if index+i>=len(nums)-1:
                    opt_c = i
                    break
                if i+nums[index+i]>opt_v:
                    opt_v = i+nums[index+i]
                    opt_c = i
            index = index+opt_c
            count += 1
        return count
    
# 一种更简洁的写法：只需遍历一遍
class Solution(object):
    def jump(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        end = 0
        maxpos = 0
        count = 0
        for i in range(0, len(nums)-1):
            maxpos = max(maxpos, nums[i]+i)  # 一边往前走，一边更新当前最远能跳到的地方
            if i == end:
                end = maxpos
                count += 1
        return count
        
nums = [2,3,1]
Solution().jump(nums)
```




    1



- 贪婪算法
- 第二种方法时间复杂度 $O(n)$

<center><img src="https://raw.githubusercontent.com/Daibingh/MyTempFile/master/leetcode_ba2fee70e53a4faba5a4df5ef52b5584.png" width="600px"></center>

## 46 全排列

给定一个没有重复数字的序列，返回其所有可能的全排列。


```python
class Solution(object):
    def permute(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        res = []  # 放结果
        def helper(l=[]):
            if len(l) == len(nums):
                res.append(l)  # l 是某一个排列结果
                return
            for t in nums:
                if t not in l:  # 保证数字不重复
                    helper(l+[t])
        helper()
        return res

nums = [1,2,3]
Solution().permute(nums)
```




    [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]



分析：

- 回溯算法（本质上是 n 叉树的遍历或搜索）

## 47 全排列 II

给定一个可包含重复数字的序列，返回所有不重复的全排列。

示例:

输入: [1,1,2]

输出:

[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/permutations-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。


```python
class Solution(object):
    def permuteUnique(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        res = []  # 放结果
        def helper(l=[], temp=[]):
            if len(l) == len(nums):
                res.append(l)  # l 是某一个排列结果
                return
            
            shown = set([])
            for i in range(len(nums)):
                if i not in temp and nums[i] not in shown:
                    helper(l+[nums[i]], temp+[i])
                    shown.add(nums[i])
        helper()
        return res
        
nums = [1,1,2]
Solution().permuteUnique(nums)
```




    [[1, 1, 2], [1, 2, 1], [2, 1, 1]]



分析:

- 回溯法，关键在于
    - 树的深度上不能重用
    - 树的兄弟节点的值不能重复

## 48 旋转图像

给定一个 n × n 的二维矩阵表示一个图像。

将图像顺时针旋转 90 度。

说明：

你必须在原地旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要使用另一个矩阵来旋转图像。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/rotate-image
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。


```python
# 进行两次翻转：转置->左右翻转
class Solution(object):
    def rotate(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: None Do not return anything, modify matrix in-place instead.
        """
        # 转置
        for i in range(len(matrix)-1):
            for j in range(i+1, len(matrix)):
                matrix[i][j],matrix[j][i] = matrix[j][i], matrix[i][j]
        # 左右翻转
        for i in range(len(matrix)):
            for j in range(len(matrix)//2):
                matrix[i][j],matrix[i][len(matrix)-1-j] = matrix[i][len(matrix)-1-j], matrix[i][j]
        
m = [
    [1,2,3],
    [4,5,6],
    [7,8,9]
]
Solution().rotate(m)
m
```




    [[7, 4, 1], [8, 5, 2], [9, 6, 3]]



分析：

- 旋转问题可以转换成若干次“翻转”问题，翻转问题简单在于，它是点到点的交换

## 49 字母异位词分组

给定一个字符串数组，将字母异位词组合在一起。字母异位词指字母相同，但排列不同的字符串。

示例:

输入: ["eat", "tea", "tan", "ate", "nat", "bat"],

输出:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/group-anagrams
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。


```python
import collections
# 法一：使用字典，排序字符串作 key。时间复杂度: O(NKlog(K)), 空间复杂度：O(NK)
class Solution(object):
    def groupAnagrams(self, strs):
        """
        :type strs: List[str]
        :rtype: List[List[str]]
        """
        str_dict = {}
        for s in strs:
            key = tuple(sorted(s))
            if key in str_dict:
                str_dict[key].append(s)
            else:
                str_dict[key]=[s]
        return list(str_dict.values())
                
# 另一种更简单写法
class Solution(object):
    def groupAnagrams(self, strs):
        ans = collections.defaultdict(list)
        for s in strs:
            ans[tuple(sorted(s))].append(s)
        return list(ans.values())


# 法二: 借助桶排序的思想，字符计数作为 key，时间复杂度 O(NK), 空间复杂度：O(NK)
class Solution(object):
    def groupAnagrams(self, strs):
        str_dict = {}
        for s in strs:
            count = [0]*26
            for c in s:
                count[ord(c)-97]+=1
            count = tuple(count)
            if count in str_dict:
                str_dict[count].append(s)
            else:
                str_dict[count] = [s]
        return list(str_dict.values())
strs = ["eat", "tea", "tan", "ate", "nat", "bat"]        
Solution().groupAnagrams(strs)
```




    [['eat', 'tea', 'ate'], ['tan', 'nat'], ['bat']]



分析：

- 分组问题，更定要用字典来作，要考虑的是如何构造 key 以实现最佳快速的映射

## 50 Pow(x, n)

实现 pow(x, n) ，即计算 x 的 n 次幂函数。


```python
class Solution(object):
    def myPow(self, x, n):
        """
        :type x: float
        :type n: int
        :rtype: float
        """
        if n == 0:
            return 1
        elif n < 0:
            return 1/self.myPow(x, -n)
        half = n // 2
        mod = n % 2
        t = self.myPow(x, half)
        if mod == 0:
            return t*t
        else:
            return t*t*x
        

Solution().myPow(2, 0)
```




    1



分析：

- 采用快速幂算法（折半思想），递归实现
- 时间复杂度 $O(logn)$
- 空间复杂度 $O(logn)$
