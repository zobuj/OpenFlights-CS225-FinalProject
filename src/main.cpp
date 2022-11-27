#include "../includes/extractData.h"

#include <fstream>
#include <iostream>
using namespace std;
int main() {
    Project init;
    // cout << "made project: " << endl;
    string routes_path = "/Users/aryanmalhotra/Desktop/cs225project/OpenFlights-CS225-FinalProject/data/raw/routes.dat";
    string airports_path = "/Users/aryanmalhotra/Desktop/cs225project/OpenFlights-CS225-FinalProject/data/raw/airports.dat";
    
    init.readRoutes(routes_path);
    
    // cout << "Read routes finished: " << endl;
    init.readAirports(airports_path);
    // cout << "read airports: " << endl;
    init.createAdjacencyList();

    init.printMap();
    init.savePNG("test");
    // should get output that matches DISCORD SCREENSHOT
    //Testing simple DFS given a source code
    init.DFS(9);
    init.createEdgeWeights();

    return 0;
}