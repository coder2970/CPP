#include "Stack.h"
#include "Queue.h"
#include "priority_queue.h"
#include <iostream>
using namespace std;

void test_stack()
{
    mystack::stack<int> st;
    for (int i = 0; i < 5; ++i)
        st.push(i);

    std::cout << "Popping out elements...";
    while (!st.empty())
    {
        std::cout << ' ' << st.top();
        st.pop();
    }
    std::cout << '\n';
}

void test_queue()
{
    myqueue::queue<int> myqueue;

    myqueue.push(1);
    myqueue.push(2);
    myqueue.push(3);
    myqueue.push(4);
    std::cout << "myqueue contains: ";
    while (!myqueue.empty())
    {
        std::cout << ' ' << myqueue.front();
        myqueue.pop();
    }
    std::cout << '\n';
}

void test_priorityqueue()
{
    // 默认是大的优先级高
    mypriority_queue::priority_queue<int> mypq1;
    mypq1.push(30);
    mypq1.push(100);
    mypq1.push(25);
    mypq1.push(40);
    std::cout << "Popping out elements...";
    while (!mypq1.empty())
    {
        std::cout << ' ' << mypq1.top();
        mypq1.pop();
    }
    std::cout << '\n';
}
int main()
{
    test_priorityqueue();
}