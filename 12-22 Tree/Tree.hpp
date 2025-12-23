#pragma once
#include <iostream>
#include <queue>
#include <windows.h>
#include <cstdio>
#include <assert.h>

template <class T>
struct TreeNode
{
    T _data;
    TreeNode *_left;
    TreeNode *_right;
    TreeNode(const T &x) : _data(x), _left(nullptr), _right(nullptr)
    {
    }
};

template <class T>
class BTree
{
    typedef TreeNode<T> Node;

public:
    BTree(TreeNode<T> *root = nullptr) : _root(root)
    {
    }

    ~BTree()
    {
        _Destroy(_root);
        _root = nullptr;
    }

    void PreOrder()
    {
        _PreOrder(_root);
        std::cout << std::endl;
    }
    void _PreOrder(Node *root)
    {
        if (root == nullptr)
        {
            return;
        }

        std::cout << root->_data << " ";

        _PreOrder(root->_left);
        _PreOrder(root->_right);
    }

    void InOrder()
    {
        _InOrder(_root);
        std::cout << std::endl;
    }

    void _InOrder(Node *root)
    {
        if (root == nullptr)
        {
            return;
        }
        _InOrder(root->_left);
        std::cout << root->_data << " ";
        _InOrder(root->_right);
    }

    void PostOrder()
    {
        _PostOrder(_root);
        std::cout << std::endl;
    }

    void _PostOrder(Node *root)
    {
        if (root == nullptr)
        {
            return;
        }
        _PostOrder(root->_left);
        _PostOrder(root->_right);
        std::cout << root->_data << " ";
    }

    // 节点个数 : 根节点个数(1) + 左子树节点数 + 右子树节点数
    int TreeSize()
    {
        return _TreeSize(_root);
    }

    int _TreeSize(Node *root)
    {
        if (root == nullptr)
            return 0;
        return 1 + _TreeSize(root->_left) + _TreeSize(root->_right);
    }

    // 叶子节点个数 : 左子树叶子节点个数 + 右子树叶子节点个数
    int LeafSize()
    {
        return _LeafSize(_root);
    }

    int _LeafSize(Node *root)
    {
        if (root == nullptr)
            return 0;
        if (root->_left == nullptr && root->_right == nullptr)
            return 1;
        return _LeafSize(root->_left) + _LeafSize(root->_right);
    }

    // 第k层节点个数 : 左子树第k层节点个数 + 右子树第k层节点个数
    int LevelKSize(int k)
    {
        return _LevelKSize(_root, k);
    }

    int _LevelKSize(Node *root, int k)
    {
        if (root == nullptr)
            return 0;
        if (k == 1)
            return 1;
        k--;
        return _LevelKSize(root->_left, k) + _LevelKSize(root->_right, k);
    }
    // 高度 : max(左子树高度, 右子树高度)
    int Depth()
    {
        return _Depth(_root);
    }

    int _Depth(Node *root)
    {
        if (root == nullptr)
            return 0;
        return 1 + std::max(_Depth(root->_left), _Depth(root->_right));
    }

    // 查找值为x的节点 : 现在左子树找,再到右子树找
    Node *FindX(const T &x)
    {
        return _FindX(_root, x);
    }

    Node *_FindX(Node *root, const T &x)
    {
        if (root == nullptr)
            return nullptr;
        if (root->_data == x)
            return root;
        // return _FindX(root->_left, x) || _FindX(root->_right, x);
        Node *leftnode = _FindX(root->_left, x);
        if (leftnode)
            return leftnode;

        Node *rightnode = _FindX(root->_right, x);
        if (rightnode)
            return rightnode;

        return nullptr;
    }

    // 层序遍历
    void LevelOrder()
    {
        _LevelOrder(_root);
        std::cout << std::endl;
    }
    void _LevelOrder(Node *root)
    {
        std::queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            // 1.取队头
            Node *tmp = q.front();
            q.pop();
            // 2.将队头的左右孩子入队列
            if (tmp->_left)
                q.push(tmp->_left);
            if (tmp->_right)
                q.push(tmp->_right);

            std::cout << tmp->_data << " ";
        }
    }

    // 判断二叉树是否为完全二叉树
    bool TreeIsComplete()
    {
        return _TreeIsComplete(_root);
    }
    bool _TreeIsComplete(Node *root)
    {
        std::queue<Node *> q;

        q.push(root);
        while (!q.empty())
        {
            // 1.出队列
            Node *tmp1 = q.front();
            q.pop();
            // 2.为空跳出循环
            if (tmp1 == nullptr)
                break;
            // 2.不为空, 将左右子节点入队列
            q.push(tmp1->_left);
            q.push(tmp1->_right);
        }
        // 此时队列不一定为空
        while (!q.empty())
        {
            Node *tmp2 = q.front();
            if (tmp2 != nullptr)
                return false;
            q.pop();
        }
        return true;
    }

private:
    Node *_root;

    void _Destroy(Node *&root)
    {
        if (root == nullptr)
            return;
        _Destroy(root->_left);
        _Destroy(root->_right);

        delete root;
        root = nullptr;
    }
};
