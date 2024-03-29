#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    /*
    // Binary Search Tree tests
    BinarySearchTree<char,int> bt;
    bt.insert(std::make_pair('b',2));
    bt.insert(std::make_pair('a',1));
    bt.insert(std::make_pair('c',4));
    //bt.insert(std::make_pair('d',0));

    BinarySearchTree<int, double> bst;
    bst.insert(std::make_pair(2, 1.0));
    bst.insert(std::make_pair(1, 1.0));
    bst.insert(std::make_pair(3, 1.0));
    bst.remove(2);

    
    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }

    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    bt.remove('b');

    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    */
    // AVL Tree Tests
    AVLTree<string,string> at;
    at.insert(std::make_pair("Hello World","!!!"));
    at.insert(std::make_pair("pepp", "..."));

    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<string,string>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(at.find("Hello World") != at.end()) {
        cout << "Found Hello World" << endl;
    }
    else {
        cout << "Did not find Hello World" << endl;
    }
    cout << "Erasing Hello World" << endl;
    at.remove("Hello World");

    int8_t br = 1;
    cout << br << endl;

    return 0;
}
