#include <iostream>
#include <vector>
#include <string>
#include <map>

#ifndef MIDDLEEARTH_H
#define MIDDLEEARTH_H

using namespace std;

// see the comments in the lab11 write-up, or in middleearth.cpp

class MiddleEarth {
private:
    /** @brief: define variables
     *
     */
    int num_city_names, xsize, ysize; 
    vector<float> xpos, ypos; /**< vectors storing position in x and y-axis */
    vector<string> cities;  /**< veector storing city names */
    float *distances; 
    map<string, int> indices; /**< a map used to determine the index of city */

public:
    /** @brief creator of a world based on given paramaters
     *
     *  @param xsize dimensionality of x
     *  @param ysize dimensionality of y
     *  @param num_cities the number of city
     *  @param seed for ramdonly generating cities
     */
    MiddleEarth (int xsize, int ysize, int numc_ities, int seed);
    /** @brief destructor of the world
     *
     */
    ~MiddleEarth();
    /** @brief print out the cities and total number in the world
     *
     */
    void print();
     /** @brief print out a tab-separated table of the distances
     *
     */
    void printTable();
    /** @brief calculate the distance between two given cities
     *
     * @return the distance between two cities passed
     * @param city1 the first city to be passed
     * @param city2 the second city to be passes
     */
    float getDistance (string city1, string city2);
    /** @brief give the list of cities based on the given length
     *
     * @return the list of cities
     * @param length vector storing the cities to be visited
     */
    vector<string> getItinerary(unsigned int length);
};

#endif
