#pragma once
#include <assert.h>
#include <iostream>

namespace mylist
{
    template <class T>
    struct list_node
    {
        list_node<T> *_next;
        list_node<T> *_prev;
        T _data;

        list_node(const T &x = T())
            : _next(nullptr), _prev(nullptr), _data(x)
        {
        }
    };

    // // 普通迭代器的实现
    // template <class T>
    // struct list_iterator
    // {
    //     typedef list_node<T> Node;

    //     Node *_node;

    //     list_iterator(Node *node)
    //         : _node(node)
    //     {
    //     }

    //     // *it
    //     T &operator*()
    //     {
    //         return _node->_data;
    //     }

    //     // it->data  --> it.operator->()->data
    //     T *operator->()
    //     {
    //         return &_node->_data;
    //     }

    //     // it++
    //     list_iterator<T> &operator++()
    //     {
    //         _node = _node->_next;
    //         return *this;
    //     }

    //     bool operator!=(const list_iterator<T> &it)
    //     {
    //         return _node != it._node;
    //     }

    //     bool operator==(const list_iterator<T> &it)
    //     {
    //         return _node == it._node;
    //     }
    // };

    // // const 迭代器的实现
    // template <class T>
    // struct list_const_iterator
    // {
    //     typedef list_node<T> Node;

    //     Node *_node;

    //     list_const_iterator(Node *node)
    //         : _node(node)
    //     {
    //     }

    //     // == != ++ * ->

    //     bool operator==(const list_const_iterator<T> &it)
    //     {
    //         return _node == it._node;
    //     }

    //     bool operator!=(const list_const_iterator<T> &it)
    //     {
    //         return _node != it._node;
    //     }

    //     list_const_iterator<T> operator++()
    //     {
    //         _node = _node->_next;
    //         return *this;
    //     }

    //     const T &operator*()
    //     {
    //         return _node->_data;
    //     }

    //     const T *operator->()
    //     {
    //         return &_node->_data;
    //     }
    // };

    // 优化：能不能用模板同时实现普通迭代器和const迭代器
    template <class T, class Ref, class Ptr> // reference pointer
    struct list_iterator
    {
        typedef list_node<T> Node;
        typedef list_iterator<T, Ref, Ptr> Self;
        Node *_node;

        list_iterator(Node *node)
            : _node(node)
        {
        }

        // *it
        Ref operator*()
        {
            return _node->_data;
        }

        // it->data  --> it.operator->()->data
        Ptr operator->()
        {
            return &_node->_data;
        }

        // it++
        Self &operator++()
        {
            _node = _node->_next;
            return *this;
        }
        Self operator++(int)
        {
            Self tmp(*this);
            _node = _node->_next;
            return tmp;
        }

        Self &operator--()
        {
            _node = _node->_prev;
            return *this;
        }

        Self operator--(int)
        {
            Self tmp(*this);
            _node = _node->_prev;
            return tmp;
        }

        bool operator!=(const Self &it) const
        {
            return _node != it._node;
        }

        bool operator==(const Self &it) const
        {
            return _node == it._node;
        }
    };

    template <class T>
    class list
    {
        typedef list_node<T> Node;

    public:
        // typedef list_iterator<T> iterator;
        // typedef list_const_iterator<T> const_iterator;
        typedef list_iterator<T, T &, T *> iterator;
        typedef list_iterator<T, const T &, const T *> const_iterator;

        void empty_init()
        {
            _head = new Node;
            _head->_next = _head;
            _head->_prev = _head;

            _size = 0;
        }

        list()
        {
            empty_init();
        }

        list(const list<T> &lt)
        {
            empty_init();
            for (auto e : lt)
            {
                push_back(e);
            }
        }
        void clear()
        {
            iterator it = begin();
            while (it != end())
            {
                it = erase(it);
            }
        }

        ~list()
        {
            clear();
            delete _head;
            _head = nullptr;
        }

        iterator begin()
        {
            iterator it(_head->_next);
            return it;
        }

        iterator end()
        {
            iterator it(_head);
            return it;
        }
        const_iterator begin() const
        {
            const_iterator it(_head->_next);
            return it;
        }

        const_iterator end() const
        {
            const_iterator it(_head);
            return it;
        }

        void swap(list<T> &lt)
        {
            std::swap(_head, lt._head);
            std::swap(_size, lt._size);
        }

        // 注意这里传参不能传引用
        list<T> &operator=(list<T> lt)
        {
            swap(lt);
            return *this;
        }
        size_t size() const
        {
            return _size;
        }

        void push_back(const T &x)
        {
            // Node *newnode = new Node(x);

            // Node *tail = _head->_prev; // 找到尾节点
            // tail->_next = newnode;
            // newnode->_prev = tail;

            // newnode->_next = _head;
            // _head->_prev = newnode;

            insert(end(), x);
        }

        void insert(iterator pos, const T &x)
        {
            Node *cur = pos._node;
            Node *prev = cur->_prev;

            Node *newnode = new Node(x);

            prev->_next = newnode;
            newnode->_prev = prev;

            newnode->_next = cur;
            cur->_prev = newnode;

            ++_size;
        }
        iterator erase(iterator pos)
        {
            assert(pos != end());
            Node *cur = pos._node;
            Node *nextnode = cur->_next;
            Node *prevnode = cur->_prev;

            prevnode->_next = nextnode;
            nextnode->_prev = prevnode;

            delete cur;
            --_size;
            // 处理迭代器失效问题
            return iterator(nextnode);
        }

        void push_front(const T &x)
        {
            insert(begin(), x);
        }

        void pop_back()
        {
            erase(--end());
        }

        void pop_front()
        {
            erase(begin());
        }

    private:
        Node *_head;
        size_t _size;
    };
}