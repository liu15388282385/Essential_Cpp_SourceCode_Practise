//
// Created by LMH on 2021/8/27.
//

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <exception>

using namespace std;

typedef bool noMem;

int *alloc_and_init(string file_name);

int *allocate_array(int);

void sort_array(int *, int);

void register_data(int *);

int main () {
    // alloc_and_init("exercise_7-1.txt");
    return 0;
}

// 练习 7-1、7-2
int *alloc_and_init(string file_name) {

    // ifstream infile(file_name); // 类型不匹配，ifstream接受const char *类型
    ifstream infile(file_name.c_str()); // 使用string的 c_str()取得其C-style字符串表达
    // 定义infile应该检查它是否成功打开
    if (!infile) {
        // 打开文件失败....
        return 0;
    }
    int elem_cnt;
    infile >> elem_cnt;
    // 读取数据后应该检查是否读取成功
    if (!infile) {
        // 读取数据失败....
        return 0;
    }
    int *pi;
    try {
        pi = allocate_array(elem_cnt);  // (1)
        // 处理指针前，必须确认是否指向实际存在的对象
        if (!pi) {
            // allocate_array()没有分配到内存
        }
        int elem;
        int index = 0;
        while (infile >> elem)
            pi[index++] = elem;

        sort_array(pi, elem_cnt);   // (2)
        register_data(pi);          // (3)
    }
    catch(const noMem &memFail) {   //异常情况(1)
        cerr << "alloc_and_init(): allocate_array() failure!\n"
             << memFail << endl;
        return 0;
    }
    catch(int &sortFail) {          //异常情况(2)
        cerr << "alloc_and_init(): sort_array() failure!\n"
             << "thrown integer value: " << sortFail; 
        return 0;
    }
    catch(string &registerFail) {   //异常情况(3)
        cerr << "alloc_and_init():register_data failure!\n"
			 << "thrown integer value: " << registerFail << endl;
		return 0;
    }

    return pi; // 如果没有任何异常，才会执行到这里

}

int *allocate_array(int) {

}

void sort_array(int *, int) {

}

void register_data(int *) {
    
}