//
// Created by 刘民皓 on 2021/8/12.
//

#include "ch4.h"

int main() {

    pro_1();
    pro_2();
    pro_3();
    pro_4();
    pro_5();

}

void pro_1() {
    char ch;
    bool more = true;

    while (more) {
        cout << "Enter value: ";
        int ival;
        cin >> ival;

        bool is_elem = Triangular::is_elem(ival);

        cout << ival
             << (is_elem ? " is " : " is not ")
             << "an element in the Triangular series.\n"
             << "Another value? (y/n) ";

        cin >> ch;
        if (ch == 'n' || ch == 'N')
            more = false;
    }
}

void pro_2() {
    Triangular tri(20, 12);
    Triangular::iterator it = tri.begin();
    Triangular::iterator end_it = tri.end();

    cout << "Triangular Series of " << tri.length() << " elements\n";

    cout << tri << endl;
//    while (it != end_it) {
//        cout << *it++ << ' ';
//    }
//    cout << endl;
}

void pro_3() {
    int ia[16] = {17, 12, 44, 9, 18, 45, 6, 14,
                  23, 67, 9, 0, 27, 55, 8, 16};
    vector<int> vec(ia, ia + 16);
    int comp_val = 20;

    cout << "Number of elements less than ";
    cout << comp_val << " are ";
    cout << count_less_than(vec, comp_val) << endl;
    print_less_than(vec, comp_val);
}

void pro_4() {
    Triangular tri(6, 3);
    cout << tri << endl;

    Triangular tri2;
    cout << "Please enter as the example (3, 5): ";
    cin >> tri2;
    cout << tri2 << endl;
}

void pro_5() {
    Triangular tri(10);
    Triangular::iterator it = tri.begin();
    Triangular::iterator end_it = tri.end();

    cout << "Triangular Series of " << tri.length() << " elements\n";
    cout << tri;

    cout << " -- sum of elements: "
         << sum(tri) << endl;

//    while (it != end_it) {
//        cout << *it << ' ';
//        ++it;
//    }
//    cout << endl;
}