//Yunlu Li, yl4df, 2019-12-03, traveling.cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <limits>
#include <cfloat>

using namespace std;

#include "middleearth.h"

float computeDistance (MiddleEarth &me, string start, vector<string> dests);
void printRoute (string start, vector<string> dests);
/** @brief main method taking six command-line paramter and print out shortest distance and path
 *
 */
int main (int argc, char **argv) {
    // check the number of parameters
    if ( argc != 6 ) {
        cout << "Usage: " << argv[0] << " <world_height> <world_width> "
             << "<num_cities> <random_seed> <cities_to_visit>" << endl;
        exit(0);
    }
    // we'll assume the parameters are all well-formed
    int width, height, num_cities, rand_seed, cities_to_visit;
    sscanf (argv[1], "%d", &width);
    sscanf (argv[2], "%d", &height);
    sscanf (argv[3], "%d", &num_cities);
    sscanf (argv[4], "%d", &rand_seed);
    sscanf (argv[5], "%d", &cities_to_visit);
    // Create the world, and select your itinerary
    MiddleEarth me(width, height, num_cities, rand_seed);
    vector<string> dests = me.getItinerary(cities_to_visit);

    /**< start is the first city in vector; retrieve it and erase it.*/
    string start = dests[0];
    
    dests.erase(dests.begin());
    /**< sort vector for permutation */
    sort(dests.begin(), dests.end());

    float min_dis = FLT_MAX;
    vector<string> bestPath;
    if(dests.size()==1){
      bestPath = dests;
      min_dis = computeDistance(me, start, dests);
    }
    else{
    while(next_permutation(dests.begin(), dests.end())){
	float dis = computeDistance(me, start, dests);
	if(dis < min_dis){
	   min_dis = dis;
	   bestPath = dests; /**< use permutation to find min_distance and path */
	}
      }
    }
    cout<< "Minimum path has distance " << min_dis << ": ";
    printRoute(start, bestPath);
    return 0;
}


/** @brief compute the distance of the given path
 *
 * This method will compute the full distance of the cycle that starts
 * at the 'start' parameter, goes to each of the cities in the dests
 * vector IN ORDER, and ends back at the 'start' parameter.
 * @return the distance
 * @param me the world
 * @param start the starting city
 * @param dests the vector storing destinations
 *
 */
float computeDistance (MiddleEarth &me, string start, vector<string> dests) {
  float dis = me.getDistance(start, dests[0]);/**< the distance from start to the fist city */
  for (int i=0; i<dests.size()-1; i++){
    dis = dis +me.getDistance(dests[i], dests[i+1]); /**< total distance within the vector destination */
  }
  dis = dis + me.getDistance(dests[dests.size()-1], start);/**< the distance from last city back to start*/
  return dis;
}


/** @brief print out the route
 * This method will print the entire route, starting and ending at the
 * start' parameter
 * @param start the starting city
 * @param dests the vector storing destinations
 *
 */
void printRoute (string start, vector<string> dests) {
  cout<< start << " -> ";/**< print out start*/
  for(int i = 0; i < dests.size(); i++){
    cout<< dests[i] << " -> ";/**< print out route within the vector*/
  }
  cout<< start << endl; /**< print out start again*/
}
