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
  cout << *tree.min_greater_than(5) << endl;
  ASSERT_TRUE(*tree.min_greater_than(5) == 7);

  cout << "cout << tree.to_string()" << endl;
  cout << tree.to_string() << endl << endl;

  cout << "cout << tree" << endl << "(uses iterators)" << endl;
  cout << tree << endl << endl; 

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
    i.insert(3);//insert right
    i.insert(1);//insert left
    ASSERT_TRUE(i.size()==3);
    ASSERT_TRUE(i.height()==2);
}

TEST(test_size){
    BinarySearchTree<int> i;
    ASSERT_EQUAL(i.size(), 0);
    i.insert(1);
    i.insert(7);
    i.insert(5);
    ASSERT_EQUAL(i.size(), 3);
}

TEST(test_size_zero) {
    BinarySearchTree<int> i;
    ASSERT_EQUAL(i.size(), 0);
}

TEST(test_height){
    BinarySearchTree<int> i;
    ASSERT_EQUAL(i.height(), 0);
    i.insert(1);
    i.insert(7);
    i.insert(5);
    ASSERT_EQUAL(i.height(), 3);
}

TEST(test_constructor){
    BinarySearchTree<int> i;
    i.insert(10);
    i.insert(5);
    i.insert(2);
    i.insert(8);
    i.insert(9);
    i.insert(15);
    BinarySearchTree<int> j = i;
    ASSERT_FALSE(i.begin()==j.begin());
    ASSERT_TRUE(i.begin()!=j.begin());
    BinarySearchTree<int>::Iterator itr_i = i.begin();
    ASSERT_EQUAL(j.min_greater_than(20), j.end());
    ASSERT_EQUAL(*j.min_greater_than(7), 8);
    ASSERT_EQUAL(j.height(), 4);
    ASSERT_EQUAL(j.size(), 6);
    ++*itr_i;
    ASSERT_EQUAL(*i.min_element(), 3);
    ASSERT_EQUAL(*j.min_element(), 2); //deep copy
    itr_i++;
    --*itr_i; 
    ASSERT_EQUAL(i.find(5), i.end());
    ASSERT_EQUAL(*i.find(4), 4);
    ASSERT_EQUAL(j.find(6), j.end()); //deep copy
    j = i;
    ASSERT_EQUAL(*j.find(4), 4); //assignment
    ASSERT_EQUAL(j.find(5), j.end());
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

TEST(test_min_greater_than_impl_1){
    BinarySearchTree<int> i;
    i.insert(4);
    i.insert(8);
    i.insert(9);
    i.insert(7);
    i.insert(2);
    i.insert(1);
    i.insert(3);
    cout << i.to_string() << endl; 
    ASSERT_EQUAL(*i.min_greater_than(1), 2);
    ASSERT_EQUAL(*i.min_greater_than(2), 3);
    ASSERT_EQUAL(*i.min_greater_than(3), 4);
    ASSERT_EQUAL(*i.min_greater_than(4), 7);
    ASSERT_EQUAL(*i.min_greater_than(5), 7);
    ASSERT_EQUAL(*i.min_greater_than(7), 8);
    ASSERT_EQUAL(*i.min_greater_than(8), 9);
    ASSERT_EQUAL(i.min_greater_than(9), i.end());
}

TEST(test_min_greater_than_impl_2){
    BinarySearchTree<int> i;
    ASSERT_EQUAL(i.min_greater_than(1), i.end());
    i.insert(10);
    i.insert(5);
    i.insert(2);
    i.insert(8);
    i.insert(9);
    i.insert(15);
    cout << i.to_string() << endl; 
    ASSERT_EQUAL(i.min_greater_than(20), i.end());
    ASSERT_EQUAL(*i.min_greater_than(7), 8);
    ASSERT_EQUAL(*i.min_greater_than(2), 5);
    ASSERT_EQUAL(*i.min_greater_than(13), 15);
    ASSERT_EQUAL(*i.min_greater_than(3), 5);
}

TEST(test_star){
    BinarySearchTree<int> i;
    BinarySearchTree<int>::Iterator itr = i.begin();
    i.insert(7);
    i.insert(9);
    i.insert(134);
    i.insert(55);
    i.insert(3);
    itr = i.begin();

    ASSERT_TRUE(*itr == 3);
}

TEST(test_plus_pre){
    BinarySearchTree<int> i;
    BinarySearchTree<int>::Iterator itr = i.begin();
    i.insert(4);
    i.insert(8);
    i.insert(12);
    i.insert(2);
    i.insert(6);
    itr = i.begin();

    ASSERT_TRUE(++*itr == 3);
}
/*
TEST(test_breaking){
    BinarySearchTree<int> i;
    i.insert(3);
    i.insert(2);
    BinarySearchTree<int>::Iterator itr = i.begin();
    ++*itr;
    ASSERT_EQUAL(*itr, 3);
    cout << i.to_string() << endl; 

}*/

TEST_MAIN()
