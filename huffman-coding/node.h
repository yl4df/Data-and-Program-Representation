//Yunlu Li, yl4df, 2019-11-22, node.h

#include <string>

using namespace std;

class Node{
 public:
  Node();
  Node(char c);
  Node* left;
  Node* right;
  int frequency;
  char character;
  string code;
};
