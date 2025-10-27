#include "vector.h"

using namespace std;

int main()
{
    myvector::vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);

    for(const auto& e : v1)
    {
        cout << e <<" ";
    }
    cout << endl;

    for(size_t i = 0;i < v1.size();i++)
    {
        cout << v1[i] <<" ";
    }
    cout <<endl;
    return 0;
}