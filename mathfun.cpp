//Yunlu Li, yl4df, 2019-11-01, mathfun.cpp
#include <iostream> 
#include <cstdlib> 

using namespace std;

extern "C" int product(int, int); 
extern "C" int power(int, int);

int main(){
  int x, y;

  cout<< "Please enter the frist positive integer:  ";
  cin>>x;
  cout<< "Please enter the second positive integer:  ";
  cin>>y;

  cout<<"The result of x*y is "<<product(x,y)<<endl;
  cout<<"The result of x^y is "<<power(x,y)<<endl;

  return 0;
}
