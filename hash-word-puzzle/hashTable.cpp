//Yunlu Li, yl4df, 2019-10-19, hashTable.cpp




#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include "hashTable.h"

using namespace std;

hashTable::hashTable(int size){
  vector<list<string> > myTable;
  for ( int i = 0; i < size; i++ )
    {
      list<string> temp;
      myTable.push_back(temp);
    }
  capacity = size;
}

hashTable::~hashTable()
{
}

void hashTable::rehash(int size){
  if(!checkprime(size)){
    size = getNextPrime(size);
  }
  myTable.resize(size);
    for ( int i = capacity; i < size; i++ )
    {
      list<string> temp;
      myTable.push_back(temp);
    }
    capacity = size;


}

//check whether myTable has the word or not. 
bool hashTable::contains(const string & word){
  int position = hashFunction(word);
  list<string>& theList = myTable.at(position);
  //find function for list returns the end interator if not success. 
  return (::find(theList.begin(), theList.end(), word)!=theList.end());

}

void hashTable::insert(const string & word){
  if(!contains(word)){
    int position = hashFunction(word);
    myTable[position].push_back(word);
  }

}

int hashTable::hashFunction(const string & word) const{
  int len = word.length();
  int value = 0;
  for(int i = 0; i<len; i++){
    value = value + word[i];
  }
  return value%capacity;
}

bool hashTable::checkprime(unsigned int p) {
    if ( p <= 1 ) // 0 and 1 are not primes; the are both special cases
        return false;
    if ( p == 2 ) // 2 is prime
        return true;
    if ( p % 2 == 0 ) // even numbers other than 2 are not prime
        return false;
    for ( int i = 3; i*i <= p; i += 2 ) // only go up to the sqrt of p
        if ( p % i == 0 )
            return false;
    return true;
}

int hashTable::getNextPrime (unsigned int n) {
    while ( !checkprime(++n) );
    return n; // all your primes are belong to us
}

  
  
