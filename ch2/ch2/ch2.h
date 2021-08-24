//
// Created by 刘民皓 on 2021/7/21.
//

#ifndef CH2_CH2_H
#define CH2_CH2_H

#include <list>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

//冒泡排序
void Display(const vector<int> &vec, ofstream &ofil);
void Swap(int &val1, int &val2, ofstream *ofil = nullptr);
void Bubble_sort(vector<int> &vec, ofstream *ofil = nullptr);
//各项数列
// const vector<int> *Fibon_seq(int size);
// const vector<int> *Lucas_seq(int size);
// const vector<int> *Pell_seq(int size);
// const vector<int> *Triang_seq(int size);
// const vector<int> *Square_seq(int size);
// const vector<int> *Pent_seq(int size);

//全局常量
// const vector<int> *(*seq_array[])(int) = {
//     Fibon_seq, Lucas_seq, Pell_seq,
//     Triang_seq, Square_seq, Pent_seq};

// enum num_sequence
// {
//     ns_unk,
//     ns_fib,
//     ns_pell,
//     ns_lucas,
//     ns_tri,
//     ns_sq,
//     ns_pent,
//     ns_cnt = 6,
//     ns_wrong_msg = 4
// };

inline bool Fibon_elem(int pos, int &elem);
//函数指针
bool Seq_elem(int pos, int &elem,
              const vector<int> *(*seq_ptr)(int) = nullptr);

inline bool is_size_ok(int size);

//重载函数
inline void Display_message(const string &);
//[[maybe_unused]]inline void Display_message( const string&, const vector<int>& );
//[[maybe_unused]]inline void Display_message( const string&, const vector<double>& );
//[[maybe_unused]]inline void Display_message( const string&, const vector<string>& );

//函数模板
//把vector参数抽离出来，将上述后三个重载函数合为一个模板函数
template <typename elemType>
void Display_message(const string &msg, const vector<elemType> &vec);
//function template 再经重载（overloaded）
template <typename elemType>
void Display_message(const string &msg, const list<elemType> &lt);

#endif //CH2_CH2_H
