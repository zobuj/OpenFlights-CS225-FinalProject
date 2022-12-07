#include "../includes/project.h"
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <cmath>
using namespace std;
/**
* Read the Simple Routes
* 
* Tests whether or not our program is reading the Routes input file correctly. The input files are named below in the "getSimple_Path".
* Reading the small routes file, we have written out what the expected routes pattern should be. 
* Utilizing the appropriate getter in our project class, we are able to assert that each node matches.
* If each node matches, we display a 'success' message at the end of our test case
*/
void ReadRoutesSimple();
/**
* Read the Simple Routes
* 
* Tests whether or not our program is reading the Airports input file correctly. The input files are named below in the "getSimple_Path".
* Reading the small airports file, we have written out what the expected airports ids should be. 
* Utilizing the appropriate getter in our project class, we are able to assert that each id matches.
* If each node matches, we display a 'success' message at the end of our test case
*/
void ReadAirportsSimple();
/**
* Testing our Simple Adjacency List
* 
* Tests whether or not our program is storing the routes in the appropriate manner. The input files are named below in the "getSimple_Path".
* Reading the small airports file, we have written out what the expected adjacency list should be. 
* Utilizing the appropriate getter in our project class, we are able to assert that each node matches as well as each neighbor of that node.
* If all of the mentioned test cases hold, we display a 'success' message at the end of our test case
*/
void TestsAdjacencyListsSimple();
/**
 * Test whether there is a connection between two nodes using Depth First Search
 * This test case uses the simple routes data file to determine whether a path exist between two airports
 * The airports' four-digit code is used as parameters in the function
 * If two airports have no connection, the function returns 0 (false)
 * If two airports have a connection, the function returns 1 (true)
*/
void SimplePathExist();

/**
* 
* Tests whether the graphical visualization algorithm displays the right graph. 
* We created a test suite.dot file that we hardcoded and then the test will run 
* diff to find any differences from the function created .dot file. If there is 
* no differences then 0 will be returned and the test passes.
*/
void testSimpleGraphOutput();

/**
* 
* Test Shortest path between two nodes with the sample dijkstras route.
* This tests a new routes file, the dijkstra routes path. Provided in the path below
* We are recieving doubles that represent the distance between the two nodes. We are matching the outputs with our hard coded values.
* We have calculated these values by hand 
* An explanation of the dijkstras function used in this test case can be found in the project.h file
* After running tests to make sure the shortest distance is what we expect, we run tests using findpath to check the shortest path 
* We have also calculated the expected paths by hand
*/
void TestShortestPath();
/**
* All the appropriate file paths for our program.
* The Dijkstras file and the Simple file are identifiable by those keywords
* 
*/


string getSimpleRoutesPath() {return "../OpenFlights-CS225-FinalProject/data/sample/sampleroutes.dat";}

string getSimpleAirportsPath() {return  "../OpenFlights-CS225-FinalProject/data/sample/sampleairports.dat";}


string getDijkstrasRoutesPath() {return "../OpenFlights-CS225-FinalProject/data/sample/sampleroutesdijkstras.dat";}

string getDijkstrasAirportsPath() {return  "../OpenFlights-CS225-FinalProject/data/sample/sampleairportsdijkstras.dat";}

