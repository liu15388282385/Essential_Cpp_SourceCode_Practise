//
// Created by 刘民皓 on 2021/7/18.
//

#include "Ex1_7.h"

/**
 * 在源文件Practise1.7.cpp所在目录下创建一个文本文件text.txt
 * 内容如下:
 * We were her pride of ten she named us:
 * Phoenix, the Prodigal, Benjamin and perspicacious, pacific Suzanne.
*/



int main()
{
    /*Chapter_1 练习1-7*/
    cout << "<Exercise 1-7>\n";
    ifstream in_file( "text.txt" );
    if ( !in_file ) {
        cerr << "Unable to open input file\n";
        return -1;
    }

    ofstream out_file( "text_sorted.txt" );
    if ( !out_file ) {
        cerr << "Unable to open output file\n";
        return -2;
    }

    vector<string> vec;
    string word;
    while ( in_file >> word ) {
        vec.push_back( word );
    }

    cout << "Unsorted file: \n";
    for (auto & ix : vec) {
        cout << ix << ' ';
    }
    cout << endl;

    sort( vec.begin(), vec.end() );
    cout << "Sorted file: \n";
    for (auto & ix : vec) {
        cout << ix << ' ';  out_file << ix << ' ';
    }
    cout << endl;   out_file << endl;

    return 0;
}