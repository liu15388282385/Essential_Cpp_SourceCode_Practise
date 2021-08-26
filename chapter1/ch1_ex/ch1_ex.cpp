//
// Created by LMH on 2021/8/24.
//

#include "ch1_ex.h"

int main() {
    
//    ex1_extra1();
//    ex1_extra2();
    ex1_5_string();
    ex1_5_cstyle();
    ex1_6_vector();
    ex1_6_array();
    int rev_val = ex1_7();

    return rev_val; 
}

void ex1_extra1() {
    vector<string *> sp_vec;
    string st;

    cout << "Please enter a series of strings\n";
    while (cin >> st)
        sp_vec.push_back(new string(st));

    auto iter = sp_vec.begin(),
            it_end = sp_vec.end();

    cout << endl;
    cout << "This is what you entered, no?\n";

    for (int items = 1; iter != it_end; ++items, ++iter) {
        if (!(items % 8))
            // print a newline every 8th item
            cout << '\n';

        // *iter returns a string*; (*(*iter)) yields string
        cout << (*(*iter)) << ' ';
        delete *iter;
    }
    cout << endl;
}

void ex1_extra2() {
    string file_name;
    cout << "Please enter a file to be opened: (try input.txt or text.txt) ";
    cin >> file_name;
    if (!cin || file_name.empty()) {
        cerr << "oops! unable to read file name\n";
        return;
    }

    ifstream ifile(file_name.c_str());

    if (!ifile) {
        cerr << "oops! unable to open input file: "
             << file_name << endl;
        return;
    } else
        cerr << "!! ok: opened " << file_name << " for input\n";

    file_name += ".sort";
    ofstream ofile(file_name.c_str());

    if (!ofile) {
        cerr << "oops! unable to open output file: "
             << file_name << endl;
        return;
    } else
        cerr << "!! ok: opened " << file_name << " for output\n";

    string word;
    vector<string> text;
    while (ifile >> word)
        text.push_back(word);

    if (text.empty()) {
        cerr << "bummer! input file is empty: bailing out\n";
        return;
    } else
        cerr << "!! ok: read " << text.size() << " strings from input\n";

    sort(text.begin(), text.end());

    unsigned int cnt = 0;
    for (auto & iter : text) {
        cnt += iter.size() + 1;
        if (cnt > 40) {
            ofile << '\n';
            cnt = 0;
        }
        ofile << iter << ' ';
    }

    cerr << "ok: wrote sorted strings into " << file_name << endl;
}

int ex1_5_string() {
    string user_name;

    cout << "Please enter your name: ";
    cin >> user_name;

    switch (user_name.size()) {
        case 0:
            cout << "Ah, the user with no name. "
                 << "Well, ok, hi, user with no name\n";
            break;

        case 1:
            cout << "A 1-character name? Hmm, have you read Kafka?: "
                 << "hello, " << user_name << endl;
            break;

        default:
            // any string longer than 1 character
            cout << "Hello, " << user_name
                 << " -- happy to make your acquaintance!\n";
            break;
    }
    return 0;
}

int ex1_5_cstyle() {
    // must allocate a fixed size
    const int nm_size = 128;
    char user_name[nm_size];

    cout << "Please enter your name: ";
    cin >> setw(nm_size) >> user_name;

    switch (strlen(user_name)) {
        // case labels the same for 0, 1
        case 127:
            // maybe string was truncated by setw()
            cout << "That is a very big name, indeed -- "
                 << "we may have needed to shorten it!\n"
                 << "In any case,\n";
            // no break -- we fall through ...
        default:
            // the 127 case drops through to here -- no break
            cout << "Hello, " << user_name
                 << " -- happy to make your acquaintance!\n";
            break;
    }
    return 0;
}

void ex1_6_vector() {
    vector<int> ivec;
    int ival;

    while (cin >> ival)
        ivec.push_back(ival);

    // we could have calculated the sum as we entered the
    // values, but the idea is to iterate over the vector ...
    int sum = 0;
    for (int ix = 0; ix < ivec.size(); ++ix) {
        cout << endl
             << ix << ") " << ivec[ix];
        sum += ivec[ix];
    }

    unsigned int average = sum / ivec.size();
    cout << "Sum of " << ivec.size()
         << " elements: " << sum
         << ". Average: " << average << endl;
}

void ex1_6_array() {
    const int arr_size = 128;
    int ia[arr_size];
    int ival, icnt = 0;

    while (cin >> ival && icnt < arr_size)
        ia[icnt++] = ival;

    // icnt is 1 greater than number of elements!
    int sum = 0;
    for (int ix = 0; ix < icnt; ++ix)
        sum += ia[ix];

    int average = sum / icnt;
    cout << endl
         << "Sum of " << icnt
         << " elements: " << sum
         << ". Average: " << average << endl;
}

int ex1_7() {
    ifstream in_file("text.txt");
    if (!in_file) {
        cerr << "oops! unable to open input file\n";
        return -1;
    }

    ofstream out_file("text.sort");
    if (!out_file) {
        cerr << "oops! unable to open output file\n";
        return -2;
    }

    string word;
    vector<string> text;
    while (in_file >> word)
        text.push_back(word);

    int ix;
    cout << "unsorted text: \n";
    for (ix = 0; ix < text.size(); ++ix)
        cout << text[ix] << ' ';
    cout << endl;

    sort(text.begin(), text.end());

    out_file << "sorted text: \n";
    for (ix = 0; ix < text.size(); ++ix)
        out_file << text[ix] << ' ';
    out_file << endl;

    return 0;
}