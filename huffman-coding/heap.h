//Yunlu Li, yl4df, 2019-11-22, heap.h

#include <vector>
#include "node.h"

using namespace std;

class Heap{
 public:
  Heap();
  Node* findMin();
  void insert(Node* n);
  Node* deleteMin();
  void percolateUp(int hole);
  void percolateDown(int hole);
  vector<Node*> myHeap;
  int size;
};
  
  
