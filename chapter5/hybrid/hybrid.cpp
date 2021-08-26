//
// Created by LMH on 2021/8/17.
//

#include "hybrid.h"

int main() {

    prog1();
    prog2();
    prog3();

    return 0;
}

void prog1() {
    const int pos = 8;

    Fibonacci fib;
    display(cout, fib, pos);

    Pell pell;
    display(cout, pell, pos);

    Lucas lucas;
    display(cout, lucas, pos);

    Triangular trian;
    display(cout, trian, pos);

    Square square;
    display(cout, square, pos);

    Pentagonal penta;
    display(cout, penta, pos);
}

void prog2() {
    Fibonacci fib(1, 8);
    Pell pell(4, 6);
    Lucas lucas(7, 10);
    Triangular trian(1, 12);
    Square square(6, 6);
    Pentagonal penta(1, 8);

    cout << "fib: "     << fib    << '\n'
         << "pell: "    << pell   << '\n'
         << "lucas: "   << lucas  << '\n'
         << "trian: "   << trian  << '\n'
         << "square: "  << square << '\n'
         << "penta: "   << penta  << endl;
}

void prog3() {
    num_sequence *pns = nullptr;
    unsigned int elem_val;
    const int pos = 8;
    const int find_pos = 14;

    int elem_values[] = {377, 80782, 843, 105, 196, 287};
    // for ( int ix = 0; ix < 6; ++ix ) // test all
    for (int ix = 0; ix < 1; ++ix) // test 1 at time
    {
        // for testing, just ensure that we try
        // out each derived class instance ...

        switch (ix) {
            case 0:
                pns = new Fibonacci(1, 8);
                break;
            case 1:
                delete pns;
                pns = new Pell(1, 8);
                break;
            case 2:
                delete pns;
                pns = new Lucas(1, 8);
                break;
            case 3:
                delete pns;
                pns = new Triangular(1, 8);
                break;
            case 4:
                delete pns;
                pns = new Square(1, 8);
                break;
            case 5:
                delete pns;
                pns = new Pentagonal(1, 8);
                break;
            default:
                delete pns;
                return;
        }

        elem_val = pns->elem(pos);
        display(cout, *pns, pos, elem_val);
        cout << pns->what_am_i() << " : ( "
             << pns->beg_pos() << ", "
             << pns->length() << " ) : "
             << *pns;
        cout << endl;

        pns->set_length(12);
        cout << *pns << endl;

        cout << "num_sequence::is_elem() ";
        if (!pns->is_elem(elem_val) ||
            pns->is_elem(2 * elem_val))
            cout << "failed\n";
        else
            cout << "ok!\n";

        cout << "copy constructor and equality ";
        num_sequence *pns2 = pns->clone();
        if (*pns != *pns2)
            cout << "failed!\n";
        else
            cout << "ok!\n";

        pns2->set_position(5);

        int posit = pns->pos_elem(elem_val);
        if (pns->pos_elem(elem_val) != pos)
            cout << "pos_elem() failed : " << posit << "\n";
        else
            cout << "pos_elem() -- ok: " << posit << "\n";

        posit = pns->pos_elem(elem_values[ix]);
        if (posit != find_pos)
            cout << "pos_elem(): not found but grown: failed: "
                 << posit << " correct: " << find_pos << "\n";
        else
            cout << "pos_elem(): not found but grown: ok\n";

        cout << "about to print final ns vector: \n";
        pns->print();
        cout << endl;

        cout << "ns2: should begin at position 5:\n"
             << *pns2 << endl;
    }
}