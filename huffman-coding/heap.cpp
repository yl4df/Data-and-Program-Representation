//Yunlu Li, yl4df, 2019-11-22, heap.cpp
//Heap operation comes from the example code provided.
#include <iostream>
#include "heap.h"

using namespace std;

Heap::Heap(){
  size=0;
  myHeap.push_back(0);
}

Node* Heap::findMin(){
  if(size==0){
    throw "No Element In Heap!";
  }
  else{
  return myHeap[1];
  }
}

void Heap::insert(Node* n){
  myHeap.push_back(n);
  percolateUp(size++);
}

Node* Heap::deleteMin(){
  if(size==0){
    throw "No Element In Heap!";
  }
  Node* n = myHeap[1];
  myHeap[1] = myHeap[size--];
  myHeap.pop_back();
  percolateDown(1);
  return n;
}

void Heap::percolateUp(int hole){
  Node* n = myHeap[hole];
  for ( ; (hole > 1) && (n->frequency < myHeap[hole/2]->frequency); hole /= 2 ){
    myHeap[hole]=myHeap[hole/2];
  }
  myHeap[hole]=n;
}

void Heap::percolateDown(int hole){
  Node* n = myHeap[hole];
  while(hole*2 <= size){
    int child = hole*2;
    if((child+1 <= size) && (myHeap[child+1]->frequency < myHeap[child]->frequency)){
      child++;
    }
    if(n->frequency>myHeap[child]->frequency){
      myHeap[hole]=myHeap[child];
      hole=child;
    }
    else
      break;
  }
  myHeap[hole]=n;
}

