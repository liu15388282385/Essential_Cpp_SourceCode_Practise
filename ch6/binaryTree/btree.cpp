//
// Created by LMH on 2021/8/22.
//

#include "btree.h"

int main() {
    
    // vector<int>
    ofstream log1("log.txt");
    if (!log1) {
        cerr << "error: unable to open log.txt!\n";
        return -1;
    }
    else {
        BinaryTree<int>::current_os(&log1);
    }
    int ia[] = { 24, 18, 36, 12, 14, 8, 24, 1, 42, 24, 8, 8, 16, 55 };
    vector< int > ivec( ia, ia + 14 );
    BinaryTree<int> bt( ivec );

    log1 << "preorder traversal: \n";
    // cout << should see\n\t ";
    bt.preorder( log1 );
    log1 << endl;
    
    bt.clear();
    log1 << "\nbt is now " << ( bt.empty() ? " empty! " : " oops -- not empty!" ) << endl;

    sort( ivec.begin(), ivec.end() );
    bt.insert( ivec );

    log1 << "\n\ninorder traversal:\n";
    bt.inorder( log1 );

    bt.insert( ivec );
    
    log1 << "\n\npostorder traversal:\n";
    bt.postorder(log1);
    log1 << endl << endl;
    
    // string
    ofstream log2("logfile.txt");
    if (!log2) {
        cerr << "error: unable to open logfile.txt!\n";
        return -1;
    }
    else
        BinaryTree<string>::current_os(&log2);
    BinaryTree<string> bt1;
    bt1.insert("Piglet");
    bt1.insert("Eeyore");
    bt1.insert("Roo");
    bt1.insert("Tigger");
    bt1.insert("Chris");
    bt1.insert("Pooh");
    bt1.insert("Kanga");

    log2 << "Preorder traversal: \n";
    bt.preorder(log2);

    bt1.remove("Piglet");
    log2 << "\n\nPreorder traversal after Piglet removal: \n";
    bt1.preorder(log2);

    bt1.remove("Eeyore");
    log2 << "\n\nPreorder traversal after Eeyore removal: \n";
    bt1.preorder(log2);

    log2 << "\n\ninorder traversal:\n";
    bt1.inorder(log2);

    log2 << "\n\npostorder traversal:\n";
    bt1.postorder(log2); 
    
    return 0;
}