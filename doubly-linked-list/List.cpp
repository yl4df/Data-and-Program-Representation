//Yunlu Li, yl4df, List.cpp, 2019-09-07

#include "List.h"
#include "ListNode.h"
#include "ListItr.h"
#include <iostream>

using namespace std;

//constructor--empty list
List::List(){
  head = new ListNode;
  tail = new ListNode;
  head->next = tail;
  tail->previous = head;
  count=0;
}

List::List(const List& source) {      // Copy Constructor
  head=new ListNode;
  tail=new ListNode;
  head->next=tail;
  tail->previous=head;
  count=0;
  ListItr iter(source.head->next);
  while (!iter.isPastEnd()) {       // deep copy of the list
        insertAtTail(iter.retrieve());
        iter.moveForward();
    }
}

//Destructor
List::~List() {
  delete head;
  delete tail;
}

List& List::operator=(const List& source) { //Equals operator
    if (this == &source)
        return *this;
    else {
        makeEmpty();
        ListItr iter(source.head->next);
        while (!iter.isPastEnd()) {
            insertAtTail(iter.retrieve());
            iter.moveForward();
        }
    }
    return *this;
}

//Check count to return whether the list is empty 
bool List::isEmpty() const{
  if(count==0)
        return true;
  else
        return false;
}

//Make the list Empty by removing value on each node one by one
void List::makeEmpty(){
  ListItr pos(head);
  pos.moveForward();
  while(!pos.isPastEnd()){
    pos.current->next->previous = head;
    delete head->next;//Use remove() defined below to remove the current node
    pos.moveForward();
    head->next = pos.current;//Reser the current node to next
  }
}

//Return the first node
ListItr List::first(){
  return ListItr(head->next);
}

//Return the last node
ListItr List::last(){
  return ListItr(tail->previous);
}

//Insert the node with value x after the given position
void List::insertAfter(int x, ListItr position){
  ListNode * insertNode = new ListNode;
  insertNode->value=x;
  insertNode->previous=position.current;
  insertNode->next=position.current->next; //Initialize the node
  insertNode->next->previous=insertNode;
  insertNode->previous->next=insertNode;
  //Insert the node to the correct position
  count=count+1;
}

//Insert the node with value x before the given position
void List::insertBefore(int x, ListItr position){
  ListNode * insertNode = new ListNode;
  insertNode->value=x;
  insertNode->previous=position.current->previous;
  insertNode->next=position.current;  //Initialize the node
  insertNode->next->previous=insertNode;
  insertNode->previous->next=insertNode;
  //Insert the node to the correct position
  count=count+1;
}

//Insert the node with value x at the tail
void List::insertAtTail(int x){
  ListNode * insertNode = new ListNode;
  insertNode->value=x;
  insertNode->previous=tail->previous;
  insertNode->next=tail;  //Initialize the node
  insertNode->previous->next = insertNode;
  insertNode->next->previous = insertNode;
  //Insert the node to the correct position
  count=count+1;
}

//Removes the first occurrence of x
void List::remove(int x){
  ListItr del = find(x);
  if(del.current->next==NULL){
    cout<<"There is no such node!"<<endl;
  }
  else{
    del.current->next->previous = del.current->previous;
    del.current->previous->next = del.current->next; //Reset links after removing
    delete del.current; //Clean up memory
    count = count - 1;
    }
}

//Returns an iterator that points to the first occurrence of x, else return
//a iterator to the dummy tail node
ListItr List::find(int x){
  ListItr currentItr = first();
  while(!currentItr.isPastEnd()){ 
    if(currentItr.current->value==x){
      return currentItr;
    }
    else
      currentItr.moveForward();
  }
  return tail;
}

//Returns the number of elements in the list
int List::size() const {
    return count;
}

//prints list forwards when direction is true or backwards when direction is false
void printList(List& source, bool direction){
  if(direction){
    ListItr currentPrint = source.first();
    while(!currentPrint.isPastEnd()){
        cout << currentPrint.retrieve() << ", ";
	currentPrint.moveForward();
      }
    cout << endl;
  }
  else{
    ListItr currentPrint = source.last();
    while(!currentPrint.isPastBeginning()){
        cout << currentPrint.retrieve() << ", ";
	currentPrint.moveBackward();
    }
    cout << endl;
  }
}
