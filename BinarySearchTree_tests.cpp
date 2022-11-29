// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
#include <sstream>

using namespace std;


TEST(test_stub) {
    // Add your tests here
    ASSERT_TRUE(true);
}

TEST(bst_public_test) {
    BinarySearchTree<int> tree;
    tree.insert(5);


  ASSERT_TRUE(tree.size() == 1);
  ASSERT_TRUE(tree.height() == 1);

  ASSERT_TRUE(tree.find(5) != tree.end());
  tree.insert(7);
  tree.insert(3);

  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_TRUE(*tree.max_element() == 7);
  ASSERT_TRUE(*tree.min_element() == 3);
  //ASSERT_TRUE(*tree.min_greater_than(5) == 7); //segfault

  cout << "cout << tree.to_string()" << endl;
  cout << tree.to_string() << endl << endl;

  cout << "cout << tree" << endl << "(uses iterators)" << endl;
  //cout << tree << endl << endl; //segfault

  ostringstream oss_preorder;
  tree.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  ASSERT_TRUE(oss_preorder.str() == "5 3 7 ");

  ostringstream oss_inorder;
  tree.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "3 5 7 ");
}

TEST(test_empty) {
    BinarySearchTree<int> i;
    ASSERT_TRUE(i.empty())
}

TEST(test_insert) {
    BinarySearchTree<int> i;
    i.insert(2);
    ASSERT_FALSE(i.empty());
}

TEST(test_size){
    BinarySearchTree<int> i;
    i.insert(1);
    i.insert(7);
    i.insert(5);
    ASSERT_EQUAL(i.size(), 3);
}

TEST(test_size_zero) {
    BinarySearchTree<int> i;
    ASSERT_EQUAL(i.size(), 0u);
}

TEST(test_height){
BinarySearchTree<int> i;
    i.insert(1);
    i.insert(7);
    i.insert(5);
    ASSERT_EQUAL(i.height(), 3u);
}

TEST(test_find){
    BinarySearchTree<int> i;
    ASSERT_EQUAL(i.find(7),i.end());
    i.insert(7);
    ASSERT_TRUE(i.find(7) != i.end());
    ASSERT_TRUE(i.find(77) == i.end());
    i.insert(5);
    i.insert(3);
    i.insert(6);
    i.insert(10);
    i.insert(8);
    ASSERT_TRUE(*i.find(8)==8);
    ASSERT_TRUE(*i.find(10)==10);
    ASSERT_TRUE(*i.find(6)==6);
    ASSERT_TRUE(*i.find(3)==3);
}

TEST(test_min_greater_than_impl){
    BinarySearchTree<int> i;
    i.insert(4);
    i.insert(8);
    i.insert(9);
    i.insert(7);
    i.insert(2);
    i.insert(1);
    i.insert(3);
    cout << "min_greater_than_test" << endl;
    cout << *i.min_greater_than(1);
    ASSERT_EQUAL(*i.min_greater_than(1), 2);
    ASSERT_EQUAL(*i.min_greater_than(2), 3);
    ASSERT_EQUAL(*i.min_greater_than(3), 4);
    ASSERT_EQUAL(*i.min_greater_than(4), 7);
    ASSERT_EQUAL(*i.min_greater_than(5), 7);
    ASSERT_EQUAL(*i.min_greater_than(7), 8);
    ASSERT_EQUAL(*i.min_greater_than(7), 9);
    //ASSERT_EQUAL(i.min_greater_than(9), i.end());
}

TEST_MAIN()
