//Yunlu Li, yl4df, 2019-10-14, BinarySearchTree.cpp
#include "BinarySearchTree.h"
#include <string>
#include <iostream>
#include "BinaryNode.h"
using namespace std;

BinarySearchTree::BinarySearchTree() { root = NULL; }

BinarySearchTree::~BinarySearchTree() {
  delete root;
  root = NULL;
}

// insert finds a position for x in the tree and places it there.
void BinarySearchTree::insert(const string& x) {
  root = insert(root, x); 
}

// remove finds x's position in the tree and removes it.
void BinarySearchTree::remove(const string& x) { root = remove(root, x); }

// pathTo finds x in the tree and returns a string representing the path it
// took to get there.
string BinarySearchTree::pathTo(const string& x) const {
   return pathTo_node(root, x);
 
}

// find determines whether or not x exists in the tree.
bool BinarySearchTree::find(const string& x) const {
  return find_node(root, x);
}

// numNodes returns the total number of nodes in the tree.
int BinarySearchTree::numNodes() const {
  return numNodes_node(root);
}

// private helper for remove to allow recursion over different nodes. returns
// a BinaryNode* that is assigned to the original node.
BinaryNode* BinarySearchTree::remove(BinaryNode*& n, const string& x) {
  if (n == NULL) {
    return NULL;
  }
  // first look for x
  if (x == n->value) {
    // found
    // no children
    if (n->left == NULL && n->right == NULL) {
      delete n;
      n = NULL;
      return NULL;
    }
    // single child
    if (n->left == NULL) {
      BinaryNode* temp = n->right;
      n->right = NULL;
      delete n;
      n = NULL;
      return temp;
    }
    if (n->right == NULL) {
      BinaryNode* temp = n->left;
      n->left = NULL;
      delete n;
      n = NULL;
      return temp;
    }
    // two children
    string sr = min(n->right);
    n->value = sr;
    n->right = remove(n->right, sr);
  } else if (x < n->value) {
    n->left = remove(n->left, x);
  } else {
    n->right = remove(n->right, x);
  }
  return n;
}

// private helper for insert to allow recursion over different nodes.
// returns a BinaryNode* that is assigned to the original node.
BinaryNode* BinarySearchTree::insert(BinaryNode*& n, const string& x){
  if( n == NULL) {
    n = new BinaryNode();
    n->value = x;
  }
  else if (x < n->value){
    n->left = insert(n->left, x);
  }
  else if (x > n->value){
    n->right = insert(n->right, x);
  }
  return n;
}

//private helper function for pathTo to allow recursion over different nodes.
// returns a string path from the node provided to the node that we find.
string BinarySearchTree::pathTo_node(BinaryNode* n, const string& x) const{
  string path = "";
  if(find_node(n,x)==true){
    if(x==n->value){
      path = path + n->value;
  }
    else if (x<n->value){
      path = n->value + " " + pathTo_node(n->left, x);
  }
    else if (x>n->value){
      path = n->value + " " + pathTo_node(n->right, x);
  }
    return path;
  }
  else{
    return "";}
 
}

//private helper function for find to allow recursion over different nodes.
//returns true if x is founded in the tree rooted at n and false otherwise.
bool BinarySearchTree::find_node(BinaryNode* n, const string& x) const {
  if(x == n -> value){
    return true;
  }
  else if ( x < n->value){
    if(n->left==NULL){
      return false;
    }else{
    return find_node(n->left, x);
    }
  }
  else if ( x > n->value){
    if(n->right==NULL){
      return false;
    }else{
    return find_node(n->right, x);
    }
  }
  return false; 
}

//private helper function for numNodes to allow recursion over different nodes.
// returns int for the number of nodes in the tree rooted at n.
int BinarySearchTree::numNodes_node(BinaryNode* n) const {
  int num = 1;
  if(n==NULL){
    return 0;
  }
  if(n->left){
   num = numNodes_node(n->left) + num;
  }
  if(n->right){
   num = numNodes_node(n->right) + num;
  }
  return num;
}

// min finds the string with the smallest value in a subtree.
string BinarySearchTree::min(BinaryNode* node) const {
  // go to bottom-left node
  if (node->left == NULL) {
    return node->value;
  }
  return min(node->left);
}

// Helper function to print branches of the binary tree
void showTrunks(Trunk* p) {
  if (p == nullptr) return;
  showTrunks(p->prev);
  cout << p->str;
}

// Recursive function to print binary tree
// It uses inorder traversal
void BinarySearchTree::printTree(BinaryNode* root, Trunk* prev, bool isLeft) {
  if (root == NULL) return;

  string prev_str = "    ";
  Trunk* trunk = new Trunk(prev, prev_str);

  printTree(root->left, trunk, true);

  if (!prev)
    trunk->str = "---";
  else if (isLeft) {
    trunk->str = ".---";
    prev_str = "   |";
  } else {
    trunk->str = "`---";
    prev->str = prev_str;
  }

  showTrunks(trunk);
  cout << root->value << endl;

  if (prev) prev->str = prev_str;
  trunk->str = "   |";

  printTree(root->right, trunk, false);
}

void BinarySearchTree::printTree() { printTree(root, NULL, false); }
