//
// Created by 刘民皓 on 2021/8/12.
//

#ifndef CH4_CH4_H
#define CH4_CH4_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//class intBuffer {
//public:
   // ...
//private:
   // static const int _buf_size = 1024; // ok but not with VC++
//    enum {
//        _buf_size = 1024
//    };
//    int _buffer[_buf_size]; // ok
//};
//
//intBuffer b1, b2;

class Triangular_iterator {

public:
    // 为了不需要在每次访问元素时都执行-1操作，
    // 此处将_index的值设为index-1。
    explicit Triangular_iterator(int index) : _index(index - 1) {} //构造函数初始化iterator;
    // 运算符函数——运算符前加上关键字operator即可
    bool operator==(const Triangular_iterator &) const;   //比较iterator是否相等;
    bool operator!=(const Triangular_iterator &) const;   //比较iterator是否不相等;
    int operator*() const;                                //指针解引用运算符;
    Triangular_iterator &operator++();                    //前置自增运算符;
    const Triangular_iterator operator++(int);            //后置自增运算符;

private:
    void check_integrity() const; //判断_index索引是否合法;
    int _index;
};

class Triangular {

public:
    //3个构造函数;
    explicit Triangular(int len = 1, int beg_pos = 1);
    Triangular(const Triangular &);
    Triangular &operator=(const Triangular &rhs);

    //获取vector长度, 起始位置, pos位置的元素值;
    int length() const { return _length; }
    int beg_pos() const { return _beg_pos; }
    static int elem(int pos) ;

    //更改Triangular的长度大小和起始位置;
    void length(int nlen) { _length = nlen; }
    void beg_pos(int npos) { _beg_pos = npos; }

    //获取元素值和重置_next指针;
    bool next(int &val) const;
    void next_reset() const { _next = 1; }

    //只能访问静态成员, 此处访问的是成员vector<int> _elems;
    static bool is_elem(int);
    static void gen_elements(int length);
    static void gen_elems_to_value(int value);
    static void display(int length, int beg_pos, ostream &os = cout);

    typedef Triangular_iterator iterator;
    Triangular_iterator begin() const {
        return Triangular_iterator(_beg_pos);
    }
    Triangular_iterator end() const {
        return Triangular_iterator(_beg_pos + _length);
    }

private:
    friend class Triangular_iterator; // 作为Triangular类的iterator友元, 可访问private中的成员;
    int _length;        // 元素个数
    int _beg_pos;       // 起始位置
    mutable int _next;  // 下一个迭代目标
    // static const int   _max_elems = 1024; // ok, but not VC++
    enum {
        _max_elems = 1024
    };
    // static data member 用来表示唯一的、可共享的member
    // 它可以在同一类的所有对象中被访问
    static vector<int> _elems;
};

//重载cout运算符，输出Triangular对象
ostream &operator<<(ostream &os, const Triangular &rhs) {
    os << "( " << rhs.beg_pos() << " , " << rhs.length() << " ) ";
    rhs.display(rhs.length(), rhs.beg_pos(), os);
    return os;
}

//重载cin运算符，输出Triangular对象
istream &operator>>(istream &is, Triangular &rhs) {
    char ch1, ch2;  
    int bp, len;

    is >> ch1 >> bp >> ch2 >> len;
    rhs.beg_pos(bp);
    rhs.length(len);
    rhs.next_reset();
    return is;
}

Triangular::Triangular(int len, int beg_pos) 
: _length(len > 0 ? len : 1), _beg_pos(beg_pos > 0 ? beg_pos : 1) {
    _next = _beg_pos;
    int elem_cnt = _beg_pos + _length;
    if (_elems.size() < elem_cnt)
        gen_elements(elem_cnt);
}

Triangular::Triangular(const Triangular &rhs) 
: _length(rhs._length), _beg_pos(rhs._beg_pos), _next(rhs._beg_pos - 1) {

}

//计算所有元素之和;
int sum(const Triangular &trian) {
    if (!trian.length())
        return 0;
    int val, sum = 0;
    trian.next_reset(); // 重置为起点开始累加;
    while (trian.next(val))
        sum += val;
    return sum;
}

int Triangular::elem(int pos) {
    return _elems[pos - 1];
}

bool Triangular::next(int &val) const {
    if (!_next)
        return false;

    if (_next < _beg_pos + _length) {
        val = _elems[_next++];
        return true;
    }
    _next = 0;
    return false;
}

Triangular &Triangular::operator=(const Triangular &rhs) {
    if (this != &rhs) {
        _length = rhs._length;
        _beg_pos = rhs._beg_pos;
        _next = 1;
    }
    return *this;
}

vector<int> Triangular::_elems; // 定义一个静态vector;

bool Triangular::is_elem(int value) {
    if (_elems.empty() || _elems[_elems.size() - 1] < value)
        gen_elems_to_value(value);

    return find(_elems.begin(), _elems.end(), value) != _elems.end();
}

void Triangular::gen_elements(int length) {
    if (length < 0 || length > _max_elems) {
        cerr << "Triangular Sequence: oops: invalid size: "
             << length << " -- max size is "
             << _max_elems << endl;
        return;
    }

    if (_elems.size() < length) {
        int ix = _elems.size() ? _elems.size() + 1 : 1;
        for (; ix <= length; ++ix)
            _elems.push_back(ix * (ix + 1) / 2); // 添加元素直到vector长度大于等于length;
    }
}

void Triangular::gen_elems_to_value(int value) {
    int ix = _elems.size();
    if (!ix) {
        _elems.push_back(1);
        ix = 1;
    }

    while (_elems[ix - 1] < value && ix < _max_elems) {
        //     cout << "elems to value: " << ix*(ix+1)/2 << endl;
        _elems.push_back(ix * (ix + 1) / 2); // 添加元素到vector中直到大于等于value;
        ++ix;
    }

    if (ix == _max_elems)
        cerr << "Triangular Sequence: oops: value too large "
             << value << " --  exceeds max size of "
             << _max_elems << endl;
}

void Triangular::display(int length, int beg_pos, ostream &os) {
    if (length <= 0 || beg_pos <= 0) {
        cerr << "invalid parameters -- unable to fulfill request: "
             << length << ", " << beg_pos << endl;
        return;
    }

    int elems = beg_pos + length - 1;

    if (_elems.size() < elems)
        gen_elements(elems);

    for (int ix = beg_pos - 1; ix < elems; ++ix)
        os << _elems[ix] << ' ';
}

inline bool 
Triangular_iterator::
operator==(const Triangular_iterator &rhs) const {
    return _index == rhs._index; // 判断2个Triangular类是否相等;
}

inline bool 
Triangular_iterator::
operator!=(const Triangular_iterator &rhs) const {
    return !(*this == rhs); // 使用重载过的==运算符的非运算;
}

// 迭代器溢出异常类
class iterator_overflow { 
public:
    iterator_overflow(int index, int max) 
            : _index(index), _max(max) {}

    int index() { return _index; }
    int max() {return _max; }

    void what_happened(ostream &os = cerr)  {
        os << "Internal error: current index"
           << _index << " exceeds maximum bound: "
           << _max;
    }

private:
    int _index;
    int _max;
};

// // example
// extern void log_message(const char*);
// extern string err_message[];
// extern ostream log_file;

// bool has_elem(Triangular_iterator first, 
//               Triangular_iterator last, int elem) {

//     bool status = true;

//     try {
//         while (first != last) {
//             if (*first == elem)
//                 return status;
//             ++first;
//         }   
//     }
//     // try块内的程序代码执行时，如果有任何异常抛出，
//     // 我们之前捕获其中类型为iterator_overflow的异常
//     catch(iterator_overflow &iof) {
//         // log_message(iof.what_happened());
//         log_message("check if iterators address same container");
//     }

//     status = false;
//     return status;
// }

//检查下标是否合法
inline void 
Triangular_iterator::check_integrity() const {
    if (_index > Triangular::_max_elems) {
        iterator_overflow ex(_index, Triangular::_max_elems); // 抛出一个异常类iterator_overflow;
        throw ex; // 明确抛出的异常对象
    }
    if (_index > Triangular::_elems.size())
        Triangular::gen_elements(_index); // 添加元素到vector中直到长度大于等于_index;
}

//重载解引用
inline int 
Triangular_iterator::operator*() const {
    check_integrity();
    return Triangular::_elems[_index]; // 获取_index索引中的元素;
}

//重载自增运算符前置版
inline Triangular_iterator 
&Triangular_iterator::operator++() {
    ++_index;
    check_integrity();
    return *this;
}

//重载自增运算符后置版
inline const Triangular_iterator 
Triangular_iterator::operator++(int) {
    Triangular_iterator tmp = *this; // 存储先前值 
    ++_index;                        // 递增下标
    check_integrity();
    return tmp;                      // 返回先前值
}

//函数对象作用是比较小于等于的值;
template<typename elemType>
class LessThan {
public:
    explicit LessThan(elemType val) : _val(val) {}

    elemType comp_val() const { return _val; }  // 基值的读取
    void comp_val(elemType val) { _val = val; } // 基值的写入

    bool operator()(elemType _value) const;

private:
    elemType _val;
};

template<typename elemType>
inline bool 
LessThan<elemType>::operator()( elemType _value) const {
    return _value < _val;
}

template<typename elemType>
int count_less_than(const vector<elemType> &vec, elemType comp) {
    LessThan<elemType> lt(comp);

    int count = 0;
    for (int ix : vec)
        if (lt(ix))
            ++count;
        
    return count;
}

template<typename elemType>
void print_less_than(const vector<elemType>&vec, int comp, ostream &os = cout) {
    LessThan<elemType> lt(comp);
    auto iter = vec.begin();
    auto it_end = vec.end();
    
    os << "elements less than " << lt.comp_val() << ": ";
    while ((iter = find_if(iter, it_end, lt)) != it_end) {
        os << *iter << ' ';
        ++iter;
    }
    os << endl;
}

//测试函数
extern void pro_1();
extern void pro_2();
extern void pro_3();
extern void pro_4();
extern void pro_5();

#endif //CH4_CH4_H
