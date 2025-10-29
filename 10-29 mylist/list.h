#pragma once

namespace mylist
{
    template <class T>
    struct list_node
    {
        list_node<T> *_next;
        list_node<T> *_prev;
        T _data;

        list_node(const T& x = T())
            :_next(nullptr), _prev(nullptr), _data(x)
        {
        }
    };

    template <class T>
    class list
    {
        typedef list_node<T> Node;

    public:
        list()
        {
            _head = new Node;
            _head->_next = _head;
            _head->_prev = _head;
        }

        void push_back(const T& x)
        {
            Node* newnode = new Node(x);

            Node* tail = _head->_prev; // 找到尾节点
            tail->_next = newnode;
            newnode->_prev = tail;

            newnode->_next = _head;
            _head->_prev = newnode;
        }

    private:
        Node *_head;
    };
}