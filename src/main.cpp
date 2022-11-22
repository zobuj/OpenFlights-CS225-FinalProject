#include "extractData.h"

#include <fstream>
#include <iostream>
using namespace std;
int main() {
    Project init;
    // cout << "made project: " << endl;
   string routes_path = "/workspaces/cs225/release-f22/release-f22/Final Project/OpenFlights-CS225-FinalProject/data/raw/routes.dat";
   string airports_path = "/workspaces/cs225/release-f22/release-f22/Final Project/OpenFlights-CS225-FinalProject/data/raw/airports.dat";
   // string routes_path = "/workspaces/cs225/release-f22/release-f22/Final Project/OpenFlights-CS225-FinalProject/data/sample/sampleroutes.dat";
   // string airports_path = "/workspaces/cs225/release-f22/release-f22/Final Project/OpenFlights-CS225-FinalProject/data/sample/sampleairports.dat";

    //Amir Path
    /*string routes_path = "/workspaces/cs225/revised/release-f22/CS225-final/OpenFlights-CS225-FinalProject/data/sample/sampleroutes.dat";
    string airports_path = "/workspaces/cs225/revised/release-f22/CS225-final/OpenFlights-CS225-FinalProject/data/sample/sampleairpots.dat";*/
    
    init.readRoutes(routes_path);
    
    // cout << "Read routes finished: " << endl;
    init.readAirports(airports_path);
    // cout << "read airports: " << endl;
    init.createAdjacencyList();

    init.printMap();
    init.savePNG("test");
    // should get output that matches DISCORD SCREENSHOT
    return 0;
}