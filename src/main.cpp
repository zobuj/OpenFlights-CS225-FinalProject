#include "extractData.h"
#include <fstream>
#include <iostream>
using namespace std;
int main() {
    Project init;
    // cout << "made project: " << endl;
    string routes_path = "/Users/alexisserrano/Documents/CS225_FinalProject/OpenFlights-CS225-FinalProject/data/sample/sampleroutes.dat";
    string airports_path = "/Users/alexisserrano/Documents/CS225_FinalProject/OpenFlights-CS225-FinalProject/data/sample/sampleairports.dat";
    
    init.readRoutes(routes_path);
    
    // cout << "Read routes finished: " << endl;
    init.readAirports(airports_path);
    // cout << "read airports: " << endl;
    init.createAdjacencyList();

    init.printMap();
    // should get output that matches DISCORD SCREENSHOT
    return 0;
}