//
// Created by LMH on 2021/8/15.
//

#ifndef CH5_CH5_H
#define CH5_CH5_H

#include <iostream>
#include <string>
#include <utility>

using namespace std;

// 顶层抽象基类
class LibMat {
public:
    LibMat() {
        cout << "LibMat::LibMat() default constructor!\n";
    }
    virtual ~LibMat() {
        cout << "LibMat::~LibMat() destructor!\n";
    }
    virtual void print() const {
        cout << "LibMat::print() -- I am a LibMat object!\n";
    }
};

// Book派生类
class Book : public LibMat {
public:
    Book(string title, string author) : _title(move(title)), _author(move(author)) {
        cout << "Book::Book(" << _title;
        cout << ", " << _author << ")  constructor\n";
    }
    ~Book() override  {
        cout << "Book::~Book() destructor!\n";
    }
    void print() const override { // 重写父类方法
        cout << "Book::print() -- I am a Book object!\n";
        cout << "My title is: " << _title << '\n';
        cout << "My author is: " << _author << endl;
    }
    
    const string &title() const {
        return _title;
    }
    const string &author() const {
        return _author;
    }
    
protected:
    string _title; // 标题
    string _author;// 作者
};

// AudioBook派生子类
class AudioBook : public Book {
public:
    AudioBook(string title, string author, string narrator) 
            : Book(move(title), move(author)), _narrator(move(narrator)){
        cout << "AudioBook::AudioBook(" << _title;
        cout << ", " << _author;
        cout << ", " << _narrator;
        cout << ")  constructor\n";
    }
    ~AudioBook() override {
        cout << "AudioBook::~AudioBook() destructor!\n";
    }
    void print() const override { // 重写父类方法
        cout << "AudioBook::print() -- I am a AudioBook object!\n";
        cout << "My title is: " << _title << '\n';
        cout << "My author is: " << _author << '\n';
        cout << "My narrator is: " << _narrator << endl;
    }
    
    const string &narrator() const {
        return _narrator;
    }
    
protected:
    string _narrator; // 播讲者
};

// Magazine派生类
class Magazine : public LibMat {
public:
    explicit Magazine(string periodical) : _periodical(std::move(periodical)) {
        cout << "Magazine::Magazine("
             << _periodical
             << ") constructor\n";
    }
    ~Magazine() override {
        cout << "Magazine:~Magazine "
             << " destructor\n";
    }
    void print() const override {
        cout << "Magazine::print() -- I am a Magazine object!\n";
        cout << "My periodical is: " << _periodical << endl;
    }
    
    const string &periodical() const {
        return _periodical;
    }

protected:
    string _periodical; // 期刊
};

// non-member-function
void print(const LibMat &mat) {
    cout << "in global print(): about to print mat.print()\n";
    mat.print();
}

#endif //CH5_CH5_H
