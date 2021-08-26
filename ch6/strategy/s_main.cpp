//
// Created by LMH on 2021/8/22.
//

#include "s_main.h"

int main() {
    
    prog1();
    prog2();
    prog3();

    return 0;
}

void prog1() {
    const int pos = 8;

	num_sequence<Fibonacci> fib;
	display(cout, fib, pos);

	num_sequence<Pell> pell;
	display(cout, pell, pos);

	num_sequence<Lucas> lucas;
	display(cout, lucas, pos);

	num_sequence<Triangular> trian;
	display(cout, trian, pos);

	num_sequence<Square> square;
	display(cout, square, pos);

	num_sequence<Pentagonal> penta;
	display(cout, penta, pos);
}

void prog2() {
    num_sequence<Fibonacci> fib(1, 8);
	cout << "fib: " << fib.what_am_i() << endl;
	num_sequence<Pell> pell(4, 6);
	num_sequence<Lucas> lucas(7, 10);
	num_sequence<Triangular> trian(1, 12);
	num_sequence<Square> square(6, 6);
	num_sequence<Pentagonal> penta(1, 8);

	cout << "fib: " << fib << '\n'
		 << "pell: " << pell << '\n'
		 << "lucas: " << lucas << '\n'
		 << "trian: " << trian << '\n'
		 << "square: " << square << '\n'
		 << "penta: " << penta << endl;
}

template <typename seq_type>
void prog_3(seq_type ns, int elem_values) {
	int elem_val = 0;
	const int pos = 8;
	const int find_pos = 14;

	elem_val = ns.elem(pos);
	display(cout, ns, pos, elem_val);
	cout << ns.what_am_i() << " : ( "
		 << ns.beg_pos() << ", "
		 << ns.length() << " ) : "
		 << ns;
	cout << endl;

	ns.set_length(12);
	cout << ns << endl;

	cout << "num_sequence::is_elem() ";
	if (!ns.is_elem(elem_val) ||
		ns.is_elem(2 * elem_val))
		cout << "failed\n";
	else
		cout << "ok!\n";

	cout << "copy constructor and equality ";
	seq_type ns2 = ns;
	if (ns != ns2)
		cout << "failed!\n";
	else
		cout << "ok!\n";

	ns2.set_position(5);

	int posit = ns.pos_elem(elem_val);
	if (ns.pos_elem(elem_val) != pos)
		cout << "pos_elem() failed : " << posit << "\n";
	else
		cout << "pos_elem() -- ok: " << posit << "\n";

	posit = ns.pos_elem(elem_values);
	if (posit != find_pos)
		cout << "pos_elem(): not found but grown: failed: "
			 << posit << " correct: " << find_pos << "\n";
	else
		cout << "pos_elem(): not found but grown: ok\n";

	cout << "about to print final ns vector: \n";
	ns.print();
	cout << endl;

	cout << "ns2: should begin at position 5:\n"
		 << ns2 << endl;
}

void prog3() {
    int elem_values[] = {377, 80782, 843, 105, 196, 287};

	// for ( int ix = 0; ix < 6; ++ix ) // test all
	for (int ix = 0; ix < 1; ++ix) {  // test 1 at time
		switch (ix) {
		case 0: {
			num_sequence<Fibonacci> ns(1, 8);
			prog_3(ns, elem_values[ix]);
			break;
		}
		case 1: {
			num_sequence<Pell> ns(1, 8);
			prog_3(ns, elem_values[ix]);
			break;
		}
		case 2: {
			num_sequence<Lucas> ns(1, 8);
			prog_3(ns, elem_values[ix]);
			break;
		}
		case 3:
		{
			num_sequence<Triangular> ns(1, 8);
			prog_3(ns, elem_values[ix]);
			break;
		}
		case 4: {
			num_sequence<Square> ns(1, 8);
			prog_3(ns, elem_values[ix]);
			break;
		}
		case 5: {
			num_sequence<Pentagonal> ns(1, 8);
			prog_3(ns, elem_values[ix]);
			break;
		}
		default:
			return;
		}
	}
}