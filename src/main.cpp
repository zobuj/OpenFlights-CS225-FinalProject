#include "../includes/project.h"

#include <fstream>
#include <iostream>
using namespace std;
// change this to your own paths
string getRoutesPath() {return "../OpenFlights-CS225-FinalProject/data/raw/routes.dat";}
//string getRoutesPath() {return "../OpenFlights-CS225-FinalProject/data/sample/sampleroutes.dat";}


string getAirportsPath() {return  "../OpenFlights-CS225-FinalProject/data/raw/airports.dat";}
//string getAirportsPath() {return  "../OpenFlights-CS225-FinalProject/data/sample/sampleairports.dat";}

int main() {

    Project init(getRoutesPath(),getAirportsPath());
    
    // init.printMap();
    // cout << "connection between Prof Evans Airport (9) and Zo_2 Airport (6): " + to_string(init.DFS("BGSF", "AYWK")) << endl;
    // cout << "Shortest Path from Prof Evans Airport (9) to Zo_2 Airport (6): " << init.shortestPath("BGSF", "AYWK") << endl;
    // init.printConnected(9,"DFS");

    init.printMap();
    cout << "connection between Keflavik International Airport (16) and Cambridge Bay Airport (32): " + to_string(init.AirportConnection("BIKF", "CYCB")) << endl;
    cout << "Shortest Path from Keflavik International Airport (16) to Cambridge Bay Airport (32): " << init.shortestPath("BIKF", "CYCB") << endl;
    init.savePNG("Path1");
    //init.printConnected(9,"DFS");

    //init.printCoord();
    
    //init.savePNG("test");
    // should get output that matches DISCORD SCREENSHOT

    
    //std::cout << "connection between 7 and 3: " + to_string(init.DFS(7, 3)) << std::endl;
    //cout << "Shortest Path from Aamir's Airport to Zo_2 Airport: " << init.shortestPath(1, 6) << endl;
    //init.savePNG("test");
    //cout << "Shortest Path from Aamir's Airport to Zo_2 Airport: " << init.shortestPath(1, 6) << endl;

    return 0;
}