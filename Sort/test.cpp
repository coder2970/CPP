#include <iostream>
#include "topK.hpp"
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

// 直接插入排序
void insertSort(vector<int> &nums)
{
    for (int i = 0; i < nums.size() - 1; i++)
    {
        int end = i;             // 1.定界：将数组分为前部的有序区和后部的无序区 有序：[0,end] 无序：[end + 1, n]
        int key = nums[end + 1]; // 2.取牌

        while (end >= 0) // 3.挪位：在有序区中从后向前扫描，将比“抓到的牌”大的元素统统向后移动。
        {
            if (key < nums[end])
            {
                nums[end + 1] = nums[end];
                end--;
            }
            else
            {
                break;
            }
        }
        nums[end + 1] = key; // 4.落座：将暂存的元素放入最终找到的空位中
    }
}
void adjustDown(vector<int> &nums, int parent, int heapsize)
{
    int n = heapsize;
    int child = parent * 2 + 1;
    while (child < n)
    {
        if (child + 1 < n && nums[child] < nums[child + 1])
            child = child + 1;
        if (nums[parent] < nums[child])
        {
            std::swap(nums[parent], nums[child]);
            parent = child;
            child = parent * 2 + 1;
        }
        else
        {
            break;
        }
    }
}
// 堆排序 升序 建大堆
void HeapSort(vector<int> &nums)
{
    int n = nums.size();
    for (int i = (n - 1 - 1) / 2; i >= 0; i--)
    {
        adjustDown(nums, i, n);
    }
    int end = n - 1;
    while (end > 0)
    {
        std::swap(nums[end], nums[0]);
        adjustDown(nums, 0, end);
        end--;
    }
}

int main()
{
    // srand(time(NULL));
    vector<int> nums = {10, 5, 2, 6, 1, 8, 7, 3, 9, 4};
    int n = nums.size();
    for (auto e : nums)
        cout << e << " ";
    cout << endl;

    // quickSort(nums, 0, n - 1);
    // mergeSort(nums, 0, n - 1);
    // insertSort(nums);
    HeapSort(nums);

    for (auto e : nums)
        cout << e << " ";
    cout << endl;

    // createData();
    // TopK();

    return 0;
}