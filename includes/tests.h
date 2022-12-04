#include "../includes/extractData.h"
#include <string>
#include <vector>
#include <map>
#include <cassert>
void ReadRoutesSimple();
void ReadAirportsSimple();
void TestsAdjacencyLists();
void testSimpleGraphOutput();
string getSimpleRoutesPath() {return "../OpenFlights-CS225-FinalProject/data/sample/sampleroutes.dat";}
string getSimpleAirportsPath() {return  "../OpenFlights-CS225-FinalProject/data/sample/sampleairports.dat";}
string getDijkstrasRoutesPath() {return "../OpenFlights-CS225-FinalProject/data/sample/sampleroutesdijkstras.dat";}
string getDijkstrasAirportsPath() {return  "../OpenFlights-CS225-FinalProject/data/sample/sampleairportsdijkstras.dat";}