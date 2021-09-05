#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <exception>

using namespace std;

int *alloc_and_init(string file_name);

int *allocate_array(int);

void sort_array(int *, int);

void register_data(int *);

int main () {
    // alloc_and_init("exercise_7-1.txt");
    return 0;
}

// 练习 7-1
int *alloc_and_init(string file_name) {

    // ifstream infile(file_name); // 类型不匹配，ifstream接受const char *类型
    ifstream infile(file_name.c_str()); // 使用string的 c_str()取得其C-style字符串表达
    // 定义infile应该检查它是否成功打开
    if (!infile) {
        // 打开文件失败....
    }
    int elem_cnt;
    infile >> elem_cnt;
    // 读取数据后应该检查是否读取成功
    if (!infile) {
        // 读取数据失败....
    }
    int *pi = allocate_array(elem_cnt);
    // 处理指针前，必须确认是否指向实际存在的对象
    if (!pi) {
        // allocate_array()没有分配到内存
    }
    int elem;
    int index = 0;
    while (infile >> elem)
        pi[index++] = elem;

    sort_array(pi, elem_cnt);

    register_data(pi);

    return pi;

}

int *allocate_array(int) {

}

void sort_array(int *, int) {

}

void register_data(int *) {
    
}