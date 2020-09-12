#include <bits/stdc++.h>
#include "utils.hpp"
#include <sys/time.h>

using namespace std;

/*
常见排序算法简单实现
*/


class Timer
{
public:
	struct timeval start;
    struct timeval end;
    void tic() {
        gettimeofday(&start, NULL);
    }
	void toc(const string& info) {
		gettimeofday(&end, NULL);
		float time_use = (end.tv_sec-start.tv_sec)*1000. + (end.tv_usec-start.tv_usec)/1000.; // 毫秒
    	printf("%s: time use %.2f ms\n", info.c_str(), time_use);
	}
	
};



void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


/*
1. 选择排序

- 不稳定
- O(n2)
*/

void selectSort(int *begin, int *end) {

    for (; begin<end-1;++begin) {
        for (int *cur=begin+1; cur<end;++cur) {
            if (*cur<*begin) swap(begin, cur);
        }
    }
}

/*
2. 冒泡排序

- 稳定
- O(n2)
- 适用链表 
*/

void bubbleSort(int *begin, int *end) {
    for (;begin<end-1;--end) {
        bool swaped = false;  // 是否交换过
        for (int *cur=begin;cur<end-1;++cur) {
            if (*(cur+1)<*cur) {
                swap(cur, cur+1);
                swaped = true;
            }
        }
        if (!swaped) return;
    }
}

/*
3. 快排

- 不稳定
- O(nlogn)
*/

void quickSort(int *begin, int *end) {
    if (end-begin<=1) return;
    int *L = begin, *R = end-1;
    int val = *R;
    while (L<R)
    {
        while (L<R && *L<val) ++L;
        while (L<R && *R>=val) --R;
        swap(L, R);
    }
    if (*L>val) swap(L, end-1);
    quickSort(begin, L);
    quickSort(L+1, end);
}


/*
4. 插入排序

- 稳定
- O(n2)
- 当元素基本有序时，排序简单高效
*/

void insertSort(int *begin, int *end) {
    for (int *cur=begin+1;cur<end;++cur) {  // cur 是新牌的位置    
        for (int *p=cur-1;p>=begin && *(p+1)<*p;--p) swap(p, p+1);  // 交换的方式插入
    }
}

/*
5. 希尔排序

- 插入排序的改进，对增量序列进行插排，增量缩减至 1
- 时间复杂度与增量序列有关，优于简单排序
- 不稳定
*/


void shellSort(int *begin, int *end) {
    for (int gap=(end-begin)/2; gap>0; gap/=2) {
        for (int * p=begin+gap; p<end; ++p) {  // 里面是个插排，将 "1" 换成 "gap"
            int tmp = *p;
            int * s=p-gap;
            for (; s>=begin && *(s)>tmp; s-=gap ) {
                *(s+gap) = *s;
            }
            *(s+gap) = tmp;
        }
    }
}


// void shellSort(int a[], int n)
// {
// 	for (int gap = n / 2; gap > 0; gap /= 2)
// 		for (int i = gap; i < n; i++)
// 			for (int j = i - gap; j >= 0 && a[j] > a[j + gap]; j -= gap)
// 				swap(&a[j], &a[j + gap]);
// }


/*
6. 堆排序

- 不稳定
- O(nlogn)
- 最大堆在前，有序区在后
*/

void percDown(int * begin, int * end, int* p) {  // 从节点 p 下滤, 堆区范围 [begin, end)
    int * child = 2*(p-begin)+1+begin;  // 左儿子 2*offset+1 (下表从 0 开始)
    int tmp = *p;
    while (child<end)
    {
        if (child < end-1 && *child < *(child+1) ) ++child;
        if (*child <= tmp) break;
        else {
            *p = *child;   // 类似与插入排序，将比我大的向上提
            p = child;
            child = 2*(p-begin)+1+begin;
        }
    }
    *p = tmp;
}

void heapSort(int* begin, int * end) {
    for (int * p=(end-begin)/2+begin; p>=begin; --p) {
        percDown(begin, end, p);
    }
    for (int * cur=end-1; cur>begin; --cur) {  // 堆区在前，有序区在后
        swap(begin, cur);   // 将最大元放在有序区开始位置
        percDown(begin, cur, begin); // 缩减堆区并调整堆区
    }
}


/*
7. 归并排序
- 分治的思想，二分将每个子集排序，然后合并，用到临时数组
- 时间复杂度 O(nlogn), 空间复杂度 O(n)
- 比较次数最少
- 稳定
*/

void merge(int * arr, int * tmpArr, int L, int M, int R) {  // 合并两个有序数组 [L, M] , [M+1, R]

    int l = L, r = M+1, t = L;
    while (l<=M && r<=R) {
        if (arr[l] < arr[r]) tmpArr[t++] = arr[l++];
        else tmpArr[t++] = arr[r++];
    }
    while (l<=M) tmpArr[t++] = arr[l++];  // 处理末尾元素
    while (r<=R) tmpArr[t++] = arr[r++];

    for (t = L; t<=R; ++t) arr[t] = tmpArr[t];  // 拷贝到原始数组
}

void mergeSortHelper(int * arr, int * tmpArr, int L, int R) {  // 递归分割函数
    if (L<R) {
        int M = (L+R)/2;
        mergeSortHelper(arr, tmpArr, L, M);
        mergeSortHelper(arr, tmpArr, M+1, R);
        merge(arr, tmpArr, L, M, R);
    }
}

void mergeSort(int *begin, int *end) {
    int * tmpArr = new int[end-begin];
    mergeSortHelper(begin, tmpArr, 0, end-begin-1);
    delete [] tmpArr;
}


/* 
8. 计数排序

- 也是桶排序的简单情况，直接建立桶的索引和数值的映射，进行计数
*/


void countSort(int * begin, int * end) {
    int minVal = *begin, maxVal = *begin;
    for (int * p=begin; p<end; ++p) {
        if (*p<minVal) minVal = *p;
        else if (*p>maxVal) maxVal = *p;
    }
    int num = maxVal - minVal + 1;
    int * count = new int[num]();  // 计数桶
    for (int * p=begin; p<end; ++p) {
        ++count[*p-minVal];  // 映射到桶序号
    }
    int *p=begin;
    for (int i=0;i<num;++i) {
        while (count[i]) {
            *p++= i+minVal;  // 反映射到值
            --count[i];
        } 
    }
    delete [] count;
}


/*
9. 桶排序

- 构造 hash 函数映射桶的序号，每个桶内部存一个短序列，每个桶内再调用其它排序算法，所以桶要用二维数组

*/

void bucketSort(int * begin, int * end, int bucketWidth=500000) {
    int minVal = *begin, maxVal = *begin;
    for (int * p=begin; p<end; ++p) {
        if (*p<minVal) minVal = *p;
        else if (*p>maxVal) maxVal = *p;
    }
    int len = end-begin;
    int num = (maxVal-minVal)/len + 1;
    int * bucket = new int[num*bucketWidth]();  // 桶
    for (int *p=begin;p<end;++p) {
        int idx = (*p-minVal)/len;  // 映射函数
        bucket[ idx*bucketWidth + bucket[idx*bucketWidth] + 1 ] = *p;
        ++bucket[idx*bucketWidth];
    }
    int * p = begin;
    for (int i=0; i<num; ++i) {
        if (bucket[i*bucketWidth]) {
            int * start = bucket+i*bucketWidth+1;
            quickSort(start, start + bucket[i*bucketWidth]);  // 桶内排序
            for (int j=0;j<bucket[i*bucketWidth];++j) *p++ = bucket[i*bucketWidth+j+1];
        }
    }
    delete [] bucket;
}



/*
10. 基数排序

- 利用桶排序实现，适用于多关键字排序
- 以数字为例，将每一位的数字看作不同的关键字
- 用次位优先 (LSD) 直接分桶，取数若干次就行
- 主位优先 (MSD) 桶内还要排序（和一般桶排序没区别了）
*/


void radixSort(int *begin, int * end, int bucketWidth=500000) {
    int maxVal = *begin;
    for (int * p=begin; p<end; ++p) {
        if (*p>maxVal) maxVal = *p;
    }
    int * bucket = new int[10*bucketWidth];
    for (int m=1; maxVal/m ; m*=10) {
        for (int i=0;i<10;++i) bucket[i*bucketWidth] = 0;
        for (int *p=begin;p<end;++p) {
            int idx = *p / m % 10;
            bucket[ idx*bucketWidth + bucket[idx*bucketWidth]+1 ] = *p;
            ++bucket[idx*bucketWidth];
        }
        int * p = begin;
        for (int i=0;i<10;++i) {
            for (int j=0;j<bucket[i*bucketWidth];++j) *p++ = bucket[i*bucketWidth+j+1];
        }  
    }
    delete [] bucket;
}

const int max_num = 100000;  // 以此参数测试时间
/*
quickSort: time use 6.15 ms
bubbleSort: time use 13485.79 ms
selectSort: time use 5127.75 ms
insertSort: time use 1436.46 ms
heapSort: time use 8.26 ms
mergeSort: time use 7.21 ms
shellSort: time use 8.47 ms
countSort: time use 0.14 ms
radixSort: time use 2.58 ms
bucketSort: time use 9.83 ms */

void genData(int *a, int *b) {
    for (int i=0;i<max_num;++i) {
        a[i] = rand()%1000 + rand()%100;
        b[i] = a[i];
    }
}

void check(int *a, int *b) {
    std::sort(b, b+max_num);
    for (int i=0;i<max_num;++i) {
         assert (a[i]==b[i]);
    }
}

int main() {

    int a[max_num];
    int b[max_num];

    Timer T;

    // T.tic();
    // std::sort(b, b+max_num);  //  time use 3.69 ms
    // T.toc("std::sort");

    genData(a,b);

    T.tic();
    quickSort(a, a+max_num);  // time use 6.08 ms
    T.toc("quickSort");

    check(a,b);
    genData(a,b);

    T.tic();
    bubbleSort(a, a+max_num);  // time use 13099.52 ms
    T.toc("bubbleSort");

    check(a,b);
    genData(a,b);

    T.tic();
    selectSort(a, a+max_num);  // time use 5241.60 ms
    T.toc("selectSort");

    check(a,b);
    genData(a,b);

    T.tic();
    insertSort(a, a+max_num);  // time use 1475.74 ms
    T.toc("insertSort");

    check(a,b);
    genData(a,b);

    T.tic();
    heapSort(a, a+max_num);  //  time use 8.01 ms
    T.toc("heapSort");

    check(a,b);
    genData(a,b);

    T.tic();
    mergeSort(a, a+max_num);  //  time use 6.96 ms
    T.toc("mergeSort");

    check(a,b);
    genData(a,b);

    T.tic();
    shellSort(a, a+max_num);  //  time use 8.10 ms
    T.toc("shellSort");

    check(a,b);
    genData(a,b);

    T.tic();
    countSort(a, a+max_num);  //  time use 0.16 ms
    T.toc("countSort");

    check(a,b);
    genData(a,b);

    T.tic();
    radixSort(a, a+max_num);  // time use 3.31 ms
    T.toc("radixSort");

    check(a,b);
    genData(a,b);

    T.tic();
    bucketSort(a, a+max_num);  // time use 11.86 ms
    T.toc("bucketSort");

    check(a,b);

    // int a[] = {71,14,34,3,85,53,20,25};
    // selectSort(a, a+8);
    // bubbleSort(a, a+8);
    // quickSort(a, a+8);
    // insertSort(a, a+8);
    // shellSort(a, a+8);
    // heapSort(a, a+8);
    // mergeSort(a, a+8);
    // countSort(a, a+8);
    // bucketSort(a, a+8);
    // radixSort(a, a+8);
    // print_arr(a, 8);

    return 0;
}