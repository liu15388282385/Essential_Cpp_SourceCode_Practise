//
// Created by LMH on 2021/8/15.
//

#include "ch5_ex.h"

int main() {

    // ex5_1();
    ex5_2();
    // ex5_3();
    // ex5_4();

    return 0;
}


// void ex5_1() {
//     LIFO_Stack st;
//     string str;

//     cout << "Please enter a series of strings.\n";

// //    while (cin >> str && !st.full())
//     while (cin >> str && st.size() < 5)
//         st.push(str);

//     cout << endl
//          << "About to call peek() with LIFO_Stack" << endl;
//     peek(st, st.top() - 1);
//     cout << st;

//     PeekBack_Stack pst;
//     while (!st.empty()) {
//         string t;
//         if (st.pop(t))
//             pst.push(t);
//     }

//     cout << "About to call peek() with PeekBack_Stack" << endl;
//     peek(pst, pst.top() - 1);
//     cout << pst;
// }

void ex5_2() {
    Stack st;
    string str;

    cout << "Please enter a series of strings.\n";

   while (cin >> str && !st.full())
    // while (cin >> str && st.size() < 5)
        st.push(str);

    cout << endl
         << "About to call peek() with Stack" << endl;
    peek(st, st.top() - 1);
    cout << st;

    PeekBack_Stack pst;
    while (!st.empty()) {
        string t;
        if (st.pop(t))
            pst.push(t);
    }

    cout << "About to call peek() with PeekBack_Stack" << endl;
    peek(pst, pst.top() - 1);
    cout << pst;
}

//void ex5_3() {
//    // 略......
//}

void ex5_4() {

}
