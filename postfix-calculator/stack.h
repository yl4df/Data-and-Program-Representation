//Yunlu Li, yl4df, stack.h, 2019-09-18

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "List.h"
#include "ListItr.h"
#include "ListNode.h"

using namespace std;

class Stack{
 public:
  Stack();
  void push(int e);
  int top();
  void pop();
  bool empty();
 private:
  List myList;
  int count;
};
  

#endif
