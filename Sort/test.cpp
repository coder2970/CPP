#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>
using namespace std;
int getRandom(vector<int> &nums, int left, int right)
{
    return nums[(rand() % (right - left + 1)) + left];
}
// 快速排序
void quickSort(vector<int> &nums, int l, int r)
{
    if (l >= r)
        return;
    int key = getRandom(nums, l, r);
    int left = l - 1, right = r + 1, i = l;
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

int main()
{
    srand(time(NULL));
    vector<int> nums = {10, 5, 2, 6, 1, 8, 7, 3, 9, 4};
    int n = nums.size();
    for (auto e : nums)
        cout << e << " ";
    cout << endl;

    quickSort(nums, 0, n - 1);

    for (auto e : nums)
        cout << e << " ";
    cout << endl;

    return 0;
}