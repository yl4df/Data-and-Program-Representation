//Yunlu Li, yl4df, 2019-09-07, ListItr.cpp

#include <iostream>
#include "ListNode.h"
#include "List.h"
#include "ListNode.h"

using namespace std;

//Constructor
ListItr::ListItr(){}

// One parameter constructor
ListItr::ListItr(ListNode * theNode){
  current=theNode;
    }

//Returns true if past end position in list, else false
bool ListItr::isPastEnd() const{
  if(current->next==NULL){
    return true;
  }
  else
    return false;
}

//Returns true if past first position in list, else false
bool ListItr::isPastBeginning() const{
  if(current->previous==NULL){
    return true;
  }
  else
    return false;
}

//Advances current to next position in list
void ListItr::moveForward(){
  current = current->next;
}

//Moves current back to previous position
void ListItr::moveBackward(){
  current = current->previous;
}

//Returns item in current position
int ListItr::retrieve() const{
  return current->value;
}


