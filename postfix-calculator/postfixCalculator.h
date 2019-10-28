//Yunlu Li, yl4df, postfixCalculator.h, 2019-09-13

#ifndef POSTFIXCALCULATOR_H
#define POSTFIXCALCULATOR_H

#include <iostream>
#include "stack.h"

using namespace std;

class PostfixCalculator{
 public:
  PostfixCalculator(); //Constrcutor
  void pushNum(int x); //Push given number to the stack
  void add(); //Perform addition
  void subtract(); // Perform subtraction
  void multiply();  //Perform multiplication
  void divide();  //Perform division
  void negate();  //Perform negation
  int finalResult(); //Show final result
  void calculate(string s);
  
 private:
  Stack myStack;
};

#endif
