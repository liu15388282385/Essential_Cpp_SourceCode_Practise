//
// Created by LMH on 2021/8/22.
//

#include "btree.h"

int main() {
    
    // int
    ofstream log1("log.txt");
    if (!log1) {
        cerr << "error: unable to open log.txt!\n";
        return -1;
    } else
        BinaryTree<int>::current_os(&log1);

	int ia[] = { 24, 18, 36, 12, 14, 8, 24, 1, 42, 24, 8, 8, 16, 55 };
	vector< int > ivec( ia, ia + 14 );
	BinaryTree<int> bt1( ivec );

	log1 << "\npreorder traversal: \n";
    // cout << should see\n\t ";
	bt1.preorder(log1);

	bt1.clear();
	log1 << "\n\nbt is now " << ( bt1.empty() ? " empty! " : " oops -- not empty!" ) << endl;

	sort( ivec.begin(), ivec.end() );
	bt1.insert( ivec );

	log1 << "\n\ninorder traversal:\n";
	bt1.inorder(log1);
	log1 << endl << endl;

	bt1.insert(ivec);
	
	log1 << "\n\npostorder traversal:\n";
	bt1.postorder(log1);

	log1 << endl;
	
	// string
    ofstream log2("logfile.txt");
    if (!log2) {
        cerr << "error: unable to open logfile.txt!\n";
        return -1;
    } else
        BinaryTree<string>::current_os(&log2);
    BinaryTree<string> bt2;
    bt2.insert("Piglet");
    bt2.insert("Eeyore");
    bt2.insert("Roo");
    bt2.insert("Tigger");
    bt2.insert("Chris");
    bt2.insert("Pooh");
    bt2.insert("Kanga");

    log2 << "preorder traversal: \n";
    bt2.preorder(log2);

    log2 << "\n\nabout to remove root: Piglet\n";
    bt2.remove("Piglet");

    log2 << "\n\npreorder traversal after Piglet removal: \n";
    bt2.preorder(log2);

    log2 << "\n\nabout to remove Eeyore\n";
    bt2.remove("Eeyore");

    log2 << "\n\npreorder traversal after Piglet removal: \n";
    bt2.preorder(log2);

    log2 << "\n\ninorder traversal:\n";
    bt2.inorder(log2);

    log2 << "\n\npostorder traversal:\n";
    bt2.postorder(log2);

    if (bt2.find("Chris")) {
        log2 << "\n\nFound the Chris!\n";
    }

    return 0;
}