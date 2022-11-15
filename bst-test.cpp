#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
  /*BinarySearchTree<int,int> testTree;

  testTree.insert(std::make_pair(2, 6));
  testTree.insert(std::make_pair(1, 9));
    testTree.insert(std::make_pair(0, 8));

  cout << "Binary Search Tree contents:" << endl;
  for(BinarySearchTree<int,int>::iterator it = testTree.begin(); it != testTree.end(); ++it) {
      cout << it->first << " " << it->second << endl;
  }

  BinarySearchTree<int, double> bst;
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(1, 1.0));
	bst.insert(std::make_pair(3, 1.0));
	bst.remove(2);*/

	/*BinarySearchTree<int, double> bst;
	bst.insert(std::make_pair(5, 1.0));
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(6, 1.0));
	bst.insert(std::make_pair(4, 1.0));

	bst.remove(5);
  bst.remove(2);
  bst.remove(6);
  bst.remove(4);

  cout << "Binary Search Tree contents:" << endl;
  for(BinarySearchTree<int,double>::iterator it = bst.begin(); it != bst.end(); ++it) {
      cout << it->first << " " << it->second << endl;
  }*/

    // Binary Search Tree tests
    /*BinarySearchTree<char,int> bt;
    bt.insert(std::make_pair('a',1));
    bt.insert(std::make_pair('b',2));
    
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
    if(bt.find('a') != bt.end()) {
        cout << "Found a" << endl;
    }
    else {
        cout << "Did not find a" << endl;
    }
    cout << "Erasing b" << endl;
    bt.remove('b');*/

    // AVL Tree Tests
    /*AVLTree<char,int> at;
    at.insert(std::make_pair('a',1));
    at.insert(std::make_pair('b',2));

    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }*/

    /*AVLTree<uint16_t, uint16_t> testTree;

    auto p1 = std::make_pair(2, 9);
    auto p2 = std::make_pair(1, 8);
    auto p3 = std::make_pair(0, 159);

    testTree.insert(p1);
    testTree.insert(p3);
    testTree.insert(p2);*/

	  /*testTree.insert(std::make_pair(2, 9));
	  testTree.insert(std::make_pair(1, 8));
	  testTree.insert(std::make_pair(0, 159));*/

    /*for(AVLTree<uint16_t,uint16_t>::iterator it = testTree.begin(); it != testTree.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }*/
    //cout << "Erasing b" << endl;
    //at.remove('b');

    AVLTree<int, double> bst;
	bst.insert(std::make_pair(3, 1.0));
	bst.insert(std::make_pair(4, 1.0));
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(1, 1.0));
	bst.remove(4);

    return 0;
}
