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

    bool Erase(const K &key)
    {
        Node *parent = nullptr;
        Node *cur = _root;
        while (cur)
        {
            if (key > cur->_key)
            {
                parent = cur;
                cur = cur->_right;
            }
            else if (key < cur->_key)
            {
                parent = cur;
                cur = cur->_left;
            }
            else
            {
                // 找到该节点 cur即为要删除结点
                // 开始删除
                if (cur->_left == nullptr) // 左子树为空
                {
                    // cur->_right != nullptr
                    // 即下面的操作都要想 要把cur->right给谁
                    if (cur == _root)
                    {
                        _root = cur->_right;
                    }
                    else
                    {
                        if (parent->_left == cur)
                        {
                            parent->_left = cur->_right;
                        }
                        else
                        {
                            parent->_right = cur->_right;
                        }
                    }
                    delete cur;
                }
                else if (cur->_right == nullptr) // 右子树为空
                {
                    if (cur == _root)
                    {
                        _root = cur->_left;
                    }
                    else
                    {
                        if (parent->_left == cur)
                        {
                            parent->_left = cur->_left;
                        }
                        else
                        {
                            parent->_right = cur->_left;
                        }
                    }
                    delete cur;
                }
                else // 左右子树都不为空
                {
                    // 找右子树的最左节点(最小节点)代替
                    Node *replace = cur->_right;
                    Node *replaceParent = cur;
                    while (replace->_left)
                    {
                        replaceParent = replace;
                        replace = replace->_left;
                    }
                    swap(replace->_key, cur->_key);

                    // 此时要删除的是这个最左节点，这个节点的左子树一定为空
                    // 但是要考虑这个节点是父亲的左节点还是右节点
                    if (replaceParent->_left == replace)
                    {
                        replaceParent->_left = replace->_right;
                    }
                    else
                    {
                        replaceParent->_right = replace->_right;
                    }
                    delete replace;
                }
                return true;
            }
        }
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

    // tree.Insert(50);
    // tree.InOrder();
    // tree.Find(50);
    // tree.Find(2000);
    // tree.Erase(8);
    // tree.InOrder();
    // tree.Erase(3);
    // tree.InOrder();
    // tree.Erase(14);
    // tree.InOrder();
    // // 左为空
    // tree.Erase(6);
    // tree.InOrder();
    for (auto e : a)
    {
        tree.Erase(e);
        tree.InOrder();
    }
}
