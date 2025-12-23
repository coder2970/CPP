#include "tree.hpp"
TreeNode<char> *CreateTree()
{
    TreeNode<char> *node1 = new TreeNode<char>('a');
    TreeNode<char> *node2 = new TreeNode<char>('b');
    TreeNode<char> *node3 = new TreeNode<char>('c');
    TreeNode<char> *node4 = new TreeNode<char>('d');
    TreeNode<char> *node5 = new TreeNode<char>('e');
    TreeNode<char> *node6 = new TreeNode<char>('f');

    node1->_left = node2;
    node1->_right = node3;

    node2->_left = node4;

    // node3->_left = node5;
    // node3->_right = node6;

    return node1;
}
int main()
{
    // SetConsoleOutputCP(65001);
    BTree<char> tree(CreateTree());

    tree.PreOrder();
    tree.InOrder();
    tree.PostOrder();

    std::cout << tree.TreeSize() << std::endl;
    std::cout << tree.LeafSize() << std::endl;
    std::cout << tree.LevelKSize(1) << std::endl;
    std::cout << tree.Depth() << std::endl;
    TreeNode<char> *c = tree.FindX('j');
    if (c)
        printf("%c\n", c->_data);
    else
        printf("没找到\n");

    tree.LevelOrder();
    if (tree.TreeIsComplete())
        std::cout << "1" << std::endl;
    else
        std::cout << "0" << std::endl;
    return 0;
}