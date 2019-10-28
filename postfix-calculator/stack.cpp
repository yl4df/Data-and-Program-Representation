//Yunlu Li, yl4df, stack.cpp, 2019-09-18

#include <iostream>
#include "stack.h"

using namespace std;

Stack::Stack(){
  List myList;
  count = myList.size();
}

void Stack::push(int e){
  ListItr first = myList.first();
  myList.insertBefore(e,first);
}

int Stack::top(){
  if(!empty()){
    int top = myList.first().retrieve();
    return top;
  }
  else{
    cout << "Error: The stack is empty!";
    exit(-1);
  }
}

void Stack::pop(){
  if(!empty()){
    ListItr first = myList.first();
    myList.remove(first.retrieve());
  }
  else{
    cout << "Error: The stack is empty!";
    exit(-1);
  }
}

bool Stack::empty(){
  return myList.isEmpty();
}

