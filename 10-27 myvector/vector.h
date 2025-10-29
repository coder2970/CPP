#pragma once
#include <iostream>
#include <assert.h>

namespace myvector
{
    template <class T>
    class vector
    {
    public:
        typedef T *iterator;
        typedef const T* const_iterator;

        iterator begin() 
        {
            return _start;
        }

        iterator end()
        {
            return _finish;
        }

        const_iterator begin() const
        {
            return _start;
        }

        const_iterator end() const
        {
            return _finish;
        }

        vector()
        {
        }

        // 拷贝构造
        vector(const vector<T>& v)
        {
            reserve(v.size());
            for(auto e : v)
            {
                push_back(e);
            }
        }

        ~vector()
        {
            delete[] _start;
            _start = _finish = _end_of_storage = nullptr;
        }

        // 赋值重载
        vector<T>& operator=(const vector<T>& v)
        {
            if(this != &v)
            {
                delete[] _start;
                _start = _finish = _end_of_storage = nullptr;
                reserve(v.size());
                for(const auto& e: v)
                {
                    push_back(e);
                }
            }
            return *this;
        }

        void resize(size_t n,const T& x = T())
        {
            if(n < size())
            {
                _finish = _start + n;
            }
            else
            {
                reserve(n);
                while(_finish != _start + n)
                {
                    *_finish = x;
                    _finish ++;
                }
            }
        }

        void reserve(size_t n)
        {
            if(n > capacity())
            {
                size_t oldsize = size();
                T* tmp = new T[n];
                // memcpy 也存在浅拷贝的问题
                // memcpy(tmp,_start,sizeof(T)*size());
                for(size_t i = 0;i < oldsize;i++)
                {
                    tmp[i] = _start[i];
                }
                delete[] _start;


                _finish = tmp + oldsize;
                _start = tmp;
                // error
                // _start = tmp;
                // _finish = _start + size(); 
                _end_of_storage = _start + n;
            }
        }

        T& operator[](size_t i)
        {
            assert(i < size());
            return _start[i];
        }

        const T& operator[](size_t i) const
        {
            assert(i < size());
            return _start[i];
        }

        size_t size() const
        {
            return _finish - _start;
        }

        size_t capacity() const
        {
            return _end_of_storage - _start;
        }

        void push_back(const T& x)
        {
            if(_finish == _end_of_storage)
            {
                reserve(capacity() == 0 ? 4 : capacity() * 2);
            }

            *_finish = x;
            _finish ++;
        }

        void pop_back()
        {
            assert(_finish > _start);
            --_finish;
        }

        void insert(iterator pos,const T& x)
        {
            assert(pos <= _finish);
            assert(pos >= _start);

            // 扩容时注意迭代器失效问题
            if(_finish == _end_of_storage)
            {
                size_t len = pos - _start;
                reserve(capacity() == 0 ? 4 : capacity() * 2);
                pos = _start + len; // 让pos 与 start对应
            }

            // 挪动数据
            iterator it = _finish - 1;
            while(it >= pos)
            {
                *(it + 1) = *(it);
                it --;
            }

            *pos = x;
            ++_finish;
        }

        iterator erase(iterator pos)
        {
            assert(pos <= _finish);
            assert(pos >= _start);

            iterator it = pos + 1;
            while(it <= _finish)
            {
                *(it-1) = *(it);
                it ++;
            }
            --_finish;
            return pos;
        }

    private:
        iterator _start = nullptr;          // 指向第一个元素
        iterator _finish = nullptr;         // 指向最后一个元素的下一个位置
        iterator _end_of_storage = nullptr; // 总容量
    };

}