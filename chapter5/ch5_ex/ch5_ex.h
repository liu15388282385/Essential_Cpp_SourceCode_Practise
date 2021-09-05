//
// Created by LMH on 2021/8/15.
//

#ifndef CH5_CH5_EX_H
#define CH5_CH5_EX_H

#include <string>
#include <vector>
#include <iostream>
#include <exception>

using namespace std;

class StackException : public logic_error {
public:
    explicit StackException(const char *unnamed, const char *what) : logic_error(unnamed), _what(what) {}
    const char *what() const noexcept override { return _what.c_str(); }
protected:
    string _what;
};

class PopOnEmpty : public StackException {
public:
    PopOnEmpty() : StackException(nullptr, "Pop on Empty Stack!") {}
};

class PushOnFull : public StackException {
public:
    PushOnFull() : StackException(nullptr, "Push on Full Stack!") {}
};

typedef string elemType;

// 抽象基类Stack --> 具象基类Stack
class Stack {
public:
    explicit Stack(int capacity = 0) : _top(0) {
        if (capacity) {
            _stack.reserve(capacity);
        }
    }
    virtual ~Stack() = default;

    void pop(elemType &);               // 返回栈顶元素并删除
    void push(const elemType &);        // 向栈中添加元素
    virtual bool peek(int, elemType &) {// 返回栈顶元素不删除
        return false;
    } 
    int top() const {                   // 返回栈顶元素
        return _top;
    }                    
    int size() const {                  // 获取栈的大小
        return _stack.size();
    }                   
    bool empty() const {                // 判断栈是否为空
        return !_top;
    }                 
    bool full() const {                 // 判断栈是否已满
        return size() >= _stack.max_size();
    }                  
    void print(ostream &) const;        // 打印元素
    
protected:
    vector<elemType> _stack;
    int _top;
};

ostream &operator<<(ostream &os, const Stack &rhs) {
    rhs.print(os);
    return os;
}

inline void Stack::
pop(elemType &elem) {
    if (empty()) {
        throw PopOnEmpty();
//        return false;
    }
    elem = _stack[--_top];
    _stack.pop_back();
    // return true;
}

inline void Stack::
push(const elemType &elem) {
    if (!full()) {
        _stack.push_back(elem);
        ++_top;
        return;
    }
    throw PushOnFull();
//    return false;
}

inline void Stack::
print(ostream &os) const {
    auto rit = _stack.rbegin(),
    rend = _stack.rend();
    os <<"\n\t";
    while (rit != rend)
        os << *rit++ << "\n\t";
    os << endl;
}

// 后进先出原则的栈
// class LIFO_Stack : public Stack {
// public:
//     explicit LIFO_Stack(int capacity = 0) 
//         : _top(0) { _stack.reserve(capacity); }
    
//     int size() const override { return _stack.size(); }
//     int top() const override { return _top; }
//     bool empty() const override { return !_top; }
//     bool full() const override { return size() >= _stack.max_size(); }
    
//     bool pop(elemType &elem) override {
//         if (empty())
//             return false;
//         elem = _stack[--_top];
//         _stack.pop_back();
//         return true;
//     }
//     bool push(const elemType &elem) override {
//         if (!full()) {
//             _stack.push_back(elem);
//             ++_top;
//             return true;
//         }
//         return false;
//     }
//     // 不提供此方法
//     bool peek(int index, elemType &elem) override {
//         return false;
//     }
    
//     void print(ostream &os) const override {
//         auto rit = _stack.rbegin(),
//              rend = _stack.rend();
//         os <<"\n\t";
//         while (rit != rend)
//             os << *rit++ << "\n\t";
//         os << endl;
//     }
    
// private:
//     vector<elemType> _stack;
//     int _top;
    
// };

// 可以让用户在不更改stack元素的前提下，访问任何一个元素
class PeekBack_Stack : public Stack {
public:
    explicit PeekBack_Stack(int capacity = 0) : Stack(capacity) {}
    
    bool peek(int index, elemType &elem) override ;
    
};

inline bool PeekBack_Stack::
peek(int index, elemType &elem) {
    if (empty())
        return false;

    if (index < 0 || index >= size())
        return false;

    elem = _stack[index];
    return true;
}

void peek(Stack &st, int index) {
    cout << endl;
    string t;
    if (st.peek(index, t))
        cout << "peek: " << t;
    else
        cout << "peek failed!" << endl;
}

// 测试函数
//void ex5_1();
void ex5_2();

#endif //CH5_CH5_EX_H
