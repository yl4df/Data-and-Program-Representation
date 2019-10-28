//Yunlu Li, yl4df, 2019-10-19, hashTable.h

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <iostream>

using namespace std;

class hashTable{
 public:
  hashTable(int size);//constructor
  ~hashTable();
  void insert(const string & word); 
  bool contains(const string & word);
  void rehash(int size);
  int hashFunction(const string & word) const; 

 private:
  vector<list<string> > myTable;
  int capacity;
  bool checkprime(unsigned int p);
  int getNextPrime (unsigned int n);
};

#endif 
