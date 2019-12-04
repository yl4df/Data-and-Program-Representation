//Yunlu Li, yl4df, 2019-11-16, threexplusone.cpp

#include <iostream>
#include <cstdlib>
#include "timer.h"

using namespace std;
extern "C" int threexplusone(int);

int main(){
  int input;
  cout<<"Input one number: "<< endl;
  cin>>input;

  int times;
  cout<<"Run how many times: "<< endl;
  cin>>times;

  timer t;
  int step;
  t.start();
  for( int i = 0; i < times; i++){
    step = threexplusone(input);
  }
  t.stop();

  double time = t.getTime();
  double averageTime = time/times;

  cout<< "The number of steps is " << step << endl;
  cout<< "The average time is " << averageTime <<endl;
  return 0;
}


