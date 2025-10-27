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
        iterator begin() 
        {
            return _start;
        }

        iterator end()
        {
            return _finish;
        }
        vector()
            : _start(nullptr), _finish(nullptr), _end_of_storage(nullptr)
        {
        }

        ~vector()
        {
            delete[] _start;
            _start = _finish = _end_of_storage = nullptr;
        }

        void reserve(size_t n)
        {
            if(n > capacity())
            {
                T* tmp = new T[n];
                memcpy(tmp,_start,sizeof(T)*size());
                delete[] _start;
                _finish = tmp + size();
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

    private:
        iterator _start;          // 指向第一个元素
        iterator _finish;         // 指向最后一个元素的下一个位置
        iterator _end_of_storage; // 总容量
    };

}