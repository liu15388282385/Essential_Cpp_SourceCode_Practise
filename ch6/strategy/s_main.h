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

    void set_position(uint pos);
    void set_length(uint len);

    bool operator==(const num_sequence &) const;
    bool operator!=(const num_sequence &) const;

    const vector<uint> *sequence() const { return _pelems; }

    iterator begin() const { return _pelems->begin() + _beg_pos -1; }
    iterator end() const { return _pelems->begin() + _beg_pos + _length; }

    uint length() const { return _length; }
    uint beg_pos() const { return _beg_pos; }
    
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

template<typename seq_type>
num_sequence<seq_type>::
num_sequence(uint len, uint beg_pos) : _pelems() {
    set_position(beg_pos);
    set_length(len);
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

// 设置position
template <typename seq_type>
inline void num_sequence<seq_type>::
set_position(uint pos) {
    if (pos <= 0 || pos > _max_elems) {
		cerr << "!! invalid position: " << pos
			 << " setting pos to default value of 1\n"
			 << "If inadequate, invoke set_position(pos)\n";
		pos = 1;
	}
    _beg_pos = pos;
}

// 设置length
template <typename seq_type>
inline void num_sequence<seq_type>::
set_length(uint len) {
    if (len <= 0 || len + _beg_pos - 1 > _max_elems) {
		cerr << "!! invalid length for this object: " << len
			 << " setting length to default value of 1\n"
			 << "If inadequate, invoke set_length(len)\n";
		len = 1;
	}
    _length = len;
}

// 查值
template <typename seq_type>
inline uint num_sequence<seq_type>::
elem(uint pos) const {
    return (check_integrity(pos, _pelems->size()))
            ? 0
            : (*_pelems)[pos - 1];
}

// 检查是否合法
template <typename seq_type>
inline bool num_sequence<seq_type>::
check_integrity (unit pos, unit size) const {
    if (pos <= 0 || pos > max_elems()) {
		cerr << "!! invalid position: " << pos
			 << " Cannot honor request\n";
		return false;
	}

	if (pos > size)
		gen_elems(pos);

	return true;
}

// 打印元素
template <typename seq_type>
inline ostream &num_sequence<seq_type>::
print(ostream &os) const {
    uint elem_pos = _beg_pos - 1;
    uint end_pos = elem_pos + _length;

    if (!check_integrity(end_pos, _pelems->size()))
        return os;

    os << "("<< _beg_pos <<", "<< _length <<")";

    while (elem_pos < end_pos)
        os << *_pelems[elem_pos++] << " ";
    os << endl;

    return os;  
}

// 测试函数
extern void prog1();
extern void prog2();
extern void prog3();

#endif //CH6_S_MAIN_H
