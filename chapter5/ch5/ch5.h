//
// Created by LMH on 2021/8/15.
//

#ifndef CH5_CH5_H
#define CH5_CH5_H

#include <string>
#include <utility>
#include <iostream>

using namespace std;

//定义cout字体颜色
#define RESET  "\033[0m"  /* Reset  */
#define GREEN  "\033[32m" /* Green  */
#define YELLOW "\033[33m" /* Yellow */
#define BLUE   "\033[34m" /* Blue   */

// 顶层抽象基类
class LibMat {
public:
    LibMat() {
        cout << GREEN << "LibMat::LibMat() default constructor!\n" << RESET;
    }
    virtual ~LibMat() {
        cout << GREEN << "LibMat::~LibMat() destructor!\n" << RESET;
    }
    virtual void print() const {
        cout << GREEN << "LibMat::print() -- I am a LibMat object!\n" << RESET;
    }
};

// Book派生类
class Book : public LibMat {
public:
    Book(string title, string author) : _title(move(title)), _author(move(author)) {
        cout << BLUE << "Book::Book(" << GREEN << _title;
        cout << BLUE << ", " << GREEN << _author << BLUE << ")  constructor\n" << RESET;
    }
    ~Book() override  {
        cout << BLUE << "Book::~Book() destructor!\n" << RESET;
    }
    void print() const override { // 重写父类方法
        cout << BLUE << "Book::print() -- I am a Book object!\n" << RESET;
        cout << BLUE << "My title is: " << GREEN << _title << '\n' << RESET;
        cout << BLUE << "My author is: " << GREEN << _author << endl << RESET;
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
        cout << BLUE << "AudioBook::AudioBook(" << GREEN << _title;
        cout << BLUE << ", " << GREEN << _author;
        cout << BLUE << ", " << GREEN << _narrator;
        cout << BLUE << ")  constructor\n" << RESET;
    }
    ~AudioBook() override {
        cout << BLUE << "AudioBook::~AudioBook() destructor!\n";
    }
    void print() const override { // 重写父类方法
        cout << BLUE << "AudioBook::print() -- I am a AudioBook object!\n";
        cout << BLUE << "My title is: " << GREEN << _title << '\n';
        cout << BLUE << "My author is: " << GREEN << _author << '\n';
        cout << BLUE << "My narrator is: " << GREEN << _narrator << endl << RESET;
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
        cout << BLUE<< "Magazine::Magazine("
             << GREEN << _periodical
             << BLUE << ") constructor\n" << RESET;
    }
    ~Magazine() override {
        cout << BLUE << "Magazine:~Magazine "
             << " destructor\n" << RESET;
    }
    void print() const override {
        cout << BLUE << "Magazine::print() -- I am a Magazine object!\n";
        cout << "My periodical is: " << GREEN << _periodical << endl << RESET;
    }
    
    const string &periodical() const {
        return _periodical;
    }

protected:
    string _periodical; // 期刊
};

// non-member-function
void print(const LibMat &mat) {
    cout << BLUE << "in global print(): about to print mat.print()\n";
    mat.print();
}

#endif //CH5_CH5_H
