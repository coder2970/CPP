#pragma once
#include <iostream>
#include <assert.h>
template <class K, class V>
struct AVLTreeNode
{
    std::pair<K, V> _kv;
    AVLTreeNode<K, V> *_left;
    AVLTreeNode<K, V> *_right;
    AVLTreeNode<K, V> *_parent; // 控制平衡需要
    int _bf;                    // 平衡因子

    AVLTreeNode(const std::pair<K, V> &kv)
        : _kv(kv),
          _left(nullptr),
          _right(nullptr),
          _parent(nullptr),
          _bf(0)
    {
    }
};

template <class K, class V>
class AVLTree
{
    typedef AVLTreeNode<K, V> Node;

public:
    bool Insert(const std::pair<K, V> &kv)
    {
        if (_root == nullptr)
        {
            _root = new Node(kv);
            return true;
        }

        Node *cur = _root;
        Node *pre = nullptr;

        while (cur)
        {
            if (cur->_kv->first < kv.first)
            {
                pre = cur;
                cur = cur->_right;
            }
            else if (cur->_kv->first > kv.first)
            {
                pre = cur;
                cur = cur->_left;
            }
            else
                return false;
        }
        cur = new Node(kv);
        if (pre->_kv->first < kv.first)
            pre->_right = cur;
        else
            pre->_left = cur;

        cur->_parent = pre;

        // 控制平衡
        // 1.更新平衡因子
        while (pre) // pre为nullptr说明cur已经更新到根节点了
        {
            if (cur == pre->_left)
            {
                pre->_bf--;
            }
            else
            {
                pre->_bf++;
            }

            // 检查父亲的平衡因子
            if (pre->_bf == 0) // 此时父亲左右子树相等
            {
                break;
            }
            else if (pre->_bf == 1 || pre->_bf == -1) // 父亲左右子树高度变化,继续向上更新
            {
                cur = pre;
                pre = pre->_parent;
            }
            else if (pre->_bf == 2 || pre->_bf == -2)
            {
                // 旋转 -TODO

                // 旋转完高度不变,可以退出
                break;
            }
            else
            {
                assert(false);
            }
        }
        return true;
    }

private:
    Node *_root = nullptr;
};
