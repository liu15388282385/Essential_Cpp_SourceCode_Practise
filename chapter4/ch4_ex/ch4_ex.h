//
// Created by 刘民皓 on 2021/8/12.
//

#ifndef CH4_CH4_EX_H
#define CH4_CH4_EX_H

#include <map>
#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <algorithm>

#include "../stack.h"

using namespace std;

/********************
 * 练习4.3
 ********************/
class globalWrapper {
public:
    // 取值
    static string program_name() { return _program_name; }
    static string version_stamp() { return _version_stamp; }
    static int version_number() { return _version_number; }
    __attribute__((unused)) static int tests_run() { return _tests_run; }
    __attribute__((unused)) static int tests_passed() { return _tests_passed; }

    // 设值
    static void program_name(const string &npn) {
        _program_name = npn;
    }
    static void version_stamp(const string &nstamp) {
        _version_stamp = nstamp;
    }
    static void version_number(int nval) {
        _version_number = nval;
    }
    __attribute__((unused)) static void tests_run(int nval) {
        _tests_run = nval;
    }
    __attribute__((unused)) static void tests_passed(int nval) {
        _tests_passed = nval;
    }

private:
    static string _program_name;
    static string _version_stamp;
    static int _version_number;
    static int _tests_run;
    static int _tests_passed;
};

string globalWrapper::_program_name;
string globalWrapper::_version_stamp;
int globalWrapper::_version_number;
int globalWrapper::_tests_run;
int globalWrapper::_tests_passed;

/********************
 * 练习4.4
 ********************/
class UserProfile {
public:
    // 用户四个可能的等级
    enum uLevel {
        Beginner, Intermediate, Advanced, Guru
    };

    // 构造函数
    explicit UserProfile(string username, uLevel = Beginner);
    UserProfile();

    // default memberwise initialization 和 default memberwise copy 已足够所需，
    // 不必另行设计 copy constructor 或 copy assignment operator，
    // 也不需要destructor

    // 重载运算符函数
    bool operator==(const UserProfile &rhs);
    bool operator!=(const UserProfile &rhs);

    // 以下函数用来读取数据
    string login() const { return _login; }
    string user_name() const { return _user_name; }
    int login_count() const { return _times_logged; }
    int guess_count() const { return _guesses; }
    int guess_correct() const { return _correct_guesses; }
    double guess_average() const;
    string level() const;

    // 以下函数用来写入数据
    void reset_login(const string &val) { _login = val; }
    void user_name(const string &val) { _user_name = val; }
    
    void reset_level(const string &);
    void reset_level(uLevel newLevel) { _user_level = newLevel; }
    
    void reset_login_count(int val) { _times_logged = val; }
    void reset_guess_count(int val) { _guesses = val; }
    void reset_guess_correct(int val) { _correct_guesses = val; }
    
    void bump_login_count(int cnt = 1) { _times_logged += cnt; }
    void bump_guess_count(int cnt = 1) { _guesses += cnt; }
    void bump_guess_correct(int cnt = 1) { _correct_guesses += cnt; }

private:
    string _login;          // 登录记录
    string _user_name;      // 用户姓名
    int _times_logged;      // 登入次数
    int _guesses;           // 猜过次数
    int _correct_guesses;   // 猜对次数
    uLevel _user_level;     // 用户等级

    static map<string, uLevel> _level_map;
    static void init_level_map();
    static string guest_login();

};

// 计算最终分数（百分制）
inline double UserProfile::guess_average() const {
    return _guesses
           ? double(_correct_guesses) / double(_guesses) * 100
           : 0.0;
}

// 构造函数，初始化数据
inline UserProfile::UserProfile(string username, uLevel level)
        : _login(std::move(username)), _user_level(level),
          _times_logged(1), _guesses(0), _correct_guesses(0) {}

// 构造函数，处理默认的初始数据
inline UserProfile::UserProfile()
        : _login("guest"), _user_level(Beginner),
          _times_logged(1), _guesses(0), _correct_guesses(0) {

    static int id = 0;
    //对于guest加入一个独一无二的会话标识符;
    _login += to_string(++id);
}

// 判断是否相等
inline bool UserProfile::operator==(const UserProfile &rhs) {
    if (_login == rhs._login && _user_name == rhs._user_name)
        return true;
    return false;
}

// 判断是否不相等
inline bool UserProfile::operator!=(const UserProfile &rhs) {
    return !(*this == rhs);
}

inline string UserProfile::level() const {
    static string _level_table[4] = {
            "Beginner", "Intermediate", "Advanced", "Guru"
    };
    return _level_table[_user_level];
}

ostream &operator<<(ostream &os, const UserProfile &rhs) {
    // 输出格式：stan1 Beginner 12 100 10 10%
    os << rhs.login() << ' ';
    os << rhs.level() << ' ';
    os << rhs.login_count() << ' ';
    os << rhs.guess_count() << ' ';
    os << rhs.guess_correct() << ' ';
    os << rhs.guess_average() << endl;
    return os;
}

map<string, UserProfile::uLevel> UserProfile::_level_map;

void UserProfile::init_level_map() {
    _level_map["Beginner"] = Beginner;
    _level_map["Intermediate"] = Intermediate;
    _level_map["Advanced"] = Advanced;
    _level_map["Guru"] = Guru;
}

inline void UserProfile::reset_level(const string &level) {
    map<string, uLevel>::iterator it;
    if (_level_map.empty())
        init_level_map();
    // 确保level的确代表一个可识别的用户等级
    _user_level =
            ((it = _level_map.find(level)) != _level_map.end()) ? it->second : Beginner;
}

inline string UserProfile::guest_login() {
    return {};
}

istream &operator>>(istream &is, UserProfile &rhs) {
    // 假设以下输入都有效，不做错误检验
    string login, level;
    int lcount, gcount, gcorrect;

    is >> login >> level;
    is >> lcount >> gcount >> gcorrect;
    rhs.reset_login(login);
    rhs.reset_level(level);

    rhs.reset_login_count(lcount);
    rhs.reset_guess_count(gcount);
    rhs.reset_guess_correct(gcorrect);

    return is;
}

/********************
 * 练习4.5
 ********************/

typedef float elemType; // 方便转为template形式
class Matrix {
    // 矩阵相加
    friend Matrix operator+(const Matrix &, const Matrix &);

    // 矩阵相乘
    friend Matrix operator*(const Matrix &, const Matrix &);

public:
    // 可接受一个拥有16个元素的数组
    explicit Matrix(const elemType *);

    // default constructor, 可选择性接受16个数值
    explicit Matrix(elemType = 0., elemType = 0., elemType = 0., elemType = 0.,
                    elemType = 0., elemType = 0., elemType = 0., elemType = 0.,
                    elemType = 0., elemType = 0., elemType = 0., elemType = 0.,
                    elemType = 0., elemType = 0., elemType = 0., elemType = 0.);

    // 复合运算符
    void operator+=(const Matrix &);

    // 下标访问矩阵元素
    elemType &operator()(int row, int column) {
        return _matrix[row][column];
    }

    elemType operator()(int row, int column) const {
        return _matrix[row][column];
    }

    // 简化"转换至通用型矩阵(general matrix)"的过程
    static int rows() { return 4; }

    static int cols() { return 4; }

    // 打印函数
    ostream &print(ostream &) const;

private:
    elemType _matrix[4][4]{};
};

// 重载输出符号
inline ostream &operator<<(ostream &os, const Matrix &m) {
    return m.print(os);
}

// 矩阵相加
Matrix operator+(const Matrix &m1, const Matrix &m2) {
    Matrix result(m1);
    result += m2;
    return result;
}

// 矩阵相乘
Matrix operator*(const Matrix &m1, const Matrix &m2) {
    Matrix result;
    for (int ix = 0; ix < Matrix::rows(); ++ix) {
        for (int jx = 0; jx < Matrix::cols(); ++jx) {
            result(ix, jx) = 0;
            for (int kx = 0; kx < Matrix::cols(); ++kx)
                result(ix, jx) += m1(ix, kx) * m2(kx, jx);
        }
    }
    return result;
}

// 复合运算符+=
void Matrix::operator+=(const Matrix &m) {
    for (int ix = 0; ix < 4; ++ix)
        for (int jx = 0; jx < 4; ++jx)
            _matrix[ix][jx] += m(ix, jx);
}

// 打印矩阵
ostream &Matrix::print(ostream &os) const {
    for (auto ix : _matrix) {
        for (int jx = 0; jx < 4; ++jx)
            os << ix[jx] << ' ';
        os << endl;
    }
    os << endl;
    return os;
}

Matrix::Matrix(elemType a11, elemType a12, elemType a13, elemType a14,
               elemType a21, elemType a22, elemType a23, elemType a24,
               elemType a31, elemType a32, elemType a33, elemType a34,
               elemType a41, elemType a42, elemType a43, elemType a44) {

    _matrix[0][0] = a11;
    _matrix[0][1] = a12;
    _matrix[0][2] = a13;
    _matrix[0][3] = a14;
    _matrix[1][0] = a21;
    _matrix[1][1] = a22;
    _matrix[1][2] = a23;
    _matrix[1][3] = a24;
    _matrix[2][0] = a31;
    _matrix[2][1] = a32;
    _matrix[2][2] = a33;
    _matrix[2][3] = a34;
    _matrix[3][0] = a41;
    _matrix[3][1] = a42;
    _matrix[3][2] = a43;
    _matrix[3][3] = a44;
}

Matrix::Matrix(const elemType *array) {
    int array_index = 0;
    for (auto &ix : _matrix)
        for (float &jx : ix)
            jx = array[array_index++];
}

/********************
 * 测试函数
 ********************/
extern void ex4_1();
extern void ex4_2();
extern void ex4_3();
extern void ex4_4();
extern void ex4_5();

#endif //CH4_CH4_EX_H
