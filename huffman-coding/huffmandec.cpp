//Yunlu Li, yl4df, 2019-11-24, huffmandec.cpp


#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "heap.h"

using namespace std;
void makeTree(Node*& root, char c, string p);
void decode(Node*& root, string allbits);

int main (int argc, char **argv) {
  if ( argc != 2 ) {
      cout << "Must supply the input file name as the only parameter" << endl;
      exit(1);
  }
  ifstream file(argv[1], ifstream::binary);
  if ( !file.is_open() ) {
      cout << "Unable to open file '" << argv[1] << "'." << endl;
      exit(2);
  }

  vector<char> c;
  vector<string> p;
  Node* root = new Node();
  while ( true ) {
      string character, prefix;
      file >> character;
      if ( (character[0] == '-') && (character.length() > 1) )
          break;
      if ( character == "space" )
          character = " ";
      c.push_back(character[0]);
      file >> prefix;
      p.push_back(prefix);
    }
 
  //Loop through the vectors storing char and prefix. Build the huffmanTree.
  for (int i = 0;i<c.size();i++){
    makeTree(root, c[i], p[i]); 
    }
  
  stringstream sstm;
  while ( true ) {
    string bits;
    file >> bits;
    if ( bits[0] == '-' )
        break;
    sstm << bits;
  }
  string allbits = sstm.str();
  decode(root, allbits);
  file.close();
  return 0;
}

//recursive helper method to build huffman tree;
//recursive call through prefix; 0 goes left and 1 goes right;
//if the whole prefix is looped, then I build the node with character and prefix
void makeTree(Node*& root, char c, string p){
  if(p.length()==0){
    root= new Node(c);
    root->code = p;
  }else{
    if(root==NULL){
    root= new Node();
    }
  if(p[0]=='0'){
    makeTree(root->left,c,p.substr(1));
  }
  else if(p[0]=='1'){
    makeTree(root->right,c,p.substr(1));
  }
  }
}

//helper method to decode; use for-loop to loop through all bits;
//0 goes left and 1 goes right;
//print out character if the tree reach leaf node.
void decode(Node*& root, string allbits){
  Node* tem = root;
  for(int i = 0; i<allbits.length();i++){
    if(allbits[i]=='0'){
      root = root->left;
    }
    else{
      root = root->right;
    }
    if(root->left==NULL&&root->right==NULL){
      cout<<root->character;
      root=tem;
    }
  }
  cout<<endl;
}


