//
// Created by LMH on 2021/8/17.
//

#ifndef CH5_HYBRID_H
#define CH5_HYBRID_H

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;

class num_sequence {
public:
    typedef vector<unsigned int>::iterator iterator;

    virtual ~num_sequence() = default;
    virtual num_sequence *clone() const = 0;

    unsigned int elem(int pos) const;           // 元素搜索
    bool is_elem(unsigned int) const;
    int pos_elem(unsigned int) const;
    const char *what_am_i() const;
    static int max_elems() { return _max_elems; }

    ostream &print(ostream &os = cout) const;   // 元素打印

    int length() const { return _length; }
    int beg_pos() const { return _beg_pos; }

    iterator begin() const {
        return _relems.begin() + _beg_pos - 1;
    }
    iterator end() const {
        return _relems.begin() + _beg_pos + _length;
    }

    void set_position(int pos);
    void set_length(int len);
    bool operator==(const num_sequence &) const;
    bool operator!=(const num_sequence &) const;

    const vector<unsigned int> *sequence() const {
        return &_relems;
    }

protected:
    // static const int _max_elems = 1024;
    // for compilers not supporting const static
    enum {
        _max_elems = 1024
    };

    virtual void gen_elems(unsigned int pos) const = 0;
    int calc_pos(unsigned int elem) const;
    bool check_integrity(int pos, unsigned int size) const;
    num_sequence(int, int, vector<unsigned int> &);

    int _length;  // 长度
    int _beg_pos; // 起始位置
    vector<unsigned int> &_relems; // 用于指向派生类中的某个static vector的引用(reference)
    // 之所以使用引用而不是用指针，是为了避免检查所指对象是否为null
};

ostream &operator<<(ostream &os, const num_sequence &ns) {
    return ns.print(os);
}

inline bool num_sequence::
operator==(const num_sequence &rhs) const {
    return (_beg_pos == rhs._beg_pos) &&
           (_length == rhs._length);
}

inline bool num_sequence::
operator!=(const num_sequence &rhs) const {
    return !(*this == rhs);
}

inline void num_sequence::
set_position(int pos) {
    if (pos <= 0 || pos > _max_elems) {
        cerr << "!! invalid position: " << pos
             << " setting pos to default value of 1\n"
             << "If inadequate, invoke set_position(pos)\n";
        pos = 1;
    }
    _beg_pos = pos;
}

inline void num_sequence::
set_length(int len) {
    if (len <= 0 || len + _beg_pos - 1 > _max_elems) {
        cerr << "!! invalid length for this object: " << len
             << " setting length to default value of 1\n"
             << "If inadequate, invoke set_length(len)\n";
        len = 1;
    }
    _length = len;
}

inline num_sequence::
num_sequence(int beg_pos, int len, 
             vector<unsigned int> &re) : _relems(re) {
    set_position(beg_pos);
    set_length(len);
}

inline unsigned int num_sequence::
elem(int pos) const {
    return (!check_integrity(pos, _relems.size()))
           ? 0
           : _relems[pos - 1];
}

#include <typeinfo>

inline const char *num_sequence::
what_am_i() const {
    return typeid(*this).name();
}

inline bool num_sequence::
check_integrity(int pos, unsigned int size) const {
    bool status = true;

    if (pos <= 0 || pos > _max_elems) {
        cerr << "!! invalid position: " << pos
             << " Cannot honor request\n";
        status = false;
    } else if (pos > size)
        gen_elems(pos);

    return status;
}

// is_elem() returns true if the element passed in a valid element
// in the object's sequence. For example, if the object represents
// a fibonacci sequence { 1,1, 2, 3, 5, 8, 13, 21, 34, 45}, beginning
// as position 3 for a length of 2, then
//    Obj.is_elem( 1 ); // false
//    Obj.is_elem( 3 ); // true
//    Obj.is_elem( 5 ); // false
//    Obj.is_elem( 4 ); // false

inline bool num_sequence::is_elem(unsigned int elem) const {
    return check_integrity(_beg_pos, _length) 
        && binary_search(begin(), end(), elem);
}

// base class non-inline implementations
// normally would go in a program text file: .cpp

ostream &num_sequence::
print(ostream &os) const {

    int elem_pos = _beg_pos - 1;
    int end_pos = elem_pos + _length;

    if (!check_integrity(end_pos, _relems.size()))
        return os;

    os << "( "
       << _beg_pos << " , "
       << _length << " ) ";

    while (elem_pos < end_pos)
        os << _relems[elem_pos++] << ' ';

    return os;
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

int num_sequence::
pos_elem(unsigned int elem) const {
    cout << "pos_elem( " << elem << " )\n";

    if (_relems[_relems.size() - 1] < elem)
        return calc_pos(elem);

    auto iter = find(_relems.begin(), _relems.end(), elem);
    return (iter == _relems.end())
           ? 0
           : distance(_relems.begin(), iter) + 1;
}

int num_sequence::
calc_pos(unsigned int elem) const {
    // presumption is that check_integrity() has passed
    unsigned int pos = _relems.size() - 1;

    cout << "calc_pos invoked()!: elem: " << elem
         << " pos: " << pos
         << " at: " << _relems[pos]
         << "\n";

    while ((pos < _max_elems) &&
           (_relems[pos] < elem)) {
        gen_elems(++pos); // virtual call!
        cout << " pos: " << pos
             << " at: " << _relems[pos] << endl;
    }

    return ((pos < _max_elems) &&
            (_relems[pos] == elem))
           ? pos + 1
           : 0;
}

// 派生类声明
// 通常放在程序的头文件(.h/.hpp)中

class Fibonacci : public num_sequence {
public:
    explicit Fibonacci(int beg_pos = 1, int len = 1)
            : num_sequence(beg_pos, len, _elems) {}

    num_sequence *clone() const override {
        return new Fibonacci(*this);
    }

protected:
    void gen_elems(unsigned int pos) const override;
    static vector<unsigned int> _elems;
};

class Pell : public num_sequence {
public:
    explicit Pell(int beg_pos = 1, int len = 1)
            : num_sequence(beg_pos, len, _elems) {}

    num_sequence *clone() const override {
        return new Pell(*this);
    }

protected:
    void gen_elems(unsigned int pos) const override;
    static vector<unsigned int> _elems;
};

class Lucas : public num_sequence {
public:
    explicit Lucas(int beg_pos = 1, int len = 1)
            : num_sequence(beg_pos, len, _elems) {}

    num_sequence *clone() const override {
        return new Lucas(*this);
    }

protected:
    void gen_elems(unsigned int pos) const override;
    static vector<unsigned int> _elems;
};

class Triangular : public num_sequence {
public:
    explicit Triangular(int beg_pos = 1, int len = 1)
            : num_sequence(beg_pos, len, _elems) {}

    num_sequence *clone() const override {
        return new Triangular(*this);
    }

protected:
    void gen_elems(unsigned int pos) const override;
    static vector<unsigned int> _elems;
};

class Square : public num_sequence {
public:
    explicit Square(int beg_pos = 1, int len = 1)
            : num_sequence(beg_pos, len, _elems) {}

    num_sequence *clone() const override {
        return new Square(*this);
    }

protected:
    void gen_elems(unsigned int pos) const override;
    static vector<unsigned int> _elems;
};

class Pentagonal : public num_sequence {
public:
    explicit Pentagonal(int beg_pos = 1, int len = 1)
            : num_sequence(beg_pos, len, _elems) {}

    num_sequence *clone() const override {
        return new Pentagonal(*this);
    }

protected:
    void gen_elems(unsigned int pos) const override;
    static vector<unsigned int> _elems;
};

inline void display(ostream &os, const num_sequence &ns,
                    int pos, unsigned int elem_val) {
    os << "The element at position " << pos
       << " for the "     << ns.what_am_i()
       << " sequence is " << elem_val << endl;
}

inline void display(ostream &os, const num_sequence &ns, 
                    int pos) {
    os << "The element at position " << pos 
       << " for the "     << ns.what_am_i() 
       << " sequence is " << ns.elem(pos) << endl;
}

// derived class implementations
// normally would go in a program text file: .cpp
vector<unsigned int> Fibonacci::_elems;
vector<unsigned int> Pell::_elems;
vector<unsigned int> Lucas::_elems;
vector<unsigned int> Triangular::_elems;
vector<unsigned int> Square::_elems;
vector<unsigned int> Pentagonal::_elems;

void Fibonacci::
gen_elems(unsigned int pos) const {
    if (pos <= 0 || pos > max_elems())
        return;

    if (_elems.empty()) {
        _elems.push_back(1);
        _elems.push_back(1);
    }

    if (_elems.size() <= pos) {
        unsigned int ix  = _elems.size();
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

void Pell::
gen_elems(unsigned int pos) const {
    if (pos <= 0 || pos > max_elems())
        return;

    if (_elems.empty()) {
        _elems.push_back(1);
        _elems.push_back(2);
    }

    if (_elems.size() <= pos) {
        unsigned int ix  = _elems.size();
        unsigned int n_2 = _elems[ix - 2],
                     n_1 = _elems[ix - 1];

        unsigned int elem;
        for (; ix <= pos; ++ix) {
            elem = n_2 + 2 * n_1;
            _elems.push_back(elem);
            n_2 = n_1;
            n_1 = elem;
        }
    }
}

void Lucas::
gen_elems(unsigned int pos) const {
    if (pos <= 0 || pos > max_elems())
        return;

    if (_elems.empty()) {
        _elems.push_back(1);
        _elems.push_back(3);
    }

    if (_elems.size() <= pos) {
        unsigned int ix  = _elems.size();
        unsigned int n_2 = _elems[ix - 2],
                     n_1 = _elems[ix - 1];

        unsigned int elem;
        for (; ix <= pos; ++ix) {
            elem = n_2 + n_1;
            _elems.push_back(elem);
            n_2 = n_1;
            n_1 = elem;
        }
    }
}

void Triangular::
gen_elems(unsigned int pos) const {
    if (pos <= 0 || pos > max_elems())
        return;

    if (_elems.size() <= pos) {
        unsigned int end_pos = pos + 1;
        unsigned int ix = _elems.size() + 1;
//        cout << "tri: ix: " << ix << " pos: " << pos << endl;
        for (; ix <= end_pos; ++ix)
            _elems.push_back(ix * (ix + 1) / 2);
    }
}

void Square::
gen_elems(unsigned int pos) const {
    if (pos <= 0 || pos > max_elems())
        return;

    if (_elems.size() <= pos) {
        unsigned int end_pos = pos + 1;
        unsigned int ix = _elems.size() + 1;
        for (; ix <= end_pos; ++ix)
            _elems.push_back(ix * ix);
    }
}

void Pentagonal::
gen_elems(unsigned int pos) const {
    if (pos <= 0 || pos > max_elems())
        return;

    if (_elems.size() <= pos) {
        unsigned int end_pos = pos + 1;
        unsigned int ix = _elems.size() + 1;
        for (; ix <= end_pos; ++ix)
            _elems.push_back(ix * (3 * ix - 1) / 2);
    }
}

// test programs
extern void prog1();
extern void prog2();
extern void prog3();

#endif //CH5_HYBRID_H
