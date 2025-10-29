#include "list.h"
void test_mylist()
{
    mylist::list<int> lt;
    lt.push_back(1);
    lt.push_back(1);
    lt.push_back(1);
    lt.push_back(1);
    lt.push_back(1);
    
}
int main()
{
    test_mylist();
    return 0;
}