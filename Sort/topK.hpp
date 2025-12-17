#include <iostream>
#include <time.h>

void createData()
{
    int n = 100000;
    srand(time(0));
    const char *file = "data.txt";
    FILE *fp = fopen(file, "w");
    if (fp == nullptr)
    {
        std::cerr << "fopen err" << std::endl;
        exit(1);
    }
    for (int i = 0; i < n; i++)
    {
        int x = (rand() + i) % 100000;
        fprintf(fp, "%d\n", x);
    }
    fclose(fp);
}
void adjustDown(int *arr, int size, int parent)
{
    int child = parent * 2 + 1;
    while (child < size)
    {
        if (child + 1 < size && arr[child] > arr[child + 1])
            child++;
        if (arr[child] < arr[parent])
        {
            std::swap(arr[child], arr[parent]);
            parent = child;
            child = parent * 2 + 1;
        }
        else
        {
            break;
        }
    }
}
// 找最大的前k个数 建小堆
void TopK()
{
    int k;
    std::cout << "cin" << std::endl;
    std::cin >> k;

    // 读取前k个数据建堆
    const char *file = "data.txt";
    FILE *fp = fopen(file, "r");
    if (fp == nullptr)
    {
        std::cerr << "fopen" << std::endl;
        exit(2);
    }

    int *minHeap = new int[k];
    for (int i = 0; i < k; i++)
        fscanf(fp, "%d ", &minHeap[i]);
    // 向下调整建堆
    for (int i = (k - 1 - 1) / 2; i >= 0; i--)
        adjustDown(minHeap, k, i);
    // 继续遍历剩下的数据,和堆顶进行比较,谁大谁入堆
    // 继续调整堆
    int x;
    while (fscanf(fp, "%d ", &x) != EOF)
    {
        if (minHeap[0] < x)
        {
            minHeap[0] = x;
            adjustDown(minHeap, k, 0);
        }
    }
    fclose(fp);

    for (int i = 0; i < k; i++)
    {
        std::cout << minHeap[i] << std::endl;
    }
}