//
// Created by 刘民皓 on 2021/8/12.
//

#ifndef CH4_STACK_H
#define CH4_STACK_H

#include <string>
#include <iostream>

using namespace std;

class Stack {
public:
    // 任何操作函数如果执行成功，就返回true
    // pop和peek会将字符串内容置于elem内
    bool push(const string &elem);
    bool pop(string &elem);
    bool peek(string &elem);
    bool empty(); // 判断栈是否为空
    bool full(); // 判断栈是否已满
    bool find(const string &elem) const; // 查看某值是否存在
    int count(const string &elem) const; // 计算某字符串出现的次数

    // size()定义于class本身中，
    // 其他member则仅仅知识声明。
    int size() { return _stack.size(); }

private:
    vector<string> _stack;
};

void fill_stack(Stack &stack, istream &is = cin) {
    string str;
    while (is >> str && !stack.full())
        stack.push(str);
}

inline bool Stack::empty() {
    return _stack.empty();
}

bool Stack::pop(string &elem) {
    if (empty())
        return false;

    elem = _stack.back();
    _stack.pop_back();
    return true;
}

inline bool Stack::full() {
    return _stack.size() == _stack.max_size();
}

bool Stack::peek(string &elem) {
    if (empty())
        return false;

    elem = _stack.back();
    return true;
}

bool Stack::push(const string &elem) {
    if (full())
        return false;

    _stack.push_back(elem);
    return true;
}

bool Stack::find(const string &elem) const {
    return std::find(_stack.begin(), _stack.end(), elem) != _stack.end();
}

int Stack::count(const string &elem) const {
    return std::count(_stack.begin(), _stack.end(), elem);
}

#endif //CH4_STACK_H
