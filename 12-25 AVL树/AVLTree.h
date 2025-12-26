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
        std::cout << root->_kv.second << " ";
        _InOrder(root->_right);
    }
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
            if (cur->_kv.first < kv.first)
            {
                pre = cur;
                cur = cur->_right;
            }
            else if (cur->_kv.first > kv.first)
            {
                pre = cur;
                cur = cur->_left;
            }
            else
                return false;
        }
        cur = new Node(kv);
        if (pre->_kv.first < kv.first)
            pre->_right = cur;
        else
            pre->_left = cur;

        cur->_parent = pre;

        // 控制平衡
        // 1.更新平衡因子
        while (pre) // pre为nullptr说明cur已经更新到根节点了  -- 思考
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
                if (pre->_bf == -2 && cur->_bf == -1) // 对应右单旋
                {
                    RotateR(pre); // 以pre为旋转点进行右单旋
                }
                else if (pre->_bf == 2 && cur->_bf == 1) // 对应左单旋
                {
                    RotateL(pre); // 左单旋
                }
                else if (pre->_bf == -2 && cur->_bf == 1) // 对应左右双旋 对于pre来说左边高,对于cur来说右边高
                {
                    RotateLR(pre);
                }
                else if (pre->_bf == 2 && cur->_bf == -1)
                {
                    RotateRL(pre);
                }
                else
                {
                    assert(false);
                }
                // 旋转完高度不变,可以退出
                break;
            }
            else
            {
                // 增加代码健壮性
                assert(false);
            }
        }
        return true;
    }

    // 右单旋:左边高
    void RotateR(Node *parent)
    {
        // 核心控制三个节点: parent 父节点 , subL 父节点的左子树的根, subLR 父节点的左子树的根节点的右子树的根
        //                       parent        parent 的左                parent 的左 的右
        // 除了这三个位置,其余子树相对位置均没变
        Node *subL = parent->_left;
        Node *subLR = subL->_right;

        parent->_left = subLR;
        subL->_right = parent;
        if (parent->_parent != nullptr)
        {
            if (parent->_parent->_left == parent)
            {
                parent->_parent->_left = subL;
            }
            else
            {
                parent->_parent->_right = subL;
            }
            subL->_parent = parent->_parent;
        }
        else
        {
            _root = subL;
            subL->_parent = nullptr;
        }
        parent->_parent = subL;
        // 注意: subLR又可能为空
        if (subLR != nullptr)
        {
            subLR->_parent = parent;
        }

        // 同时subL和parent的平衡因子也要更新
        subL->_bf = parent->_bf = 0;
    }

    void RotateL(Node *parent)
    {
        Node *subR = parent->_right;
        Node *subRL = subR->_left;

        parent->_right = subRL;
        subR->_left = parent;
        if (subRL != nullptr)
            subRL->_parent = parent;

        if (parent->_parent != nullptr)
        {
            // parent的parent的左右指针也要修改
            if (parent->_parent->_left == parent)
                parent->_parent->_left = subR;
            else
                parent->_parent->_right = subR;
            subR->_parent = parent->_parent;
        }
        else
        {
            _root = subR;
            subR->_parent = nullptr;
        }
        parent->_parent = subR;

        // 更新平衡因子
        subR->_bf = parent->_bf = 0;
    }

    // 左右双旋
    void RotateLR(Node *parent)
    {
        // 根据8的平衡因子来确定5和10的平衡因子,分三种情况
        Node *subL = parent->_left;
        Node *subLR = subL->_right;
        int bf = subLR->_bf;

        RotateL(parent->_left);
        RotateR(parent);

        if (bf == -1)
        {
            subLR->_bf = 0;
            subL->_bf = 0;
            parent->_bf = 1;
        }
        else if (bf == 1)
        {
            subLR->_bf = 0;
            subL->_bf = -1;
            parent->_bf = 0;
        }
        else if (bf == 0)
        {
            subLR->_bf = 0;
            subL->_bf = 0;
            parent->_bf = 0;
        }
        else
        {
            assert(false);
        }
    }

    void RotateRL(Node *parent)
    {
        Node *subR = parent->_right;
        Node *subRL = subR->_left;
        int bf = subRL->_bf;

        RotateR(parent->_right);
        RotateL(parent);

        if (bf == 1)
        {
            subR->_bf = 0;
            subRL->_bf = 0;
            parent->_bf = -1;
        }
        else if (bf == -1)
        {
            subR->_bf = 1;
            subRL->_bf = 0;
            parent->_bf = 0;
        }
        else if (bf == 0)
        {
            subR->_bf = 0;
            subRL->_bf = 0;
            parent->_bf = 0;
        }
        else
        {
            assert(false);
        }
    }
    int Height()
    {
        return _Height(_root);
    }
    int _Height(Node *root)
    {
        if (root == nullptr)
            return 0;
        return 1 + std::max(_Height(root->_left), _Height(root->_right));
    }
    // 先算左子树高度,再算右子树高度
    bool isBalance()
    {
        return _isBalance(_root);
    }
    bool _isBalance(Node *root)
    {
        if (root == nullptr)
            return true;
        int leftHeight = _Height(root->_left);
        int rightHeight = _Height(root->_right);
        int diff = rightHeight - leftHeight;

        if (std::abs(diff) >= 2)
        {
            std::cout << root->_kv.first << "高度差异常" << std::endl;
            return false;
        }

        if (root->_bf != diff)
        {
            std::cout << root->_bf << " " << diff << "平衡因子异常" << std::endl;
            return false;
        }

        return _isBalance(root->_left) && _isBalance(root->_right);
    }

private:
    Node *_root = nullptr;
};
