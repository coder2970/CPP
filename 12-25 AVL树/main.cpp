#include "AVLTree.h"
#include <time.h>
void test()
{
    AVLTree<int, int> t;
    // int a[] = { 16,3,7,11,9,26,18,14,15 };
    //  双旋
    int a[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
    for (auto e : a)
    {
        t.Insert({e, e});
    }
    t.InOrder();
    std::cout << t.isBalance();
}
#include <vector>

void TestAVLTree2()
{
    const int N = 100000;
    std::vector<int> v;
    v.reserve(N);
    srand(time(0));

    for (size_t i = 0; i < N; i++)
    {
        v.push_back(rand() + i);
    }

    size_t begin2 = clock();
    AVLTree<int, int> t;
    for (auto e : v)
    {
        t.Insert(std::make_pair(e, e));
    }
    size_t end2 = clock();

    std::cout << "Insert:" << end2 - begin2 << std::endl;
    std::cout << t.isBalance() << std::endl;

    std::cout << t.Height() << std::endl;
}
int main()
{
    // test();
    TestAVLTree2();
    return 0;
}