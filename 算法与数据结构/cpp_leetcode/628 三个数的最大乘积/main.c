#include <stdio.h>

#define M 10000
#define MAX(x,y) (x) > (y) ? (x) : (y)

int maximumProduct(int* nums, int numsSize){
    int max = -M, max2 = -M, max3 = -M;
    int min = M, min2 = M;
    for (int i=0; i<numsSize; ++i) {
        if ( nums[i] > max ) {
            max3 = max2;
            max2 = max;
            max = nums[i];
        }
        else if ( nums[i] > max2 ) {
            max3 = max2;
            max2 = nums[i];
        }
        else if ( nums[i] > max3 ) {
             max3 = nums[i];
        }
        
        if ( nums[i] < min ) {
            min2 = min;
            min = nums[i];
        }
        else if ( nums[i] < min2 ) {
            min2 = nums[i];
        }
    }
    // printf("%d, %d, %d, %d, %d\n", max, max2, max3, min, min2);
    int ret1 =  max*max2*max3;
    int ret2 =  max*min*min2;
    return MAX(ret1, ret2);
}

int main() {
    
}