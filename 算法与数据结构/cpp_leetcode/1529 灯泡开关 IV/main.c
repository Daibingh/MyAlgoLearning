
/*
房间中有 n 个灯泡，编号从 0 到 n-1 ，自左向右排成一行。最开始的时候，所有的灯泡都是 关 着的。
请你设法使得灯泡的开关状态和 target 描述的状态一致，其中 target[i] 等于 1 第 i 个灯泡是开着的，
等于 0 意味着第 i 个灯是关着的。
有一个开关可以用于翻转灯泡的状态，翻转操作定义如下：
选择当前配置下的任意一个灯泡（下标为 i ）
翻转下标从 i 到 n-1 的每个灯泡
翻转时，如果灯泡的状态为 0 就变为 1，为 1 就变为 0 。
返回达成 target 描述的状态所需的 最少 翻转次数。
*/


// 本题是一个找规律的题，直接从前到后扫描，遇到不一致就开始翻转，再接着扫描
// 因为只有两个状态，所以不用实际翻转，根据当前翻转的次数的“奇偶”进行判断
int minFlips(char * target){
    int n = strlen(target);
    int cnt = 0;
    for (int i=0;i<n;++i) {
        if ((cnt & 1)==0 && target[i]!='0' || (cnt & 1) && target[i]=='0' )
            ++cnt;
    }
    return cnt;
}


// 解法二：相邻比较，不相同计数
int minFlips2(char * target){
    int ret = target[0] - '0';
    int len = strlen(target);
    for (int i = 1; i < len; i++)
        if (target[i] != target[i - 1])  // 相邻比较
            ret++;
    return ret;
}