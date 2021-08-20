//
// Created by LMH on 2021/8/15.
//

#include "ch5.h"

int main () {
    // 使用花括号可以看到析构函数被调用后的情况
    {
        cout << "\nCreating a LibMat object to print()\n";
        LibMat libMat;
        print(libMat);
    }
    cout << "===========================================\n";
    {
        cout << "\nCreating a Book object to print()\n";
        Book b("The Castle", "Franz Kafka");
        print(b);
    }
    cout << "===========================================\n";
    {
        cout << "\nCreating a AudioBook object to print()\n";
        AudioBook ab("Man Without Qualities", "Robert Musil", "Kenneth Meyer");
        print(ab);
    }
    cout << "===========================================\n";
    {
        cout << "\nCreating a Magazine object to print()\n" ;
        Magazine mag("SCI");
        print(mag);
    }
    return 0;
}