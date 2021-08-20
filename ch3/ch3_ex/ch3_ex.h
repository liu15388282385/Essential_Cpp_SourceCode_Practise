//
// Created by 刘民皓 on 2021/7/29.
//

#ifndef CH3_CH3_EX_H
#define CH3_CH3_EX_H

#include <iostream>
#include <functional>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

typedef vector<string> vstring;

//定义cout字体颜色
#define RESET  "\033[0m"  /* Reset */
#define GREEN  "\033[32m" /* Green */
#define YELLOW "\033[33m" /* Yellow */
#define BLUE   "\033[34m" /* Blue */

//练习3-1
[[maybe_unused]]void ex3_1();

void initialize_exclusion_set(set<string> &);

void progress_file(map<string, int> &, const set<string> &, ifstream &ifile);

void user_query(const map<string, int> &);

void display_word_count(const map<string, int> &, ofstream &);

//练习3-2
[[maybe_unused]]void ex3_2();

/**
 * function object
 */
class LessThan {
public:
    bool operator()(const string &s1, const string &s2) {
        return s1.size() < s2.size();
    }
};

/**
 * 打印排序后的vector
 * @tparam elemType
 * @param vec
 * @param os
 * @param len
 */
template<typename elemType>
void display_vector(const vector<elemType> &vec,
                    ostream &os = cout, int len = 8) {
    typename vector<elemType>::const_iterator
            iter = vec.begin();

    int elem_cnt = 1;
    while (iter != vec.end())
        os << *iter++
           << (!(elem_cnt++ % len) ? '\n' : ' ');
    os << endl;
}

//练习3-3
[[maybe_unused]]void ex3_3();

void populate_map(ifstream &, map<string, vstring> &);

void query_map(const string &, const map<string, vstring> &);

void display_map(const map<string, vstring> &, ostream &);

//练习3-4
[[maybe_unused]]void ex3_4();

/**
 * function object
 */
class even_elem {
public:
    bool operator()(int elem) {
        return elem % 2 == 0;
    }
};

//filter练习
const int elem_size = 8;
int ia[elem_size] = {12, 8, 43, 0, 6, 21, 3, 7};
vector<int> ivec(ia, ia + elem_size);
int ia2[elem_size];
vector<int> ivec2;

template<typename InputIterator, typename OutputIterator,
        typename ElemType, typename Comp>
OutputIterator filter(InputIterator first, InputIterator last,
                      OutputIterator out, const ElemType &val, Comp pred);

[[maybe_unused]]void ex_filter();

#endif //CH3_CH3_EX_H
