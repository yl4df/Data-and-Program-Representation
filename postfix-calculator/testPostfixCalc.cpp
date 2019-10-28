//Yunlu Li, yl4df, testPostfixCalc.cpp, 2019-09-13

#include "postfixCalculator.h"
#include "stack.h"
#include <iostream>

using namespace std;

int main() {
    PostfixCalculator p;
    string s;
    while (cin >> s) {
      p.calculate(s);
    }
    cout << "Result is: " << p.finalResult() << endl;
    return 0;
}
  /*
    PostfixCalculator p1;
    p1.pushNum (1);
    p1.pushNum (2);
    p1.pushNum (3);
    p1.pushNum (4);
    p1.pushNum (5);
    p1.add();
    p1.add();
    p1.add();
    p1.add();
    cout << "Case 1 Result is: " << p1.finalResult() << endl;
    
    PostfixCalculator p2;
    p2.pushNum (20);
    p2.pushNum (10);
    p2.subtract();
    p2.pushNum (-3);
    p2.pushNum (10);
    p2.subtract();
    p2.subtract();
    p2.pushNum (2);
    p2.subtract();
    cout << "Case 2 Result is: " << p2.finalResult() << endl;

    PostfixCalculator p3;
    p3.pushNum(-1);
    p3.pushNum(-2);
    p3.pushNum(-5);
    p3.pushNum(3);
    p3.multiply();
    p3.pushNum(2);
    p3.pushNum(-2);
    p3.multiply();
    p3.multiply();
    p3.multiply();
    p3.multiply();
    cout << "Case 3 Result is: " << p3.finalResult() << endl;

    PostfixCalculator p4;
    p4.pushNum(-1512);
    p4.pushNum(-12);
    p4.pushNum(-2);
    p4.divide();
    p4.divide();
    p4.pushNum(-2);
    p4.divide();
    p4.pushNum(3);
    p4.divide();
    cout << "Case 4 Result is: " << p4.finalResult() << endl;
     
    PostfixCalculator p5;
    p5.pushNum(-1);
    p5.negate();
    p5.negate();
    p5.negate();
    cout << "Case 5 Result is: " << p5.finalResult() << endl;
    return 0;
  */
