//
// Created by 刘民皓 on 2021/7/31.
//

#ifndef CH3_CH3_H
#define CH3_CH3_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>

using namespace std;

// globals as convenience for executing procedures
const int int_size = 12;
//const int double_size = 8;
const int string_size = 4;
const int int_not_present = 1024;

static int ia[int_size] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144};
//double da[double_size] = { 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0 };
static string sa[string_size] = {"pooh", "piglet", "eeyore", "tigger"}; /* NOLINT */

static vector<int> ivec{1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144}; /* NOLINT */
//vector<double> dvec( da, da + double_size ); /* NOLINT */
static vector<string> svec{"pooh", "piglet", "eeyore", "tigger"}; /* NOLINT */

//定义cout字体颜色
#define RESET  "\033[0m"  /* Reset */
#define GREEN  "\033[32m" /* Green */
#define YELLOW "\033[33m" /* Yellow */
#define BLUE   "\033[34m" /* Blue */

//各版本find_ver函数
const int *find_ver1(const vector<int> &vec, int value);

template<typename elemType>
const elemType *find_ver2(const vector<elemType> &vec, const elemType &value);

template<typename elemType>
const elemType *find_ver3(const elemType *array, int size, const elemType &value);

template<typename elemType>
const elemType *find_ver4(const elemType *array, int size, const elemType &value);

template<typename elemType>
const elemType *find_ver5(const elemType *first, const elemType *last,
                          const elemType &value);

template<typename IteratorType, typename elemType>
IteratorType find_ver6(IteratorType first, IteratorType last, const elemType &value);

//测试上述所有find函数
void prog_find_vers();

//mybegin函数防止获取错误的起始位置;
template<typename elemType>
inline const elemType *mybegin(const vector<elemType> &vec) //源程序begin与标准库中的函数重名需改为mybegin;
{
    return vec.empty() ? nullptr : &vec[0];
}

//myend函数防止获取错误的终止位置;
template<typename elemType>
inline const elemType *myend(const vector<elemType> &vec) //源程序end与标准库中的函数重名需改为myend;
{
    return vec.empty() ? nullptr : &vec[vec.size()];
}

//filter函数
vector<int> filter_ver1(const vector<int> &vec, int filter_value, bool ( *pred )(int, int));

vector<int> filter_ver2(const vector<int> &vec, int val, less<int> lt);

template<typename InputIterator, typename OutputIterator,
        typename ElemType, typename Comp>
OutputIterator filter_ver3(InputIterator first, InputIterator last,
                           OutputIterator at, const ElemType &val, Comp pred);

template<typename elemType>
vector<elemType> sub_vec(const vector<elemType> &vec, elemType val);

//测试上述所有filter函数
void prog_filter_vers();

//遍历顺序性容器
template<typename elemType>
void display(const vector<elemType> &vec, ostream &os = cout);

//从stdin流输入数据并输出至stdout流中;
void prog_io_std();

//文件输入输出;
void prog_io_fil();

//测试iostream_iterator;
void prog_io_iters();

#endif //CH3_CH3_H
