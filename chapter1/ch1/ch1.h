//
// Created by 刘民皓 on 2021/7/16.
//

#ifndef CH1_CH1_H
#define CH1_CH1_H

#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

//定义cout字体颜色
#define RESET  "\033[0m"  /* Reset  */
#define GREEN  "\033[32m" /* Green  */
#define YELLOW "\033[33m" /* Yellow */
#define BLUE   "\033[34m" /* Blue   */

// external type definitions
typedef const vector<unsigned int> *(*pfunc)(int); //声明一个函数指针指向返回值为const vector<unsigned>* 参数列表为int的函数;
typedef const vector<unsigned int> *pvec;          //声明一个指向const vector<unsigned>对象的指针;

enum num_sequence {
    ns_unk,
    ns_fib,
    ns_pell,
    ns_lucas,
    ns_tri,
    ns_sq,
    ns_pent,
    ns_cnt = 6,
    ns_wrong_msg = 4
};

struct user_profile {
    string name; //玩家名字;
    int guesses; //玩家猜测次数;
    int correct; //玩家猜测正确次数;
    float score; //最终百分制分数
    int level;   //玩家游戏等级;

    num_sequence cur_seq; //玩家猜测数列的类型;
    pvec cur_seq_vec;     //存储玩家当前猜测数列的元素;
    int pos;              //存储玩家当前猜测数列的随机一个元素位置;
};

// external structures
extern pfunc gen_elems[];
extern const char *name_seq[];
extern const char *wrong_msg[];
extern int level_size[];

extern bool greet_user(user_profile *);
extern void play_game(user_profile *);
extern void display_statistics(user_profile *);
extern void file_in(user_profile *);
extern void file_out(user_profile *);

//生成各种数列
extern pvec Fibonacci_gen_elems(int);
extern pvec Pell_gen_elems(int);
extern pvec Lucas_gen_elems(int);
extern pvec Triangular_gen_elems(int);
extern pvec Square_gen_elems(int);
extern pvec Pentagonal_gen_elems(int);

extern void init_user(user_profile *puser, const string &nm, int level);
extern bool correct_guess(user_profile *puser, unsigned int guess);

inline void set_seq_vec(user_profile *pu, pvec p) { pu->cur_seq_vec = p; } //设置玩家当前所猜数列, 赋予一个新数列;
inline pvec seq_vec(user_profile *pu) { return pu->cur_seq_vec; }          //获取玩家当前所猜数列的地址;

/**
 * 获取玩家名字;
 * @param puser
 * @return
 */
inline string user_name(user_profile *puser) {
    return puser->name;
}

/**
 * 获取玩家当前猜测的数列类型;
 * @param puser
 * @return
 */
inline num_sequence seq(user_profile *puser) {
    return puser->cur_seq;
}

/**
 * 递增猜测次数;
 * @param puser
 */
inline void bump_guess(user_profile *puser) {
    ++puser->guesses;
}

/**
 * 递增猜测次数和猜测正确次数;
 * @param puser
 */
inline void bump_correct(user_profile *puser) {
    bump_guess(puser);
    ++puser->correct;
}

#include <cstdlib>
/**
 * 随机选择一个数列进行游戏猜测;
 * @param ui
 * @return
 */
inline num_sequence gen_seq_id() {
    srand(time(nullptr));
    return static_cast<num_sequence>(rand() % ns_cnt + 1);
}

/**
 * 重载打印追踪信息的一系列函数显示当前游戏情况;
 * @param where
 * @param msg
 * @param data
 */
inline void trace(const string &where, const string &msg, const string &data) {
    cerr << where << " " << msg << " " << data << endl;
}

/**
 * @param where
 * @param msg
 * @param val
 */
inline void trace(const string &where, const string &msg, int val) {
    cerr << where << " " << msg << " " << val << endl;
}

/**
 * @param where
 * @param msg
 * @param val
 * @param val2
 */
inline void trace(const string &where, const string &msg, int val, int val2) {
    cerr << where << " " << msg << " " << val << ' ' << val2 << endl;
}

/**
 * @param where
 * @param val1
 * @param val2
 */
inline void trace(const string &where, int val1, int val2) {
    cerr << where << " " << val1 << " " << val2 << endl;
}

/**
 * 检查元素索引是否正确;
 * @param pos
 * @return
 */
inline bool check_integrity(int pos) {
    const int max_elems = 512;

    if (pos <= 0 || pos > max_elems)
    {
        cerr << "!! invalid position: " << pos
             << " Cannot honor request\n";
        return false;
    }

    return true;
}

/**
 * 检查数列索引是否正确;
 * @param id
 * @return
 */
inline num_sequence check_sequence(int id) {
    if (id <= 0 || id > ns_cnt)
    {
        cerr << "!! invalid sequence value: " << id
             << " Choosing one at random\n";

        id = (id % ns_cnt) + 1;
    }

    return static_cast<num_sequence>(id);
}

#endif //CH1_CH1_H
