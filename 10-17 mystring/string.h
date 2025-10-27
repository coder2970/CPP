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
        typedef char* iterator;
        typedef const char* const_iterator;

        iterator begin()
        {
            return _str;
        }

        iterator end()
        {
            return _str + _size;
        }

        const_iterator begin() const
        {
            return _str;
        }

        const_iterator end() const
        {
            return _str + _size;
        }

        string(const char* ="");
        ~string();
        void clear()
        {
            _str[0] = '\0';
            _size = 0;
        }

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
        void erase(size_t pos = 0,size_t len = npos);

        size_t find(char ch,size_t pos = 0);
        size_t find(const char* str,size_t pos = 0);

        size_t size() const
        {
            return _size;
        }

        size_t capacity() const
        {
            return _capacity;
        }

        char& operator[](size_t pos)
        {
            assert(pos < _size);
            return _str[pos];
        }
        const char& operator[](size_t pos) const
        {
            assert(pos < _size);
            return _str[pos];
        }

        string substr(size_t pos,size_t len = npos);

        bool operator==(const string& s) const;
        bool operator!=(const string& s) const;
        bool operator>(const string& s) const;
        bool operator>=(const string& s) const;
        bool operator<(const string& s) const;
        bool operator<=(const string& s) const;

    private:
        char *_str;    // 指向字符串实际存储的字符数组的指针
        size_t _size;     // 有效字符个数
        size_t _capacity; // 总容量

        const static size_t npos;
    };

    ostream& operator<<(ostream& out,const string& s);
    istream& operator>>(istream& in,string& s);
    void test_string();
}