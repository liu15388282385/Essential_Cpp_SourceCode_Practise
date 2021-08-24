//
// Created by LMH on 2021/8/22.
//

#ifndef CH6_S_MAIN_H
#define CH6_S_MAIN_H

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;

typedef unsigned int unit; // 统一使用unsigned int类型

// class template num_sequence 的前置声明 
template<typename seq_type>
class num_sequence;

template<typename seq_type>
ostream &operator<<(ostream &os, const num_sequence<seq_type> &ns);

template<typename seq_type>
class num_sequence {
public:
    typedef vector<uint>::iterator iterator;
    num_sequence(unit len = 1, uint beg_pos = 1);

    unit elem(uint pos) const;
    bool is_elem(uint) const;
    uint pos_elem(unit) const;

    const char *what_am_i() const { return seq_type::what_am_i(); }
    static uint max_elems() { return _max_elems; }
    ostream &print(ostream &os = cout) const;

    void set_position(int pos);
    void set_length(int pos);

    bool operator==(const num_sequence &) const;
    bool operator!=(const num_sequence &) const;

    const vector<uint> *sequence() const { return _pelems; }

    iterator begin() const { return _pelems->begin() + _beg_pos -1; }
    iterator end() const { return _pelems->begin() + _beg_pos + _length; }

    uint length() { return _length; }
    uint beg_pos() { return _beg_pos; }
    
protected:
    void gen_elems(uint pos) const { _ns.gen_elems(pos); }
    bool check_integrity(uint pos, unit size) const;
    uint calc_pos(uint elem) const; 

    seq_type _ns;
    unit _length;
    unit _beg_pos;
    vector<uint> *_pelems;
    enum { _max_elems = 1024 };
};

// 重载output运算符
template<typename seq_type>
ostream &operator<<(ostream &os, const num_sequence<seq_type> &ns) {
    return ns.print(os);
}

// 重载==运算符
template <typename seq_type>
inline bool num_sequence<seq_type>::
operator==(const num_sequence &rhs) const {
    return (_beg_pos == rhs._beg_pos) 
        && (_length == rhs._length);
}

// 重载!=运算符
template <typename seq_type>
inline bool num_sequence<seq_type>::
operator!=(const num_sequence &rhs) const {
    return !(*this == rhs);
}

// 测试函数
extern void prog1();
extern void prog2();
extern void prog3();

#endif //CH6_S_MAIN_H
