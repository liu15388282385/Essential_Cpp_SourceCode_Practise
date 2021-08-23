//
// Created by LMH on 2021/8/22.
//

#include "ch6.h"

int main() {
    Fibonacci<8> fib1;
    Fibonacci<8,8> fib2;
    Fibonacci<12,8> fib3;
    
    cout << "fib1: " << fib1 << endl
         << "fib2: " << fib2 << endl
         << "fib3: " << fib3 << endl;
    
    return 0;
}