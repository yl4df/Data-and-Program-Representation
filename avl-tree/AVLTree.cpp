//Yunlu Li, yl4df, 2019-10-16, AVLTree.cpp
#include "AVLTree.h"
#include <string>
#include <iostream>
#include "AVLNode.h"
using namespace std;

AVLTree::AVLTree() { root = NULL; }

AVLTree::~AVLTree() {
  delete root;
  root = NULL;
}

// insert finds a position for x in the tree and places it there, rebalancing
// as necessary.
void AVLTree::insert(const string& x) {
  root=insert(root,x);
}

// remove finds x's position in the tree and removes it, rebalancing as
// necessary.
void AVLTree::remove(const string& x) { root = remove(root, x); }

// pathTo finds x in the tree and returns a string representing the path it
// took to get there.
string AVLTree::pathTo(const string& x) const {
  return pathTo_node(root,x);
}

// find determines whether or not x exists in the tree.
bool AVLTree::find(const string& x) const {
  return find_node(root,x);
}

// numNodes returns the total number of nodes in the tree.
int AVLTree::numNodes() const {
  return numNodes_node(root);
}

// balance makes sure that the subtree with root n maintains the AVL tree
// property, namely that the balance factor of n is either -1, 0, or 1.
void AVLTree::balance(AVLNode*& n) {
  if((height(n->right)-height(n->left))==2){
    if((height(n->right->right)-height(n->right->left))<0){
      n->right = rotateRight(n->right);
    }
    n=rotateLeft(n);
  }
  else if((height(n->right)-height(n->left))==-2){
    if((height(n->left->right)-height(n->left->left))>0){
     n->left = rotateLeft(n->left);
    }
    n=rotateRight(n);
  }
}

// rotateLeft performs a single rotation on node n with its right child.
AVLNode* AVLTree::rotateLeft(AVLNode*& n) {
  AVLNode* n_sub_r = n->right;
  AVLNode* n_sub_r_l = n_sub_r->left;
  n_sub_r->left = n;
  n->right = n_sub_r_l;
  n->height = max(height(n->left),     
                    height(n->right)) + 1;  
  n_sub_r->height = max(height(n_sub_r->left),  
                    height(n_sub_r->right)) + 1;
  return n_sub_r;
}

// rotateRight performs a single rotation on node n with its left child.
AVLNode* AVLTree::rotateRight(AVLNode*& n) {
  AVLNode* n_sub_l = n->left;
  AVLNode* n_sub_l_r = n_sub_l->right;
  n_sub_l->right = n;
  n->left = n_sub_l_r;
  n->height = max(height(n->left),     
                    height(n->right)) + 1;  
  n_sub_l->height = max(height(n_sub_l->left),  
                    height(n_sub_l->right)) + 1;
  return n_sub_l;
}

// private helper for remove to allow recursion over different nodes. returns
// an AVLNode* that is assigned to the original node.
AVLNode* AVLTree::remove(AVLNode*& n, const string& x) {
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
      AVLNode* temp = n->right;
      n->right = NULL;
      delete n;
      n = NULL;
      return temp;
    }
    if (n->right == NULL) {
      AVLNode* temp = n->left;
      n->left = NULL;
      delete n;
      n = NULL;
      return temp;
    }
    // two children -- tree may become unbalanced after deleting n
    string sr = min(n->right);
    n->value = sr;
    n->right = remove(n->right, sr);
  } else if (x < n->value) {
    n->left = remove(n->left, x);
  } else {
    n->right = remove(n->right, x);
  }
  n->height = 1 + max(height(n->left), height(n->right));
  balance(n);
  return n;
}

AVLNode* AVLTree::insert(AVLNode*& n, const string& x){
  if( n == NULL) {
    n = new AVLNode();
    n->value = x;
  }
  else if (x < n->value){
    n->left = insert(n->left, x);
  }
  else if (x > n->value){
    n->right = insert(n->right, x);
  }
  n->height = 1 + max(height(n->left), height(n->right));
  balance(n);
  return n;
}


//private helper function for pathTo to allow recursion over different nodes.
// returns a string path from the node provided to the node that we find.
string AVLTree::pathTo_node(AVLNode* n, const string& x) const{
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
    return "";
  }
 
}

//private helper function for find to allow recursion over different nodes.
//returns true if x is founded in the tree rooted at n and false otherwise.
bool AVLTree::find_node(AVLNode* n, const string& x) const {
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
int AVLTree::numNodes_node(AVLNode* n) const {
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
string AVLTree::min(AVLNode* node) const {
  // go to bottom-left node
  if (node->left == NULL) {
    return node->value;
  }
  return min(node->left);
}

// height returns the value of the height field in a node. If the node is
// null, it returns -1.
int AVLTree::height(AVLNode* node) const {
  if (node == NULL) {
    return -1;
  }
  return node->height;
}

// max returns the greater of two integers.
int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

// Helper function to print branches of the binary tree
void showTrunks(Trunk* p) {
  if (p == nullptr) return;
  showTrunks(p->prev);
  cout << p->str;
}

// Recursive function to print binary tree
// It uses inorder traversal
void AVLTree::printTree(AVLNode* root, Trunk* prev, bool isLeft) {
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

void AVLTree::printTree() { printTree(root, NULL, false); }
