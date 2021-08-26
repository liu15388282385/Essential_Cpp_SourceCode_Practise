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
    num_sequence(unit beg_pos = 1, uint len = 1);

    unit elem(uint pos) const;
    bool is_elem(uint elem) const;
    uint pos_elem(unit elem) const;

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

// constructor
template<typename seq_type>
num_sequence<seq_type>::
num_sequence(uint beg_pos, uint len) : _pelems(seq_type::elemset()) {
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
    return (!check_integrity(pos, _pelems->size()))
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
        os << (*_pelems)[elem_pos++] << " ";
    os << endl;

    return os;  
}

// is_elem() returns true if the element passed in a valid element
// in the object's sequence. For example, if the object represents
// a fibonacci sequence { 1,1, 2, 3, 5, 8, 13, 21, 34, 45}, beginning
// as position 3 for a length of 2, then
//    Obj.is_elem( 1 ); // false
//    Obj.is_elem( 3 ); // true
//    Obj.is_elem( 5 ); // false
//    Obj.is_elem( 4 ); // false
template <typename seq_type>
inline bool num_sequence<seq_type>::
is_elem(uint elem) const {
    return (!check_integrity(_beg_pos, _length))
           ? false
           : binary_search(begin(), end(), elem);
}

// pos_elem() returns the position of an element within the sequence
// independent of what the object's position and length. The object
// simply is used to identify the sequence for which to return a position.
// If the element value is invalid, return 0. For example, if the object
// represents a fibonacci sequence, then
//     Obj.pos_elem( 1 ); // returns 1 - ignore duplicate
//     Obj.pos_elem( 32 ); // returns 9
//     Obj.pos_elem( very-large-instance ); // your choice
//     Obj.pos_elem( 4 ); // return 0
template <typename seq_type>
uint num_sequence<seq_type>::
pos_elem(uint elem) const {
    cout << "pos_elem( " << elem << " )\n";

    if((*_pelems)[_pelems->size() - 1] < elem)
        return calc_pos(elem);
    
    iterator iter = find(_pelems->begin(), _pelems->end(), elem);
    return (iter == _pelems->end())
           ? 0
           : distance(_pelems->begin(), iter) + 1;// distance()函数用于计算两个迭代器范围内的元素个数
}

template <typename seq_type>
uint num_sequence<seq_type>::
calc_pos (uint elem) const {
    int pos = _pelems->size() - 1;
    cout << "calc_pos invoked()!: elem: " << elem
		 << " pos: " << pos
		 << " at: " << (*_pelems)[pos] << endl;
    
    while (pos < _max_elems && (*_pelems)[pos] < elem) {
        _ns.gen_elems(++pos);
        cout << "pos: " << pos
             << " at: " << (*_pelems)[pos]
             << endl;
    }

    return (pos < _max_elems) && ((*_pelems)[pos] == elem)
           ? pos + 1
           : 0;
}

class Fibonacci {
public:
    void gen_elems(uint pos) const;
    static vector<uint> *elemset() { return &_elems; }
    static const char *what_am_i() { return "Fibonacci"; }

protected:
    static vector<uint> _elems;
};

class Pell {
public:
    void gen_elems(uint pos) const;
    static vector<uint> *elemset() { return &_elems; }
    static const char *what_am_i() { return "Pell"; }
    
protected:
    static vector<uint> _elems;
};

class Lucas {
public:
    void gen_elems(uint pos) const;
    static vector<uint> *elemset() { return &_elems; }
    static const char *what_am_i() { return "Lucas"; }
    
protected:
    static vector<uint> _elems;
};

class Triangular {
public:
    void gen_elems(uint pos) const;
    static vector<uint> *elemset() { return &_elems; }
    static const char *what_am_i() { return "Triangular"; }
    
protected:
    static vector<uint> _elems;
};

class Square {
public:
    void gen_elems(uint pos) const;
    static vector<uint> *elemset() { return &_elems; }
    static const char *what_am_i() { return "Square"; }
    
protected:
    static vector<uint> _elems;
};

class Pentagonal {
public:
    void gen_elems(uint pos) const;
    static vector<uint> *elemset() { return &_elems; }
    static const char *what_am_i() { return "Pentagonal"; }
    
protected:
    static vector<uint> _elems;
};

vector<uint> Fibonacci::_elems;
vector<uint> Pell::_elems;
vector<uint> Lucas::_elems;
vector<uint> Triangular::_elems;
vector<uint> Square::_elems;
vector<uint> Pentagonal::_elems;

template<typename seq_type>
inline void display(ostream &os, const num_sequence<seq_type> &ns, 
                    uint pos) {
    os << "The element at position "
	   << pos << " for the "
	   << ns.what_am_i() << " sequence is "
	   << ns.elem(pos) << endl;
}

template<typename seq_type>
inline void display(ostream &os, const num_sequence<seq_type> &ns, 
                    uint pos, uint elem_val) {
    os << "The element at position " << pos
	   << " for the "
	   << ns.what_am_i()
	   << " sequence is " << elem_val << endl;
}

void Fibonacci::
gen_elems(uint pos) const {
	if (pos <= 0 ||
		pos > num_sequence<Fibonacci>::max_elems())
		return;

	if (_elems.empty()) {
		_elems.push_back(1);
		_elems.push_back(1);
	}

	if (_elems.size() <= pos) {
		int ix = _elems.size();
		int n_2 = _elems[ix - 2],
			n_1 = _elems[ix - 1];

		int elem;
		for (; ix <= pos; ++ix) {
			elem = n_2 + n_1;
			// cout << "gen_elems: " << elem << endl;
			_elems.push_back(elem);
			n_2 = n_1;
			n_1 = elem;
		}
	}
}

void Pell::
gen_elems(uint pos) const {
	if (pos <= 0 ||
		pos > num_sequence<Pell>::max_elems())
		return;

	if (_elems.empty()) {
		_elems.push_back(1);
		_elems.push_back(2);
	}

	if (_elems.size() <= pos) {
		int ix = _elems.size();
		int n_2 = _elems[ix - 2],
			n_1 = _elems[ix - 1];

		int elem;
		for (; ix <= pos; ++ix) {
			elem = n_2 + 2 * n_1;
			_elems.push_back(elem);
			n_2 = n_1;
			n_1 = elem;
		}
	}
}

void Lucas::
gen_elems(uint pos) const {
	if (pos <= 0 ||
		pos > num_sequence<Lucas>::max_elems())
		return;

	if (_elems.empty()) {
		_elems.push_back(1);
		_elems.push_back(3);
	}

	if (_elems.size() <= pos) {
		int ix = _elems.size();
		int n_2 = _elems[ix - 2],
			n_1 = _elems[ix - 1];

		int elem;
		for (; ix <= pos; ++ix) {
			elem = n_2 + n_1;
			_elems.push_back(elem);
			n_2 = n_1;
			n_1 = elem;
		}
	}
}

void Triangular::
gen_elems(uint pos) const {
	if (pos <= 0 ||
		pos > num_sequence<Triangular>::max_elems())
		return;

	if (_elems.size() <= pos) {
		int end_pos = pos + 1;
		int ix = _elems.size() + 1;

		for (; ix <= end_pos; ++ix)
			_elems.push_back(ix * (ix + 1) / 2);
	}
}

void Square::
gen_elems(uint pos) const {
	if (pos <= 0 ||
		pos > num_sequence<Square>::max_elems())
		return;

	if (_elems.size() <= pos) {
		int end_pos = pos + 1;
		int ix = _elems.size() + 1;
		for (; ix <= end_pos; ++ix)
			_elems.push_back(ix * ix);
	}
}

void Pentagonal::
gen_elems(uint pos) const {
	if (pos <= 0 ||
		pos > num_sequence<Pentagonal>::max_elems())
		return;

	if (_elems.size() <= pos) {
		int end_pos = pos + 1;
		int ix = _elems.size() + 1;
		for (; ix <= end_pos; ++ix)
			_elems.push_back(ix * (3 * ix - 1) / 2);
	}
}

// 测试函数
extern void prog1();
extern void prog2();
extern void prog3();

#endif //CH6_S_MAIN_H
