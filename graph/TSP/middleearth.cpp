#include "middleearth.h"

#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// The list of all the place names that we'll be using
/** @brief store the list of cities that we will use 
 *
 */
string all_city_names[] = {
    // human towns, cities and strongholds
    "Bree",             // a human and hobbit town between the Shire and Rivendell
    "Isengard",         // the tower fortress where Saruman resided; Gandalf was imprisoned there.
    "Minas Tirith",     // capital of Gondor, the "white city"; home to Boromir, Denethor, and later, Aragorn
    "Osgiliath",        // city on the river Anduin; is at the other end of Pelennor Fields from M. Tirith
    "Edoras",           // the capital city of Rohan, where King Theoden resides
    "Helm's Deep",      // fortress of Rohan, it is where the people of Edoras fled to from the orc invasion
    "Dunharrow",        // a refuge of Rohan, it is where Elrond presents the sword to Aragorn in the movie
    // dwarf cities
    "Moria",            // the enormous dwarven underground complex that the Fellowship traveled through
    // elvish cities
    "Lothlorien",       // the elvish tree-city, home of Lady Galadriel and Lord Celeborn
    "Rivendell",        // the elvish city that is home to Lord Elrond
    "The Grey Havens",  // the port city on the western coast from which the elves travel westward
    // hobbit villages
    "Bucklebury",       // a Shire village, it has a ferry across the Brandywine River that the Hobbits use
    "Bywater",          // a Shire village, it is the site of the Battle of Bywater (removed from the movie)
    "Hobbiton",         // a Shire village, it is home to Bilbo and, later, Frodo
    "Michel Delving",   // a Shire village, it is the chief town of the Shire
    // Mordor places
    "Orodruin",         // Mount Doom in Mordor, it is where the Ring was made, and later, unmade
    "Barad-Dur",        // Sauron's fortress that was part castle, part mountain
    "Minas Morgul",     // formerly the Gondorian city of Minas Ithil; renamed when Sauron took it over
    "Cirith Ungol",     // the mountianous pass that Sam & Frodo went through; home of Shelob
    "Gorgoroth",        // the plains in Mordor that Frodo & Sam had to cross to reach Mount Doom
    // places that are not cities
    "Emyn Muil",        // the rocky region that Sam & Frodo climb through after leaving the Fellowship
    "Fangorn Forest",   // the forest where Treebeard (and the other Ents) live
    "Dagorlad",         // great plain/swamp between Emyn Muil & Mordor where a great battle was fought long ago
    "Weathertop",       // the tower between Bree and Rivendell where Aragorn and the Hobbits take refuge
    "Gladden Fields",   // this is where the Ring is lost in the River Anduin, after Isildur is ambushed and killed by Orcs
    "Entwash River",    // a river through Rohan, which flows through Fangorn Forest
    "River Isen",       // river through the Gap of Rohan; Theoden's son was slain in a battle here.
    "The Black Gate",   // huge gate to Mordor that Aragorn and company attack as the ring is destroyed
    "The Old Forest",   // a forest to the west of the Shire (adventures there were removed from the movie)
    "Trollshaws",       // area to the west of Rivendell that was home to the trolls that Bilbo met
    "Pelennor Fields",  // great plain between M. Tirith and Osgiliath; site of the Battle of M. Tirith
    "Hollin",           // the empty plains that the Fellowship crosses between Rivendell and Moria
    "Mirkwood",         // Legolas' forest home; Bilbo travels there in 'The Hobbit'.
    "Misty Mountains",  // the north-south moutain range that runs through Middle-earth
    "Prancing Pony",    // an inn in Bree where the hobbits tried to meet Gandalf, but meet Aragorn instead
    // places from the Hobbit book and movies
    "Laketown",         // also called Esgaorth, it is the town of men on the Long Lake near Erebor
    "Dale",             // the town of men outside Erebor, destroyed by Smaug long before the Hobbit story
    "Erebor",           // the Elvish name for the Lonely Mountain, where the dwarves had their fortress
    "Beorn's House",    // Beorn is the shape-shifter who shelters the dwarf party
    "Dol Guldur",       // fortress in Mirkwood where Sauron, as the Necromancer, hid during most of the Hobbit
    // END marker
    "END"
};

// Iluvatar, the creator of Middle-Earth
 /** @brief creator of a world based on given paramaters
     *
     *  @param xsize dimensionality of x
     *  @param ysize dimensionality of y
     *  @param num_cities the number of city
     *  @param seed for ramdonly generating cities
     */
MiddleEarth::MiddleEarth (int xsize, int ysize, int num_cities, int seed) {
    // set up the random number seed
    srand( (seed==-1) ? time(NULL) : seed );
    // count the number of cities in the array
    for ( num_city_names = 0; all_city_names[num_city_names] != "END";
            num_city_names++ );
    if ( num_cities > num_city_names ) {
        cout << "There are only " << num_city_names << " city names, so "
             << num_cities << " cities cannot be created.\nExiting." << endl;
        exit(0); /**< throws error when reaching the limit of city_name list*/
    }
    if ( num_cities < 5 )
      num_cities = 5; /**< at least 5 cities are needed for a world */
    // select the num_cities names of the cities that we'll be using
    for ( int i = 0; all_city_names[i] != "END"; i++ )
        cities.push_back(string(all_city_names[i]));
    /**< make sure all cities are evenly distributed */
    random_shuffle(cities.begin(), cities.end());
    /**< remove cities out of the given range */
    cities.erase(cities.begin()+num_cities,cities.end());
    /**< compute random city positions */
    for ( unsigned int i = 0; i < cities.size(); i++ ) {
        xpos.push_back((rand()/((float)RAND_MAX)) * xsize);
        ypos.push_back((rand()/((float)RAND_MAX)) * ysize);
    }
    /**< compute the 2-d distance array */
    this->xsize = xsize;
    this->ysize = ysize;
    // we assume that num_cities < xsize*ysize
    distances = new float[num_cities*num_cities]; /**< row-major order */
    for ( int r = 0; r < num_cities; r++ )
        for ( int c = 0; c < num_cities; c++ ) {
            distances[r*num_cities+c] = sqrt((xpos[c]-xpos[r])*(xpos[c]-xpos[r]) +
                                             (ypos[c]-ypos[r])*(ypos[c]-ypos[r]));
        }/**< use two for-loops to build a 2D matrix for distance */
    // create hash of indices so we don't have to do a linear search
    // each time we want to find a city name to index mapping
    for ( unsigned int i = 0; i < cities.size(); i++ )
        indices[cities[i]] = i;
}

// Sauron, the destructor of Middle-Earth.
 /** @brief destructor of the world
     *
     */
MiddleEarth::~MiddleEarth () {
    delete[] distances;
}

// The Mouth of Sauron!  (prints out info on the created 'world')
    /** @brief print out the cities and total number in the world
     *
     */
void MiddleEarth::print() {
    cout << "there are " << num_city_names
         << " locations to choose from; we are using " << cities.size() << endl;
    cout << "they are: " << endl; /**< print cities */
    for ( unsigned int i = 0; i < cities.size(); i++ )
        cout << "\t" << cities[i] << " @ (" << xpos[i] << ", " << ypos[i]
             << ")" << endl; /**< print distance */
}

// prints a tab-separated table of the distances (this can be loaded
// into Excel or similar)
 /** @brief print out a tab-separated table of the distances
     *
     */
void MiddleEarth::printTable() {
    cout << "Table: " << endl << endl << "Location\txpos\typos\t";
    for ( unsigned int r = 0; r < cities.size(); r++ )
      cout << cities[r] << "\t"; /**< print all cities horizontally */
    cout << endl; 
    for ( unsigned int r = 0; r < cities.size(); r++ ) {
        cout << cities[r] << "\t" << xpos[r] << "\t" << ypos[r] << "\t";
        for ( unsigned int c = 0; c < cities.size(); c++ )
            cout << distances[r*cities.size()+c] << "\t";
        cout << endl; /**< print all cities vertically with distance between two cities */
    }
}

// This method returns the distance between the two passed cities.  If
// we assume that the hash table (i.e. the map) is O(1), then this
// method call is also O(1)
 /** @brief calculate the distance between two given cities
     *
     * @return the distance between two cities passed
     * @param city1 the first city to be passed
     * @param city2 the second city to be passes
     */
float MiddleEarth::getDistance (string city1, string city2) {
    return distances[indices[city1]*cities.size()+indices[city2]];
 /**< get the distance by finding corresponding index in distance matrix */
}
// Returns the list of cities to travel to.  The first city is the
// original start point as well as the end point.  The number of
// cities passed in does not include this start/end point (so there
// will be length+1 entries in the returned vector).
/** @brief give the list of cities based on the given length
     *
     * @return the list of cities
     * @param length vector storing the cities to be visited
     */
vector<string> MiddleEarth::getItinerary (unsigned int length) {
    length++; // to account for the start point
    // check parameter
    if ( length > cities.size() ) { /**< throw out of range error */
        cout << "You have requested an itinerary of " << length-1
             << " cities; you cannot ask for an itinerary of more than length "
             << cities.size()-1 << endl;
        exit(0);
    }
    // we need to make a deep copy of the cities vector.  itinerary is a
    // pointer so that it doesn't get deleted when it goes out of scope.
    /**< make deep copy of cities */
    vector<string> itinerary;
    for ( unsigned int i = 0; i < cities.size(); i++ )
        itinerary.push_back(cities[i]);
    /**< shuffle, erase unneeded ones, and return the itinerary */
    random_shuffle(itinerary.begin(), itinerary.end());
    itinerary.erase(itinerary.begin()+length,itinerary.end());
    return itinerary;
}
