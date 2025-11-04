#pragma once
#include <list>
#include <vector>
#include <deque>

namespace myqueue
{
    template <class T, class Container = std::deque<T>>
    class queue
    {
    public:
        void push(const T &x)
        {
            _con.push_back(x);
        }

        void pop()
        {
            _con.pop_front();
        }

        bool empty() const
        {
            return _con.empty();
        }

        size_t size() const
        {
            return _con.size();
        }

        const T &back() const
        {
            return _con.back();
        }

        const T &front() const
        {
            return _con.front();
        }

    private:
        Container _con;
    };
}