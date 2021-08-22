//
// Created by LMH on 2021/8/22.
//

#ifndef CH6_BTREE_H
#define CH6_BTREE_H

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
    explicit BTnode(const valType &);
    const valType &value() const { return _val; };
    int occurs() const { return _cnt; };

    void insert_value(const valType &);
    void remove_value(const valType &, BTnode *&);
    bool find_value(const valType &) const;

    void preorder(BTnode *, ostream &) const;
    void inorder(BTnode *, ostream &) const;
    void postorder(BTnode *, ostream &) const;

    static void lchild_leaf(BTnode *leaf, BTnode *subtree);

private:
    int _cnt;       // 某值出现次数
    valType _val;   // 节点值
    BTnode *_lchild;// 左子节点
    BTnode *_rchild;// 右子节点

    void display_val(BTnode *pt, ostream &os) const;
    BTnode(const BTnode &);
    BTnode &operator=(const BTnode &);
};

/**
 * constructor
 * @tparam valType 
 * @param val 
 */
template<typename valType>
inline BTnode<valType>::
BTnode(const valType &val) :_val(val) {
    _cnt = 1;
    _lchild = _rchild = 0;
}

/**
 * 插值
 * @tparam valType 
 * @param val 
 */
template<typename valType>
inline void BTnode<valType>::
insert_value(const valType &val) {
    if (val == _val) {
        _cnt++;
        (*BinaryTree<valType>::os()) << "BTnode::insert_value: increment count( "
                                     << val << " : " << _cnt << " )\n";
        return;
    }
    if (val < _val) {
        if (!_lchild) {
            _lchild = new BTnode(val);
            (*BinaryTree<valType>::os()) << "ok: BTnode::insert_value at left child( " << val << " )\n";
        } else
            _lchild->insert_value(val);
    } else {
        if (!_rchild) {
            _rchild = new BTnode(val);
            (*BinaryTree<valType>::os()) << "ok: BTnode::insert_value at right child( " << val << " )\n";
        } else 
            _rchild->insert_value(val);
    }
}

/**
 * 查找某值
 * @tparam valType 
 * @param val 
 * @return 
 */
template<typename valType>
bool BTnode<valType>::
find_value(const valType &val) const {
    if (val == _val)
        return true;

    if (val < _val) {
        if (!_lchild)
            return false;
        else
            return _lchild->find_value(val);
    } else {
        if (!_rchild)
            return false;
        else
            return _rchild->find_value(val);
    }
}

/**
 * 
 * @tparam valType 
 * @param leaf 
 * @param subtree 
 */
template<typename valType>
inline void BTnode<valType>::
lchild_leaf(BTnode *leaf, BTnode *subtree) {
    while (subtree->_lchild)
        subtree = subtree->_lchild;
    subtree->_lchild = leaf;
}

/**
 * 移除值
 * @tparam valType 
 */
template<typename valType>
inline void BTnode<valType>::
remove_value(const valType &val, BTnode *&prev) {
    if (val < _val) {
        if (!_lchild)
            return; // not present
        else
            _lchild->remove_value(val, _lchild);
    } else if (val > _val) {
        if (!_rchild)
            return; // not present
        else
            _rchild->remove_value(val, _rchild);
    } else {
        // ok: found it 
        // reset the tree then delete this node
        if (_rchild) {
            prev = _rchild;
            if (_lchild) {
                if (!prev->_lchild)
                    prev->_lchild = _lchild;
                else
                    BTnode<valType>::lchild_leaf(_lchild, prev->_lchild);
            }
        } else
            prev = _lchild;
        delete this;
    }
}

/**
 * 打印节点值
 * @tparam valType 
 * @param pt 
 * @param os 
 */
template<typename valType>
inline void BTnode<valType>::
display_val(BTnode<valType> *pt, ostream &os) const {
    os << pt->_val;
    if (pt->_cnt > 1)
        os << "( " << pt->_cnt << " ) ";
    else
        os << ' ';
}

/**
 * 前序遍历
 * @tparam valType 
 * @param pt 
 * @param os 
 */
template<typename valType>
inline void BTnode<valType>::
preorder(BTnode *pt, ostream &os) const {
    if (pt) {
        display_val(pt, os);
        if (pt->_lchild)
            preorder(pt->_lchild, os);
        if (pt->_rchild)
            preorder(pt->_rchild, os);
    }
}

/**
 * 中序遍历
 * @tparam valType 
 * @param pt 
 * @param os 
 */
template<typename valType>
inline void BTnode<valType>::
inorder(BTnode<valType> *pt, ostream &os) const {
    if (pt) {
        if (pt->_lchild)
            inorder(pt->_lchild, os);
        display_val(pt, os);
        if (pt->_rchild)
            inorder(pt->_rchild, os);
    }
}

/**
 * 后序遍历
 * @tparam valType 
 * @param pt 
 * @param os 
 */
template<typename valType>
inline void BTnode<valType>::
postorder(BTnode<valType> *pt, ostream &os) const {
    if (pt) {
        if (pt->_lchild)
            postorder(pt->_lchild, os);
        if (pt->_rchild)
            postorder(pt->_rchild, os);
        display_val(pt, os);
    }
}

// BinaryTree class template的定义
template<typename elemType>
class BinaryTree {
    friend ostream &operator<<(ostream &, const BinaryTree<elemType> &);
public:
    BinaryTree();
    explicit BinaryTree(const vector<elemType> &);
    BinaryTree(const BinaryTree &);
    ~BinaryTree();
    BinaryTree &operator=(const BinaryTree &);

    void insert(const elemType &);
    void insert(const vector<elemType> &);
    void remove(const elemType &);
    bool find(const elemType &) const;
    bool empty() { return _root == 0; }
    void clear() {
        if (_root) {
            clear(_root);
            _root = 0;
        }
    } // 移除整个二叉树
    
    void inorder(ostream &os = *_current_os) const { _root->inorder(_root, os); }
    void postorder(ostream &os = *_current_os) const { _root->postorder(_root, os); }
    void preorder(ostream &os = *_current_os) const { _root->preorder(_root, os); }

    ostream &print(ostream &os = *_current_os,
                   void (BinaryTree<elemType>::*traversal)(ostream &) const =
                   &BinaryTree<elemType>::preorder) const;
    
    static void current_os(ostream *os) {
        if (os)
            _current_os = os;
    }
    static ostream *os() { return _current_os; }

private:
    BTnode<elemType> *_root; // BTnode指针，指向二叉树根节点
    static ostream *_current_os;

    // 将src所指子树(subtree)复制到tar所指子树。
    void copy(BTnode<elemType> *&tar, BTnode<elemType> *src);
    void clear(BTnode<elemType> *);
    void remove_root();
};

template<typename elemType>
ostream *BinaryTree<elemType>::_current_os = &cout;

/*
 * default constructor
 */
template<typename elemType>
inline BinaryTree<elemType>::
BinaryTree() : _root(0) {}

/**
 * copy constructor
 * @tparam elemType 
 * @param rhs 
 */
template<typename elemType>
inline BinaryTree<elemType>::
BinaryTree(const BinaryTree &rhs) {
    copy(_root, rhs._root);
}

/**
 * constructor - vector
 * @tparam elemType 
 * @param vec 
 */
template <typename elemType>
BinaryTree<elemType>::
BinaryTree(const vector<elemType> &vec) {
    _root = 0;
    for (int ix = 0; ix < vec.size(); ++ix)
        insert(vec[ix]);
}

/**
 * destructor
 * @tparam elemType 
 */
template<typename elemType>
inline BinaryTree<elemType>::
~BinaryTree() {
    clear();
}

/**
 * copy assignment operator
 * @tparam elemType 
 * @param rhs 
 * @return 
 */
template<typename elemType>
inline BinaryTree<elemType> &
BinaryTree<elemType>::
operator=(const BinaryTree &rhs) {
    if (this != &rhs) {
        clear();
        copy(_root, rhs._root);
    }
    return *this;
}

/**
 * 插入某值
 * @tparam elemType 
 * @param elem 
 */
template<typename elemType>
inline void BinaryTree<elemType>::
insert(const elemType &elem) {
    if (!_root) {
        _root = new BTnode<elemType>(elem);
        (*BinaryTree<elemType>::os()) << "BinaryTree::insert: root( " << elem << " )\n";
    } else
        _root->insert_value(elem);
}

/**
 * 插值 - vector<int>
 * @tparam elemType 
 * @param vec 
 */
template <typename elemType>
void BinaryTree<elemType>::
insert(const vector<elemType> &vec) {
    for (int ix = 0; ix < vec.size(); ++ix)
        insert(vec[ix]);
}

/**
 * 移除某值
 * @tparam elemType 
 * @param elem 
 */
template<typename elemType>
inline void BinaryTree<elemType>::
remove(const elemType &elem) {
    if (_root) {
        if (_root->_val == elem)
            remove_root();  // 根节点的移除操作以特例处理
        else
            _root->remove_value(elem, _root);
    }
}

/**
 * 移除根节点
 * @tparam elemType 
 */
template<typename elemType>
inline void BinaryTree<elemType>::
remove_root() {
    if (!_root)
        return;

    BTnode<elemType> *tmp = _root;
    if (_root->_rchild) {
        _root = _root->_rchild;
        // 现在我们必须将左子节点搬移到
        // 右子节点的左子树的底部
        if (tmp->_lchild) {
            // 为了可读性，分解如下：
            BTnode<elemType> *lc = tmp->_lchild;
            BTnode<elemType> *newlc = _root->_lchild;
            if (!newlc)
                // 没有任何子树，直接接上
                _root->_lchild = lc;
                // lchild_leaf()会遍历整个左子树，
                // 寻找某个可接上去的null左子节点。
                // lchild_leaf是个static member function。
            else
                BTnode<elemType>::lchild_leaf(lc, newlc);
        }
    } else
        _root = _root->_lchild;

    delete tmp;
}

/**
 * 移除整个二叉树
 * @tparam elemType 
 * @param pt 
 */
template<typename elemType>
inline void BinaryTree<elemType>::
clear(BTnode<elemType> *pt) {
    if (pt) {
        clear(pt->_lchild);
        clear(pt->_rchild);
        delete pt;
    }
}

/**
 * 打印元素值
 * @tparam elemType 
 * @param os 
 * @param traversal 
 * @return 
 */
template<typename elemType>
ostream &BinaryTree<elemType>::
print(ostream &os,
      void (BinaryTree::*traversal)(ostream &) const) const {
    (this->*traversal)(os);
    return os;
}

/**
 * 重载输出运算符
 * @tparam elemType 
 * @param os 
 * @param bt 
 * @return 
 */
template<typename elemType>
inline ostream &operator<<(ostream &os, const BinaryTree<elemType> &bt) {
    os << "Tree: " << endl;
    bt.print(os, &BinaryTree<elemType>::preorder);
    return os;
}

/**
 * 查值
 * @tparam elemType 
 * @param elem 
 * @return 
 */
template<typename elemType>
inline bool BinaryTree<elemType>::
find(const elemType &elem) const {
    return _root && _root->find_value(elem);
}

/**
 * 将src所指子树(subtree)复制到tar所指子树
 * @tparam elemType 
 * @param tar 
 * @param src 
 */
template<typename elemType>
void BinaryTree<elemType>::
copy(BTnode<elemType> *&tar, BTnode<elemType> *src) {
    if (src) {
        tar = new BTnode<elemType>(src->_val);
        if (src->_lchild)
            copy(tar->_lchild, src->_lchild);
        if (src->_rchild)
            copy(tar->_rchild, src->_rchild);
    }
}

#endif //CH6_BTREE_H
