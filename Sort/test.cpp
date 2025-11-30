#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>

using namespace std;
// 快速排序
int getRandom(vector<int> &nums, int left, int right)
{
    return nums[(rand() % (right - left + 1)) + left];
}

void quickSort(vector<int> &nums, int l, int r)
{
    if (l >= r)
        return;
    int key = getRandom(nums, l, r);
    int left = l - 1, right = r + 1, i = l; // 注意i不能从0开始，应该从传入区间的端点处开始
    while (i < right)
    {
        if (key > nums[i])
            swap(nums[i++], nums[++left]);
        else if (key == nums[i])
            i++;
        else
            swap(nums[i], nums[--right]);

        quickSort(nums, l, left);
        quickSort(nums, right, r);
    }
}

// 归并排序
void mergeSort(vector<int> &nums, int left, int right)
{
    if (left >= right)
        return;
    // 1.取数组中点
    int middle = (left + right) >> 1;
    // 2.排序左右两边
    // [left, middle] [middle + 1, right]
    mergeSort(nums, left, middle);
    mergeSort(nums, middle + 1, right);
    // 3.合并有序数组
    vector<int> tmp(right - left + 1);
    int cur1 = left, cur2 = middle + 1, i = 0;
    while (cur1 <= middle && cur2 <= right)
        tmp[i++] = nums[cur1] < nums[cur2] ? nums[cur1++] : nums[cur2++];
    while (cur1 <= middle)
        tmp[i++] = nums[cur1++];
    while (cur2 <= right)
        tmp[i++] = nums[cur2++];
    // 4.还原
    for (int k = left; k <= right; k++)
        nums[k] = tmp[k - left];
}

int main()
{
    srand(time(NULL));
    vector<int> nums = {10, 5, 2, 6, 1, 8, 7, 3, 9, 4};
    int n = nums.size();
    for (auto e : nums)
        cout << e << " ";
    cout << endl;

    // quickSort(nums, 0, n - 1);
    mergeSort(nums, 0, n - 1);

    for (auto e : nums)
        cout << e << " ";
    cout << endl;

    return 0;
}