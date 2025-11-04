#pragma once
#include <vector>

namespace mypriority_queue
{
    template <class T>
    class Less
    {
    public:
        bool operator()(const T &x, const T &y)
        {
            return x < y;
        }
    };

    template <class T>
    class Greater
    {
    public:
        bool operator()(const T &x, const T &y)
        {
            return x > y;
        }
    };

    template <class T, class Container = std::vector<T>, class Compare = Less<T>>
    class priority_queue
    {
    public:
        void adjustUp(size_t child)
        {
            Compare com;
            size_t parent = (child - 1) / 2;
            while (child > 0)
            {
                if (com(_con[parent], _con[child]))
                {
                    std::swap(_con[parent], _con[child]);
                    child = parent;
                    parent = (child - 1) / 2;
                }
                else
                {
                    break;
                }
            }
        }

        void adjustDown(size_t parent)
        {
            Compare com;
            size_t child = parent * 2 + 1;
            while (child < _con.size())
            {
                if (child + 1 < _con.size() && com(_con[child], _con[child + 1]))
                {
                    ++child;
                }

                if (com(_con[parent], _con[child]))
                {
                    std::swap(_con[child], _con[parent]);
                    parent = child;
                    child = parent * 2 + 1;
                }
                else
                {
                    break;
                }
            }
        }

        void push(const T &x)
        {
            _con.push_back(x);
            adjustUp(_con.size() - 1);
        }
        void pop()
        {
            std::swap(_con[0], _con[_con.size() - 1]);
            _con.pop_back();
            adjustDown(0);
        }

        const T &top()
        {
            return _con[0];
        }

        size_t size() const
        {
            return _con.size();
        }

        bool empty() const
        {
            return _con.empty();
        }

    private:
        Container _con;
    };
}