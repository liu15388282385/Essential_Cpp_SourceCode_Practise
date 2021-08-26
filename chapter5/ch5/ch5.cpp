//
// Created by LMH on 2021/8/15.
//

#include "ch5.h"

int main () {
    // 使用花括号可以看到析构函数被调用后的情况
    {
        cout << YELLOW << "\nCreating a LibMat object to print()\n" << RESET;
        LibMat libMat;
        print(libMat);
    }
    cout << "===========================================\n";
    {
        cout << YELLOW << "\nCreating a Book object to print()\n" << RESET;
        Book b("The Castle", "Franz Kafka");
        print(b);
    }
    cout << "===========================================\n";
    {
        cout << YELLOW << "\nCreating a AudioBook object to print()\n" << RESET;
        AudioBook ab("Man Without Qualities", "Robert Musil", "Kenneth Meyer");
        print(ab);
    }
    cout << "===========================================\n";
    {
        cout << YELLOW << "\nCreating a Magazine object to print()\n" << RESET;
        Magazine mag("SCI");
        print(mag);
    }
    return 0;
}