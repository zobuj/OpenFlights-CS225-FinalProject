#include "../includes/extractData.h"

#include <fstream>
#include <iostream>
using namespace std;
// change this to your own paths

string getRoutesPath() {return "../OpenFlights-CS225-FinalProject/data/raw/routes.dat";}
//string getRoutesPath() {return "/Users/alexisserrano/Documents/CS225_FinalProject/OpenFlights-CS225-FinalProject/data/sample/sampleroutes.dat";}


string getAirportsPath() {return  "../OpenFlights-CS225-FinalProject/data/raw/airports.dat";}
//string getAirportsPath() {return  "/Users/alexisserrano/Documents/CS225_FinalProject/OpenFlights-CS225-FinalProject/data/sample/sampleairports.dat";}



int main() {

    



    Project init(getRoutesPath(),getAirportsPath());

    
    // init.printMap();
    
    // init.savePNG("presenting");
    // should get output that matches DISCORD SCREENSHOT

    
    //std::cout << "connection between 7 and 3: " + to_string(init.DFS(7, 3)) << std::endl;
    //init.printConnected(9,"DFS");
    // init.createEdgeWeights();
    // cout << "Shortest Path from Aamir's Airport to Zo_2 Airport: " << init.shortestPath(1, 6) << endl;

    return 0;
}