
inline void swap( int * s, int * p ) {
    int t = *s;
    *s = *p;
    *p = t;
}

inline void reverse( int * s, int * p ) {
    while ( s < p ) {
        swap(s++, p--);
    }
}

void nextPermutation(int* nums, int numsSize){
    int i = numsSize - 2;
    for (; i>=0; --i) {
        if ( nums[i] <nums[i+1] ) break;
    }
    if ( i == -1) {
        reverse(nums, nums+numsSize-1);
        return;
    }
    int j = numsSize - 1;
    for (; j>i; --j) {
        if ( nums[j] > nums[i] ) break;
    }
    swap(nums+i, nums+j);
    reverse(nums+i+1, nums+numsSize-1);
}

int main() {
    
}