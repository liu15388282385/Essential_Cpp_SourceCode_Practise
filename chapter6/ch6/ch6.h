//
// Created by LMH on 2021/8/22.
//

#ifndef CH6_CH6_H
#define CH6_CH6_H

#include <vector>
#include <string>
#include <utility>
#include <typeinfo>
#include <iostream>

using namespace std;

//len是数列长度, beg_pos是数列起始位置, 把2个属性作为模板参数后可以动态指定;
template<int len, int beg_pos = 1>
class num_sequence;

template<int len, int beg_pos>
class num_sequence {
public:
    virtual ~num_sequence() = default;

    unsigned int elem(int pos) const {
        return !check_integrity(pos, _pelems->size())
               ? 0 :
               (*_pelems)[pos - 1];
    };
    const char *what_am_i() const { return typeid(*this).name(); };
    static unsigned int max_elems() { return _max_elems; };
    ostream &print(ostream &os = cout) const;

protected:
    virtual void gen_elems(unsigned int pos) const = 0;
    bool check_integrity(int pos, int size) const;
    
    explicit num_sequence(vector<unsigned int> *pe) : _pelems(pe) {}
    enum {
        _max_elems = 1024
    };
    vector<unsigned int> *_pelems;
};

/**
 * output运算符的function template定义
 * @tparam len 
 * @tparam beg_pos 
 * @param os 
 * @param ns 
 * @return 
 */
template<int len, int beg_pos>
ostream &operator<<(ostream &os, const num_sequence<len, beg_pos> &ns) {
    return ns.print(os);
}

/**
 * 检查合法性
 * @tparam len 
 * @tparam beg_pos 
 * @param pos 
 * @param size 
 * @return 
 */
template<int len, int beg_pos>
bool num_sequence<len, beg_pos>::
check_integrity(int pos, int size) const {
    if (pos <= 0 || pos > max_elems()) {
        cerr << "Invalid position: " << pos
             << " Cannot honer request!\n";
        return false;
    }

    if (pos > size)
        gen_elems(pos);

    return true;
}

/**
 * 打印数列
 * @tparam len 
 * @tparam beg_pos 
 * @param os 
 * @return 
 */
template<int len, int beg_pos>
ostream &num_sequence<len, beg_pos>::
print(ostream &os) const {
    int elem_pos = beg_pos - 1;
    int end_pos = elem_pos + len;

    if (!check_integrity(end_pos, _pelems->size()))
        return os;

    os << "( " << beg_pos << " , ";
    os << len << " ) ";

    while (elem_pos < end_pos)
        os << (*_pelems)[elem_pos++] << ' ';
    os << endl;

    return os;
}

// 带有默认参数值的Fibonacci class template
template<int len, int beg_pos = 1>
class Fibonacci : public num_sequence<len, beg_pos> {
public:
    Fibonacci() : num_sequence<len, beg_pos>(&_elems) {};
    
protected:
    virtual void gen_elems(unsigned int pos) const;
    static vector<unsigned int> _elems;
};

// 声明Fibonacci的static data member template
template<int len, int beg_pos>
vector<unsigned int> Fibonacci<len, beg_pos>::_elems;

/**
 * 生成Fibonacci数列
 * @tparam len 
 * @tparam beg_pos 
 * @param pos 
 */
template<int len, int beg_pos>
void Fibonacci<len, beg_pos>::
gen_elems(unsigned int pos) const {
    if (pos <= 0 || pos > Fibonacci<len, beg_pos>::max_elems())
        return;

    if (_elems.empty()) {
        _elems.push_back(1);
        _elems.push_back(1);
    }

    if (_elems.size() <= pos) {
        unsigned int ix = _elems.size();
        unsigned int n_2 = _elems[ix - 2],
                n_1 = _elems[ix - 1];

        unsigned int elem;
        for (; ix <= pos; ++ix) {
            elem = n_2 + n_1;
            // cout << "gen_elems: " << elem << endl;
            _elems.push_back(elem);
            n_2 = n_1;
            n_1 = elem;
        }
    }
}

#endif //CH6_CH6_H
