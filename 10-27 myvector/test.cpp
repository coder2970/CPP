#include "vector.h"

using namespace std;

void func(const myvector::vector<int>& v)
{
    // const_iterator
    myvector::vector<int>::const_iterator it = v.begin();
    while(it != v.end())
    {
        cout<< *it ;
        it++;
    }
    cout<<endl;
}
int main()
{
    myvector::vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    // v1.push_back(20);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    // v1.push_back(50);

    // for(const auto& e : v1)
    // {
    //     cout << e <<" ";
    // }
    // cout << endl;
    // v1.pop_back();
    // v1.pop_back();
    // v1.pop_back();
    // v1.pop_back();
    // v1.pop_back();
    // v1.pop_back();
    
    // v1.insert(v1.begin(),10);
    // v1.insert(v1.begin() + 2,20);
    // v1.insert(v1.begin() + 2,30);

    // v1.erase(v1.begin()+2);
    // 删除偶数的正确写法 给erase返回值 记录每次删除后pos指向的位置
    // auto it = v1.begin();
    // while(it != v1.end())
    // {
    //     if(*it % 2 == 0)
    //     {
    //         it = v1.erase(it);
    //     }
    //     else{
    //         it++;
    //     }
    // }
    for(size_t i = 0;i < v1.size();i++)
    {
        cout << v1[i] <<" ";
    }
    cout <<endl;

    // myvector::vector<int> v2(v1);
    // myvector::vector<int> v3;
    // v3.resize(10,1);
    // for(size_t i = 0;i < v3.size();i++)
    // {
    //     cout << v3[i] <<" ";
    // }
    // cout <<endl;
    // for(size_t i = 0;i < v2.size();i++)
    // {
    //     cout << v2[i] <<" ";
    // }
    // cout <<endl;
    // v3 = v1;
    // for(size_t i = 0;i < v3.size();i++)
    // {
    //     cout << v3[i] <<" ";
    // }
    // cout <<endl;
    // cout << v1._start << " " << v2._start <<endl;
    // func(v1);

    myvector::vector<string> v2;
    v2.push_back("1111111111111111111111111111111111111111111");
    v2.push_back("1111111111111111111111111111111111111111111");
    v2.push_back("1111111111111111111111111111111111111111111");
    v2.push_back("1111111111111111111111111111111111111111111");
    v2.push_back("1111111111111111111111111111111111111111111");
    v2.push_back("1111111111111111111111111111111111111111111");
    for(size_t i = 0;i < v2.size();i++)
    {
        cout << v2[i] <<" ";
    }
    cout <<endl;
    return 0;
}