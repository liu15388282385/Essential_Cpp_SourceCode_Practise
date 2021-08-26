//
// Created by 刘民皓 on 2021/7/22.
//

#ifndef CH2_SOL_CH2_SOL_H
#define CH2_SOL_CH2_SOL_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

//定义函数
extern bool Fibon_elem(int, int &);
extern bool Print_seq(int);
extern bool Calc_elem(vector<int> &vec, int pos);
extern void Display_elem(vector<int> &vec, const string &title);
extern void Really_calc_elem(vector<int> &vec, int pos);
extern bool Pentagonal_elem(int pos, int &elem);
extern const vector<int> *Pentagonal_series(int pos);

//测试执行函数
[[maybe_unused]] extern void ex2_1();
[[maybe_unused]] extern void ex2_2();
[[maybe_unused]] extern void ex2_3();
[[maybe_unused]] extern void ex2_4();

//内联函数
inline bool Check_validity(int pos)
{
    return !(pos <= 0 || pos > 64);
}

inline bool Calc_elems(vector<int> &vec, int pos)
{
    if (!Check_validity(pos))
    {
        cerr << "Sorry. Invalid position:"
             << pos << endl;
        return false;
    }

    Really_calc_elem(vec, pos);

    return true;
}

/*练习2-5，2-6*/

//重载函数max()
//两个整数、浮点数、字符串
[[maybe_unused]] inline int max(int t1, int t2)
{
    return t1 > t2 ? t1 : t2;
}

[[maybe_unused]] inline float max(float t1, float t2)
{
    return t1 > t2 ? t1 : t2;
}

[[maybe_unused]] inline string max(const string &t1, const string &t2)
{
    return t1 > t2 ? t1 : t2;
}
//一个 整数/浮点数/字符串 vector
[[maybe_unused]] inline int max(const vector<int> &vec)
{
    return *max_element(vec.begin(), vec.end());
}

[[maybe_unused]] inline float max(const vector<float> &vec)
{
    return *max_element(vec.begin(), vec.end());
}

[[maybe_unused]] inline string max(const vector<string> &vec)
{
    return *max_element(vec.begin(), vec.end());
}
//一个 整数/浮点数/字符串 数组, 一个数组大小
[[maybe_unused]] inline int max(const int *parray, int size)
{
    return *max_element(parray, parray + size);
}

[[maybe_unused]] inline float max(const float *parray, int size)
{
    return *max_element(parray, parray + size);
}

[[maybe_unused]] inline string max(const string *parray, int size)
{
    return *max_element(parray, parray + size);
}

//模板函数max()
template <typename Type>
[[maybe_unused]] inline Type max(Type t1, Type t2)
{
    return t1 > t2 ? t1 : t2;
}

template <typename elemType>
[[maybe_unused]] inline elemType max(const vector<elemType> &vec)
{
    return *max_element(vec.begin(), vec.end());
}

template <typename arrayType>
[[maybe_unused]] inline arrayType max(const arrayType *parray, int size)
{
    return *max_element(parray, parray + size);
}

#endif //CH2_SOL_CH2_SOL_H
