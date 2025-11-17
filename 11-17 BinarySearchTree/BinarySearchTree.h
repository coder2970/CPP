#pragma once
#include <iostream>
using namespace std;
// 二叉搜索树
template <class K>
struct BSTreeNode
{
public:
    K _key;
    BSTreeNode<K> *_left;
    BSTreeNode<K> *_right;
    BSTreeNode(const K &key)
        : _key(key), _left(nullptr), _right(nullptr)
    {
    }
};

// 默认不允许重复插入
template <class K> // Key
class BSTree
{
    typedef BSTreeNode<K> Node;

public:
    bool Insert(const K &key)
    {
        // 如果是空树，直接new一个结点
        if (_root == nullptr)
        {
            _root = new Node(key);
            return true;
        }
        // 不用递归
        Node *cur = _root;
        Node *parent = nullptr;

        while (cur)
        {
            if (key > cur->_key) // 插入值比结点值大
            {
                parent = cur;
                cur = cur->_right;
            }
            else if (key < cur->_key) // 小
            {
                parent = cur;
                cur = cur->_left;
            }
            else
            {
                return false;
            }
        }
        cur = new Node(key);
        // 判断链接在父节点的左子树还是右子树
        if (key > parent->_key)
        {
            parent->_right = cur;
        }
        else
        {
            parent->_left = cur;
        }
        return true;
    }

    // 解决私有变量无法传参问题
    void InOrder()
    {
        _InOrder(_root);
        cout << endl;
    }

    void _InOrder(Node *root)
    {
        if (root == nullptr)
        {
            return;
        }

        // 递归
        _InOrder(root->_left);
        cout << root->_key << " ";
        _InOrder(root->_right);
    }

    bool Find(const K &key)
    {
        Node *cur = _root;
        while (cur)
        {
            if (key < cur->_key)
            {
                cur = cur->_left;
            }
            else if (key > cur->_key)
            {
                cur = cur->_right;
            }
            else
            {
                cout << "find success!" << endl;
                return true;
            }
        }
        cout << "not find " << endl;
        return false;
    }

private:
    Node *_root = nullptr;
};

void testBSTree()
{
    int a[] = {8, 3, 1, 10, 6, 4, 7, 14, 13};
    BSTree<int> tree;
    for (auto e : a)
    {
        tree.Insert(e);
    }
    tree.InOrder();

    tree.Insert(50);
    tree.InOrder();
    tree.Find(50);
    tree.Find(2000);
}
