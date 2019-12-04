//Yunlu Li, yl4df, 2019-11-29, topological.cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <fstream>
#include <stdlib.h>
using namespace std;

class vertex{
public:
  vertex();
  int indegree;
  string element;
  vector <vertex*> adj;
};

/** @brief construct vertex class
 *
 */
vertex::vertex(){
    indegree = 0;
    element="";
}

/** @brief read in the file and perform topological sort
 *
 */
int main (int argc, char **argv) {
    // verify the correct number of parameters
  if ( argc != 2 ) {
      cout << "Must supply the input file name as the one and only parameter" << endl;
      exit(1);
  }
    // attempt to open the supplied file
  ifstream file(argv[1], ifstream::binary);
    // report any problems opening the file and then exit
  if ( !file.is_open() ) {
      cout << "Unable to open file '" << argv[1] << "'." << endl;
      exit(2);
  }
    // read in two strings
  string s1, s2;
  string str;
  vector<string> elementList;/**< vector storing name of vertex */
  vector<vertex*> vertexList;/**< vector storing vertex */
  while(s1 != "0" && s2 != "0"){
    file >> s1;
    file >> s2;
    if(s1 == "0" && s2 == "0"){
      break; /**< read in two strings in one line; end until the string is 0 */
    }
    else{
      if(find(elementList.begin(), elementList.end(), s1) == elementList.end()){
	vertex * ver = new vertex();
	ver->element = s1;
	elementList.push_back(s1);
	vertexList.push_back(ver);
      }/**< if s1 is new, push it back to two vectors */
      if(find(elementList.begin(), elementList.end(), s2) == elementList.end()){
	vertex * ver = new vertex();
	ver->element = s2;
	elementList.push_back(s2);
	vertexList.push_back(ver);
      }/**< if s2 is new, push it back to two vectors */
      int index1 = find(elementList.begin(), elementList.end(), s1)- elementList.begin(); 
      int index2 = find(elementList.begin(), elementList.end(), s2)- elementList.begin();
      vertexList[index1]->adj.push_back(vertexList[index2]);
      vertexList[index2]->indegree++;
    }/**< if it is not new, push it to adj vector and increase indegree */
  }

    // close the file before exiting
  file.close();

  /**< Perform topsort; Reference from slide 11 and Wikipedia reading */
  queue<vertex*> q = queue<vertex*>();
  vertex *v;
  string res="";
  

  for(int i=0; i<vertexList.size(); i++){
    if(vertexList[i]->indegree == 0){
      q.push(vertexList[i]);
    }/**< if no incoming edge, then put it into the queue */
  }
  while(!q.empty()){ /**< loop through queue*/
      v=q.front();
      q.pop();
      res = res + v->element +" "; /** <pop the front from queue and print out */
      for( int k=0; k<v->adj.size(); k++){
	v->adj[k]->indegree--; /**< loop through its adj vector and decrease indegree one by one */
	if(v->adj[k]->indegree == 0){
	  q.push(v->adj[k]);/**< put it into the queue when indegree is 0 */
	  }
	}
    }
  cout<< res << endl;
  return 0; 
}
  
