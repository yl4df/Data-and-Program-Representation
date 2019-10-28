//Yunlu Li, yl4df, postfixCalculator.cpp, 2019-09-13

#include "postfixCalculator.h"
#include "stack.h"
#include <iostream>

using namespace std;

PostfixCalculator::PostfixCalculator(){
  Stack myStack; 
}


void PostfixCalculator::pushNum(int x){
  myStack.push(x);
}

void PostfixCalculator::add(){
  int a = myStack.top(); 
  myStack.pop(); 
  int b = myStack.top(); 
  myStack.pop();
  int c = a+b; 
  myStack.push(c);
}

void PostfixCalculator::subtract(){
  int a = myStack.top();
  myStack.pop();
  int b = myStack.top();
  myStack.pop();
  int c = b-a;
  myStack.push(c);
}

void PostfixCalculator::multiply(){
  int a = myStack.top();
  myStack.pop();
  int b = myStack.top();
  myStack.pop();
  int c = a*b;
  myStack.push(c);
}

void PostfixCalculator::divide(){
  int a = myStack.top();
  myStack.pop();
  int b = myStack.top();
  myStack.pop();
  int c = b/a;
  myStack.push(c);
}

void PostfixCalculator::negate(){
  int a = myStack.top();
  myStack.pop();
  int b = (-1)*a;
  myStack.push(b);
}

int PostfixCalculator::finalResult(){
  return myStack.top();
}

void PostfixCalculator::calculate(string s){
  if(s=="+"){
    add();
  }else if (s=="-"){
    subtract();
  }else if (s=="*"){
    multiply();
  }else if (s=="/"){
    divide();
  }else if (s=="~"){
    negate();
  }else{
    pushNum(atoi(s.c_str()));
  }
}
    
  
