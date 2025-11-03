#include "list.h"
#include <iostream>

using namespace std;

struct A
{
    A(int a1 = 1, int a2 = 1)
        : _a1(a1), _a2(a2)
    {
    }

    int _a1;
    int _a2;
};

void test_mylist2()
{
    mylist::list<A> lt2;
    lt2.push_back({1, 1});
    lt2.push_back({2, 2});

    mylist::list<A>::iterator it = lt2.begin();

    while (it != lt2.end())
    {
        cout << it->_a1 << " " << it->_a2 << " ";
        ++it;
    }
    cout << endl;
}

void Print(const mylist::list<int> lt)
{
    mylist::list<int>::const_iterator it = lt.begin();
    while (it != lt.end())
    {
        cout << *it << " ";
        ++it;
    }
    cout << endl;
}

void test_mylist()
{
    mylist::list<int> lt;
    lt.push_back(1);
    lt.push_back(2);
    lt.push_back(3);
    lt.push_back(4);
    lt.push_back(5);
    mylist::list<int>::iterator it = lt.begin();
    while (it != lt.end())
    {
        cout << *it << " ";
        ++it;
    }
    cout << endl;

    for (auto &e : lt)
    {
        cout << e << " ";
    }
    cout << endl;

    Print(lt);
}
void test_mylist3()
{
    mylist::list<int> lt;
    lt.push_back(1);
    lt.push_back(2);
    lt.push_back(3);
    lt.push_front(4);
    lt.push_front(5);
    lt.push_front(6);

    lt.pop_back();
    lt.pop_back();
    lt.pop_front();
    lt.pop_front();

    for (auto &e : lt)
    {
        cout << e << " ";
    }
    cout << endl;
    mylist::list<int> lt2;
    lt2 = lt;
    for (auto &e : lt)
    {
        cout << e << " ";
    }
    cout << endl;
}
int main()
{
    test_mylist3();
    return 0;
}