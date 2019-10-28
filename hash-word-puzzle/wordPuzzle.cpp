//Yunlu Li, yl4df, 2019-10-19,wordPuzzle.cpp

/* The big-Theta running time is (rows*cols*words). In word searching, we 
need two for-loops for each row and column and use “contains” function of hash 
table to check, of which running time depends on how many words we have. 


Actual running time:
3x3.grid.txt: 0.001115 seconds.
4x7.grid.txt: 0.007542 seconds.
50x50.grid.txt: 0.940174 seconds.
140x70.grid.txt: 3.94168 seconds.
250x250.grid.txt: 23.2906 seconds.
300x300.grid.txt: 4.59611 seconds
*/
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "hashTable.h"
#include "timer.h"

using namespace std;

#define MAXROWS 500
#define MAXCOLS 500
char grid[MAXROWS][MAXCOLS];
hashTable dictTable(30000);
timer t;

int getNumLines (string filename);
bool readInDict (string filename);
bool readInGrid (string filename, int &rows, int &cols);
char* getWordInGrid (int startRow, int startCol, int dir, int len,
                     int numRows, int numCols);

int main(int argc, char ** argv){
   if ( argc != 3 ) 
        {
            cout << "Error: missing argument(s), try again" << endl;
            exit(1);
        }

   string dict = argv[1];
   int size = getNumLines(dict);
   
   dictTable.rehash(size);//change to prime size according to dictionary line.
   
   bool result1 = readInDict(dict);
   if(result1==false){
     cout<< "Error in reading in dictionary" << endl;
     exit(1);
   }

  string grid = argv[2];
  int rows, cols;
  bool result2 = readInGrid(grid, rows, cols);
   if(result2==false){
     cout<< "Error in reading in grid" << endl;
     exit(1);
   }


  t.start();
  string dir;
  int wordFound=0;
  for(int r = 0; r < rows; r++){
    for(int c = 0; c < cols; c++){
      for(int d = 0; d < 8; d++){
	for(int len=3; len <=22; len++){
	  string word = getWordInGrid(r, c, d, len, rows, cols);
	  if(dictTable.contains(word)){
	    if(word.length()==len){
	    wordFound++;
	    switch (d) {
	    case 0:
	      dir = "N";
	      break;
	    case 1:
	      dir = "NE";
	      break;
	    case 2:
	      dir = "E";
	      break;
	    case 3:
	      dir = "SE";
	      break;
	    case 4:
	      dir = "S";
	      break;
	    case 5:
	      dir = "SW";
	      break;
	    case 6:
	      dir = "W";
	      break;
	    case 7:
	      dir = "NW";
	      break;
	    }
	    cout<<dir<< " (" << r << ", " << c << "): \t"
		<< word << endl;
	  }
	  }
	}
      }
    }
  }
  t.stop();
  double time = t.getTime();
  cout << wordFound << " words found" << endl;
  cout << "Found all  words in : " << time << " seconds" << endl;
  cout << time*1000<<endl; 
 return 0;
}

int getNumLines (string filename){
  int wordCount = 0;
  ifstream file(filename.c_str());
  string word;
  while (getline(file, word)) 
   {
     wordCount ++;
   }
   file.close();
   return wordCount;
}

bool readInDict (string filename){
  ifstream file(filename.c_str());
  if(!file.is_open()){return false;}
  string word;
  while ( getline(file, word)){
	 dictTable.insert(word);
     }
   
   file.close();
   return true;
}

bool readInGrid (string filename, int &rows, int &cols) {
    // a C++ string to hold the line of data that is read in
    string line;
    // set up the file stream to read in the file (takes in a C-style
    // char* string, not a C++ string object)
    ifstream file(filename.c_str());
    // upon an error, return false
    if ( !file.is_open() )
        return false;
    // the first line is the number of rows: read it in
    file >> rows;
    //cout << "There are " << rows << " rows." << endl;
    getline (file,line); // eats up the return at the end of the line
    // the second line is the number of cols: read it in and parse it
    file >> cols;
    //cout << "There are " << cols << " cols." << endl;
    getline (file,line); // eats up the return at the end of the line
    // the third and last line is the data: read it in
    getline (file,line);
    // close the file
    file.close();
    // convert the string read in to the 2-D grid format into the
    // grid[][] array.  In the process, we'll print the grid to the
    // screen as well.
    int pos = 0; // the current position in the input data
    for ( int r = 0; r < rows; r++ ) {
        for ( int c = 0; c < cols; c++ ) {
            grid[r][c] = line[pos++];
            //cout << grid[r][c];
        }
        //cout << endl;
    }
    // return success!
    return true;
}



/** This function will retrieve a word in a grid of letters in a given
 * direction.  If the end of the grid is encountered before the length
 * of the desired string is reached, then a shorter string will be
 * returned.  The data is retrieved from a global char grid[][]
 * array, which is assumed to be defined (and in scope).  NOTE: The
 * return value is a static char[][] variable (for efficiency
 * reasons), so a successive return value will overwrite a previous
 * return value.
 *
 * @return A char* containing the letters in the provided direction
 *         (NOTE: it is returned in a static char array).
 * @param startRow The starting (row,col) position to find the word.
 * @param startCol The starting (row,col) position to find the word.
 * @param dir The direction to move: 0 is north (upwards), 1 is
 *            northeast, and it rotates around clockwise until it
 *            reaches 7 for northwest.
 * @param len The desired length of the string to return (assuming
 *            the edge of the grid is not reached--if the edge of the
 *            grid is reached, it will return as many characters as
 *            possible up to the edge of the grid, so the returned
 *            string may not have the same length as this parameter
 *            indicates).
 * @param numRows The number of rows in the global char grid[][]
 *                array.
 * @param numCols The number of columns in the global char grid[][]
 *                array.
 */
char* getWordInGrid (int startRow, int startCol, int dir, int len,
                     int numRows, int numCols) {
    // the static-ness of this variable prevents it from being
    // re-declared upon each function invocataion.  It also prevents it
    // from being deallocated between invocations.  It's probably not
    // good programming practice, but it's an efficient means to return
    // a value.
    static char output[256];
    // make sure the length is not greater than the array size.
    if ( len >= 255 )
        len = 255;
    // the position in the output array, the current row, and the
    // current column
    int pos = 0, r = startRow, c = startCol;
    // iterate once for each character in the output
    for ( int i = 0; i < len; i++ ) {
        // if the current row or column is out of bounds, then break
        if ( (c >= numCols) || (r >= numRows) || (r < 0) || (c < 0) )
            break;
        // set the next character in the output array to the next letter
        // in the grid
        output[pos++] = grid[r][c];
        // move in the direction specified by the parameter
        switch (dir) { // assumes grid[0][0] is in the upper-left
            case 0:
                r--;
                break; // north
            case 1:
                r--;
                c++;
                break; // north-east
            case 2:
                c++;
                break; // east
            case 3:
                r++;
                c++;
                break; // south-east
            case 4:
                r++;
                break; // south
            case 5:
                r++;
                c--;
                break; // south-west
            case 6:
                c--;
                break; // west
            case 7:
                r--;
                c--;
                break; // north-west
        }
    }
    // set the next character to zero (end-of-string)
    output[pos] = 0;
    // return the string (a C-style char* string, not a C++ string
    // object)
    return output;
}

    
