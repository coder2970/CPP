#include "string.h"

namespace mystring
{
    const static size_t npos = -1;

    string::string(const char *str)
        : _size(strlen(str))
    {
        _capacity = _size;
        _str = new char[_size + 1];
        strcpy(_str, str);
    }

    string::~string()
    {
        delete[] _str;
        _str = nullptr;
        _size = _capacity = 0;
    }

    // 只扩不缩
    void string::reserve(size_t n)
    {
        if (n > _capacity)
        {
            char *tmp = new char[n + 1];
            strcpy(tmp, _str);
            delete[] _str;
            _str = tmp;
            _capacity = n;
        }
    }

    void string::push_back(char ch)
    {
        // 先判断capacity 二倍扩容
        if (_size + 1 > _capacity)
        {
            reserve(_capacity == 0 ? 4 : 2 * _capacity);
        }

        // 插入
        _str[_size] = ch;
        _size++;
        _str[_size] = '\0';
    }

    void string::append(const char *str)
    {
        size_t len = strlen(str);
        if (_size + len > _capacity)
        {
            // reserve(_capacity == 0 ? 4 : 2*_capacity);  size + len 有可能大于2capacity
            size_t newCapacity = 2 * _capacity;
            if (_size + len > newCapacity)
            {
                newCapacity = _size + len;
            }
            newCapacity += 1; // 预留'\0'

            reserve(newCapacity);
        }

        strcpy(_str + _size, str);
        _size += len;
    }

    string &string::operator+=(char ch)
    {
        push_back(ch);
        return *this;
    }
    string &string::operator+=(const char *str)
    {
        append(str);
        return *this;
    }

    void string::insert(size_t pos, size_t n,char ch)
    {
        assert(pos <= _size);

        // 检查空间容量
        if(_size + n > _capacity)
        {
            size_t newCapacity = _capacity * 2;
            if(_size + n > newCapacity)
            {
                newCapacity = _size + n;
            }
            reserve(newCapacity);
        }

        //插入
        size_t end = _size;
        while(end >= pos)
        {
            _str[end + n] = _str[end];
            -- end;
        }
        for(int i = 0;i < n;i++)
        {
            _str[pos + i] = ch;
        }

        _size += n;
        
    }

    void string::insert(size_t pos,const char* str)
    {
        assert(pos < _size);
    }

    //void string::erase(size_t pos = 0,size_t len = npos)
    //{

    //}

    void test_string()
    {
        string s1("hello world");
        cout << s1.c_str()<<endl;
        string s2;
        cout<<s2.c_str()<<endl;
        // s1+=' ';
        // s1+='1';
        // s1+="hello";
        // cout << s1.c_str()<< endl;

        // s1 += "hello bit1111111111111111111111111";
        // cout << s1.c_str() << endl;
        s1.insert(5,3,'a');
        cout << s1.c_str()<<endl;
    }
}