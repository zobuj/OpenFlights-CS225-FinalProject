#include "../includes/extractData.h"
#include <string>
#include <vector>
#include <map>
#include <cassert>
void ReadRoutesSimple();
void ReadAirportsSimple();
void TestsAdjacencyLists();
string getRoutesPath() {
    // just change this to your path
    return "/workspaces/cs225/revised/release-f22/OpenFlights-CS225-FinalProject/data/sample/sampleroutes.dat";
}
string getAirportsPath() {
    // just change this to your path
    return  "/workspaces/cs225/revised/release-f22/OpenFlights-CS225-FinalProject/data/sample/sampleairports.dat";
}