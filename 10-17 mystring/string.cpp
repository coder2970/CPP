#include "string.h"

namespace mystring
{
    const size_t string::npos = -1;

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
        // 如果使用size_t end 会出现问题
        int end = _size;
        while(end >= (int)pos)
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
        assert(pos <= _size);
        // 用insert复写
        size_t n = strlen(str);
        insert(pos,n,'x');
        for(size_t i = 0;i < n;i++)
        {
            _str[pos + i] = str[i];
        }
    }

    void string::erase(size_t pos,size_t len)
    {
        assert(pos <= _size);
        // 删完了
        if(len >= _size - pos)
        {
            _str[pos] = '\0';
            _size = pos;
        }
        else
        {
            size_t end = pos + len;
            while(end <= _size)
            {
                _str[end - len] = _str[end];
                end ++;
            }
            _size -= len;
        }
    }
    
    //字符查找
    size_t string::find(char ch,size_t pos)
    {
        for(size_t i = 0;i < _size;i++)
        {
            if(_str[i] == ch)
            {
                return i;
            }
        }
        return npos;
    }

    //字符串查找
    size_t string::find(const char* str,size_t pos)
    {
        const char* p = strstr(_str,str);
        if(p == nullptr)
        {
            return npos;
        }
        else 
        {
            return p - _str;
        }
    }

    string string::substr(size_t pos,size_t len)
    {
        size_t leftlen = _size - pos;
        if(leftlen < len)
        {
            len = leftlen;
        }

        string tmp;
        tmp.reserve(len);
        for(size_t i = 0;i < len;i++)
        {
            tmp += _str[pos + i];
        }

        return tmp;
    }

    bool string::operator==(const string& s) const
    {
        return strcmp(s._str,_str) == 0;
    }
    bool string::operator!=(const string& s) const
    {
        return !(*this == s);
    }
    bool string::operator>(const string& s) const
    {
        return strcmp(_str,s._str) > 0;
    }
    bool string::operator>=(const string& s) const
    {
        return (*this > s || *this == s);
    }
    bool string::operator<(const string& s) const
    {
        return !(*this >= s);
    }
    bool string::operator<=(const string& s) const
    {
        return *this < s || *this == s;
    }

    ostream& operator<<(ostream& out,const string& s)
    {
        for(const auto& e : s)
        {
            out<< e;
        }
        return out;
    }
    istream& operator>>(istream& in,string& s)
    {
        s.clear();

        const size_t N = 1024;
        char buffer[N];
        int i = 0;
        char ch = in.get();
        while(ch != ' ' && ch != '\n')
        {
            buffer[i++] = ch;
            if(i == N -1)
            {
                buffer[i] = '\0';
                s += buffer;
                i = 0;
            }
            ch = in.get();
        }

        if(i > 0)
        {
            buffer[i] = '\0';
            s += buffer;
        }

        return in;
    }













    void test_string()
    {
        string s1("hello world");
        cout << s1.c_str() <<endl;
        // string s2;
        // cout<<s2.c_str()<<endl;
        // s1+=' ';
        // s1+='1';
        // s1+="hello";
        // cout << s1.c_str()<< endl;

        // s1 += "hello bit1111111111111111111111111";
        // cout << s1.c_str() << endl;
        // s1.insert(0,3,'a');
        // cout << s1.c_str()<<endl;

        // const char* str = "abcdefg";
        // s1.insert(4,"str");
        // cout << s1.c_str() << endl;
        // s1.erase(6,2);

        // size_t n = s1.find('e');
        // cout<<n<<endl;

        // cout<< s1.size() <<'-'<< s1.capacity() <<endl;
        // string s2 = s1.substr(6,33);
        // cout << s2.c_str() << endl;
        string s2 = "hello world";
        cin>>s2;
        cout << s2 << endl;
    }
}