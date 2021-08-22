//
// Created by LMH on 2021/8/22.
//

#ifndef CH6_CH6_H
#define CH6_CH6_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

// BTnode class template的前置声明(forward declaration)
template<typename valType>
class BTnode;

// BinaryTree class template的前置声明
template<typename elemType>
class BinaryTree;

// BTnode class template的定义
template<typename valType>
class BTnode {
    friend class BinaryTree<valType>;
public:
    
    
private:
    valType _val;
    int _cnt;
    BTnode *_lchild;
    BTnode *_rchild;
};

// BinaryTree class template的定义
template<typename elemType>
class BinaryTree {
public:
    BinaryTree();
//    BinaryTree(const vector<elemType> &);
    BinaryTree(const BinaryTree &);
    ~BinaryTree();
    BinaryTree &operator=(const BinaryTree &);
    
    bool empty() { return _root == 0; }
    void clear();
    
private:
    BTnode<elemType> *_root; // BTnode指针，指向二叉树根节点
    
    // 将src所指子树(subtree)复制到tar所指子树。
    void copy(BTnode<elemType> *tar, BTnode<elemType> *src);
};

template<typename elemType>
inline BinaryTree<elemType>::
        BinaryTree() : _root(0) {}

template<typename elemType>
inline BinaryTree<elemType>::
        BinaryTree(const BinaryTree &rhs) {
    copy(_root, rhs._root);
}

template<typename elemType>
inline BinaryTree<elemType>
        ::~BinaryTree() {
    clear();
}

template<typename elemType>
inline BinaryTree<elemType> &
        BinaryTree<elemType>::
        operator=(const BinaryTree &rhs) {
    if (this !=&rhs) {
        clear();
        copy(_root, rhs._root);
    }
    return *this;   
}

#endif //CH6_CH6_H
