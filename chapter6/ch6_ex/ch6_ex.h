//
// Created by LMH on 2021/8/22.
//

#ifndef CH6_CH6_EX_H
#define CH6_CH6_EX_H

#include <vector>
#include <cassert>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

/****************************
 * 练习6-1，改写下列类为模板类
 * **************************/

//class example_1{ 
//public:
//    example_1(double min, double max); 
//    example_1(const double *array, int size);
//
//    double& operator[](int index);
//    bool operator==(const example_1&) const;
//
//    bool insert(const double*, int); 
//    bool insert(double);
//
//    double min() const { return _min; } 
//    double max() const { return _max; }
//
//    void min(double); 
//    void max(double);
//
//    int count(double value) const; 
//
//private:
//    int _size; 
//    double *_parray; 
//    double _min; 
//    double _max;
//};

// class template
//template<typename elemType>
//class example_2 {
//public:
//    example_2(const elemType &min, const elemType &max); 
//    example_2(const elemType *array, int size);
//
//    elemType& operator[](int index);
//    bool operator==(const example_2&) const;
//
//    bool insert(const elemType*, int); 
//    bool insert(const elemType&);
//
//    elemType min() const { return _min; } 
//    elemType max() const { return _max; }
//
//    void min(const elemType &); 
//    void max(const elemType &);
//
//    int count(const elemType &value) const; 
//
//private:
//    int _size; 
//    elemType *_parray; 
//    elemType _min; 
//    elemType _max;
//};

/***************************************************
 * 练习6-2，重新以template实现练习4.5的Matrix class，并扩
 * 充其功能，使它能够通过heap memory来支持任意行列大小
 * *************************************************/
typedef unsigned int uint; // 统一将int转为使用unsigned int

template<typename elemType>
class Matrix {
   // 矩阵相加
   friend Matrix<elemType> 
   operator+(const Matrix<elemType> &m1, const Matrix<elemType> &m2) {
        Matrix<elemType> res(m1);
        res += m2;
        return res;
   }
   // 矩阵相乘
   friend Matrix<elemType> 
   operator*(const Matrix<elemType> &m1, const Matrix<elemType> &m2) {
        Matrix<elemType> res(m1);
        m1.comfortable(m2); // m1的列数(cols)必须和m2的行数(rows)相同
        res *= m2;
        return res;
   }

public:
    Matrix(uint rows, uint cols);       // constructor
    Matrix(const Matrix &);             // copy constructor
    Matrix &operator=(const Matrix &);  // copy assignment operator
    ~Matrix() { delete[] _matrix; };    // destructor

    // Matrix operator+(const Matrix &);   // 矩阵相加+
    // Matrix operator*(const Matrix &);   // 矩阵相乘*
    void operator+=(const Matrix &);  // 复合运算+=
    void operator*=(const Matrix &m); // 复合运算*=

    uint rows() const { return _rows; }
    uint cols() const { return _cols; }

    elemType &operator()(uint row, uint col) {
        return _matrix[row * cols() + col];
    }
    const elemType &operator()(uint row, uint col) const {
        return _matrix[row * cols() + col];
    }

    bool same_size(const Matrix &m) const {
        return (rows() == m.rows()) 
            && (cols() == m.cols());
    }
    bool comfortable(const Matrix &m) const {
        return (cols() == m.rows());
    }

    ostream &print(ostream &) const;

protected:
    uint _rows;         // 行数
    uint _cols;         // 列数
    elemType *_matrix;  // 指向矩阵的指针
};

// 重载output运算符
template <typename elemType>
inline ostream &operator<<(ostream &os, const Matrix<elemType> &ns) {
    return ns.print(os);
}

// 矩阵+=运算
template<typename elemType>
void Matrix<elemType>::
operator+=(const Matrix &m) {
    assert(same_size(m)); // 确定m1和m2的大小相同
    uint mat_size = cols() * rows();

    for (uint i = 0; i < mat_size; i++)
        (*(_matrix + i)) += (*(m._matrix + i));
    
}

template<typename elemType>
void Matrix<elemType>::
operator*=(const Matrix &m) {
    uint mat_size = cols() * rows();

    for (uint i = 0; i < mat_size; i++)
        (*(_matrix + i)) *= (*(m._matrix + i));
    
}

// 打印矩阵
template<typename elemType>
ostream &Matrix<elemType>::
print(ostream &os) const {
    uint mat_size = cols() * rows();
    for (uint i = 0; i < mat_size; i++) {
        if (i % cols() == 0) os << endl;
        os << (*(_matrix + i)) << ' ';
    }
    os << endl;
    return os;
}

// constructor
template<typename elemType>
Matrix<elemType>::
Matrix(uint rows, uint cols) : _rows(rows), _cols(cols) {
    uint size = _rows * _cols;
    _matrix = new elemType[size];
    for (int i = 0; i < size; ++i)
        _matrix[i] = elemType();
}

// copy constructor
template<typename elemType>
Matrix<elemType>::
Matrix(const Matrix &rhs) {
    _rows = rhs._rows;
    _cols = rhs._cols;
    uint mat_size = _rows * _cols;
    _matrix = new elemType[mat_size];
    for (uint i = 0; i < mat_size; i++)
        _matrix[i] = rhs._matrix[i];
}

// copy assignment operator
template<typename elemType>
Matrix<elemType> &Matrix<elemType>::
operator=(const Matrix &rhs) {
    if (this != &rhs) {
        _rows = rhs._rows;
        _cols = rhs._cols;
        uint mat_size = _rows * _cols;
        delete[] _matrix;
        _matrix = new elemType[mat_size];
        for (uint i = 0; i < mat_size; i++)
            _matrix[i] = rhs._matrix[i];
    }
    return *this;
}

// 测试函数
extern void test_rotate();
extern void ex6_2();

#endif //CH6_CH6_EX_H
