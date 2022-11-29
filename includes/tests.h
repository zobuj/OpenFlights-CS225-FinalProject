#include "../includes/extractData.h"
#include <string>
#include <vector>
#include <map>
#include <cassert>
void ReadRoutesSimple();
void ReadAirportsSimple();
void TestsAdjacencyLists();
void testSimpleGraphOutput();
string getRoutesPath() {
    // just change this to your path
    return "/workspaces/cs225/release-f22/release-f22/Final Project/OpenFlights-CS225-FinalProject/data/sample/sampleroutes.dat";
}
string getAirportsPath() {
    // just change this to your path
    return  "/workspaces/cs225/release-f22/release-f22/Final Project/OpenFlights-CS225-FinalProject/data/sample/sampleairports.dat";
}