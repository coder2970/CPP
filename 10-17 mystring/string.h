#pragma once

#include <iostream>
#include <assert.h>
#include <string.h>

using namespace std;
namespace mystring
{
    class string
    {
    public:
        string(const char* ="");
        ~string();

        const char* c_str() const
        {
            return _str;
        }

        void reserve(size_t n);
        void push_back(char ch);
        void append(const char* str);

        string& operator+=(char ch); 
        string& operator+=(const char* str);

        void insert(size_t pos, size_t n,char ch);
        void insert(size_t pos,const char* str);
        //void erase(size_t pos = 0,size_t len = npos);

    private:
        char *_str;    // 指向字符串实际存储的字符数组的指针
        size_t _size;     // 有效字符个数
        size_t _capacity; // 总容量

        const static size_t npos;
    };

    void test_string();
}