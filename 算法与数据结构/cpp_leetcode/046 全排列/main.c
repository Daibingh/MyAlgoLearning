/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#define MAX_SIZE 5000


static void dfs(int* nums, 
                int numsSize, 
                int* returnSize, 
                int** returnColumnSizes,
                int** ppRes, 
                int depth, 
                int* tmp
                )
{

    if (depth == numsSize)
    {
        ppRes[*returnSize] = (int*)malloc(numsSize * sizeof(int));
        memcpy(ppRes[*returnSize], tmp, numsSize * sizeof(int));
        (*returnColumnSizes)[*returnSize] = numsSize;
        (*returnSize)++;
    }
    else 
    {
        for (int i = 0; i < numsSize ; ++i)
        {
        	if (nums[i]==-100) continue;
        	int bak = nums[i];
        	nums[i] = -100;
        	tmp[depth++] = bak;
            dfs(nums, numsSize, returnSize, returnColumnSizes, ppRes, depth, tmp);
            --depth;
            nums[i] = bak;
        }
    }

}

int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int** ppRes = (int**)malloc(MAX_SIZE * sizeof(int*));
    *returnSize = 0;
    *returnColumnSizes = (int*)malloc(MAX_SIZE * sizeof(int));
    int * tmp = (int*)malloc(numsSize*sizeof(int));
    dfs(nums, numsSize, returnSize, returnColumnSizes, ppRes, 0, tmp);
    free(tmp);
    return ppRes;
}
