
/*
给你一个由 不同 整数组成的整数数组 arr 和一个整数 k 。
每回合游戏都在数组的前两个元素（即 arr[0] 和 arr[1] ）之间进行。比较 arr[0] 与 arr[1] 的大小，
较大的整数将会取得这一回合的胜利并保留在位置 0 ，较小的整数移至数组的末尾。当一个整数赢得 k 个连续回合时，
游戏结束，该整数就是比赛的 赢家 。
返回赢得比赛的整数。
题目数据 保证 游戏存在赢家。

*/


// 类似双指针
int getWinner(int* arr, int arrSize, int k) {
    int i = 0, j = 1;
    int cnt = 0;
    while (j < arrSize) {
        if (arr[i] > arr[j]) {
            ++cnt;
            ++j;
        }
        else {
            i = j;
            ++j;
            cnt = 1;
        }
        if (cnt == k) return arr[i];
    }
    return arr[i];
}