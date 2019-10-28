// Yunlu Li, yl4df, 2019-10-13, TreeCalc.cpp
// TreeCalc.cpp:  CS 2150 Tree Calculator method implementations

#include "TreeCalc.h"
#include <iostream>
#include <cstdlib>

using namespace std;

//Constructor
TreeCalc::TreeCalc() {
  stack<TreeNode*> mystack;
}

//Destructor- frees memory
TreeCalc::~TreeCalc() {
  cleanTree(mystack.top());
}

//Deletes tree/frees memory
void TreeCalc::cleanTree(TreeNode* ptr) {
  delete ptr;
  if(ptr->left){
    cleanTree(ptr->left);
  }
  if(ptr->right){
    cleanTree(ptr->right);
  }   
}

//Gets data from user
void TreeCalc::readInput() {
    string response;
    cout << "Enter elements one by one in postfix notation" << endl
         << "Any non-numeric or non-operator character,"
         << " e.g. #, will terminate input" << endl;
    cout << "Enter first element: ";
    cin >> response;
    //while input is legal
    while (isdigit(response[0]) || response[0]=='/' || response[0]=='*'
            || response[0]=='-' || response[0]=='+' ) {
        insert(response);
        cout << "Enter next element: ";
        cin >> response;
    }
}

//Puts value in tree stack
void TreeCalc::insert(const string& val) {
    // insert a value into the tree
  TreeNode *toInsert = new TreeNode(val);
  if (val == "+" || val == "-" || val == "*" || val == "/"){
    toInsert -> right = mystack.top();
    mystack.pop();
    toInsert -> left = mystack.top();
    mystack.pop();
    mystack.push(toInsert);
  }
  else{
    mystack.push(toInsert);
  }
}


//Prints data in prefix form
void TreeCalc::printPrefix(TreeNode* curNode) const {
    // print the tree in prefix format
  cout << curNode->value << " ";
  if (curNode->left){
    printPrefix(curNode->left);
    }
  if (curNode->right){
    printPrefix(curNode->right);
    }
}

//Prints data in infix form
void TreeCalc::printInfix(TreeNode* curNode) const {
    // print tree in infix format with appropriate parentheses
  if(curNode->left){
    cout<<"(";
    printInfix(curNode->left);
  }
  cout << " " << curNode->value << " ";
  if(curNode->right){
    printInfix(curNode->right);
    cout<<")";
  }
}

//Prints data in postfix form
void TreeCalc::printPostfix(TreeNode* curNode) const {
    // print the tree in postfix form
  if (curNode->left){
      printPostfix(curNode->left);
    }
  if (curNode->right){
      printPostfix(curNode->right);
    }
    cout << curNode->value << " ";
}
 

// Prints tree in all 3 (pre,in,post) forms

void TreeCalc::printOutput() const {
    if (mystack.size()!=0 && mystack.top()!=NULL) {
        cout << "Expression tree in postfix expression: ";
        // call your implementation of printPostfix()
	printPostfix(mystack.top());
        cout << endl;
        cout << "Expression tree in infix expression: ";
        // call your implementation of printInfix()
	printInfix(mystack.top());
        cout << endl;
        cout << "Expression tree in prefix expression: ";
        // call your implementation of printPrefix()
	printPrefix(mystack.top());
        cout << endl;
    } else
        cout<< "Size is 0." << endl;
}

//Evaluates tree, returns value
// private calculate() method
int TreeCalc::calculate(TreeNode* ptr) const {
    // Traverse the tree and calculates the result
  string val = ptr -> value;
  if ( val == "+"){
    return (calculate(ptr->left)+calculate(ptr->right));
    }
    
  else if ( val == "-"){
    return (calculate(ptr->left)-calculate(ptr->right));
    }

  else if ( val == "*"){
    return (calculate(ptr->left)*calculate(ptr->right));
    }
        
  else if ( val == "/"){
    return (calculate(ptr->left)/calculate(ptr->right));
    }
  else return atoi(val.c_str()); 
}

//Calls calculate, sets the stack back to a blank stack
// public calculate() method. Hides private data from user
int TreeCalc::calculate() {
    int i = 0;
    i = calculate(mystack.top());// call private calculate method here
    return i;
}
