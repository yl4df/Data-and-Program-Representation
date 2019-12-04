//Yunlu Li, yl4df, 2019-11-22, huffmanenc.cpp

#include <iostream>
#include <vector>
#include <algorithm>
#include "heap.h"
#include <string>

using namespace std;

void makeTree(Heap* h);
void prefix(Node* n, string s);
string getPrefix(Node* n, char c);

int main(int argc, char **argv){
  if ( argc != 2 ) {
    cout << "Must supply the input file name as the one and only parameter" << endl;
     exit(1);
    }
  
  FILE *fp = fopen(argv[1], "r");
  
  if ( fp == NULL ) {
     cout << "File '" << argv[1] << "' does not exist!" << endl;
     exit(2);
    }
  
  char g;
  vector<char> c; //store character
  vector<int> f; //store frequency
  int symbols=0;
  //Instead of using map, we use two vectors to store char and its frequency;
  while ( (g = fgetc(fp)) != EOF && 0x20<=g && g<=0x7e ){
    if(find(c.begin(), c.end(), g) == c.end()){
      c.push_back(g);
      f.push_back(1);
      symbols++;
    }
    else{
      int index = find(c.begin(), c.end(), g)- c.begin();
      f[index] = f[index] + 1;
      symbols++;
    }
  }

  Heap* h = new Heap();
  for (int i=0; i<c.size();i++){
    char ch = c[i];
    Node* n = new Node(ch);
    int fre = f[i];
    n->frequency = fre;
    h->insert(n);
  }

  makeTree(h);
  prefix(h->findMin(),"");
  cout << "----------------------------------------" << endl;
  
  rewind(fp);
  int comp = 0;
  while ( (g = fgetc(fp)) != EOF ){
    cout<<getPrefix(h->findMin(),g)<<" ";
    comp = comp + getPrefix(h->findMin(),g).length();
  }
  cout<<endl;
  cout << "----------------------------------------" << endl;
  
  int uncomp = 8*symbols;
  double ratio = (double) uncomp/comp;
  double cost = (double) comp/symbols;
  cout << "There are  a total of " << symbols << " symbols that are encoded." << endl;
  cout << "There were " << uncomp << " bits in the originial file " << endl;
  cout << "There were " << comp << " bits in the compressed file." << endl;
  cout << "This gives a compression ratio of " << ratio << endl;
  cout << "The cost of the huffman tree is " << cost << " bits per character" <<endl;
  fclose(fp);
  return 0;
}

void makeTree(Heap* h){
  while (h->size > 1){
    Node* newNode = new Node();
    Node* l = h->deleteMin();
    Node* r = h->deleteMin();
    newNode->frequency = l->frequency + r->frequency;
    newNode->left = l;
    newNode->right = r;
    h->insert(newNode);
  }
}

void prefix(Node* n, string s){
  if (n->left != NULL){
    prefix(n->left, s+"0");
  }
  if(n->right != NULL){
    prefix(n->right, s+"1");
  }
  if(n->left==NULL && n->right==NULL){
    if(n->character==' '){
      n->code = s;
      cout<<"space "<<s<<endl;
    }
    else{
      n->code=s;
      cout<<n->character<<" "<<s<<endl;
    }
  }
}

string getPrefix(Node* n, char c){
   if(n->character==c){
     return n->code;
   }
   else{
     if(n->left==NULL && n->right==NULL){
       return "";
     }
     else{
       if(getPrefix(n->right, c).compare("")==0){
       return getPrefix(n->left, c);
    }
       else{
	 return getPrefix(n->right, c);
       }
     }
   }
}
  

  
