//Yunlu Li, yl4df, 2019-11-22, node.cpp
#include "node.h"

using namespace std;

Node::Node(){
  frequency=0;
  left=NULL;
  right=NULL;
  code="";
}

Node::Node(char c){
  frequency=0;
  character = c;
  left=NULL;
  right=NULL;
  code="";
}
