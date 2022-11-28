#include "../includes/extractData.h"

#include <fstream>
#include <iostream>
using namespace std;
// change this to your own paths
string getRoutesPath() {return "/workspaces/cs225/revised/release-f22/OpenFlights-CS225-FinalProject/data/sample/sampleroutes.dat";}
string getAirportsPath() {return  "/workspaces/cs225/revised/release-f22/OpenFlights-CS225-FinalProject/data/sample/sampleairports.dat";}
int main() {
    Project init(getRoutesPath(),getAirportsPath());
    
    init.printMap();
    
    init.savePNG("test");
    
    init.DFS(9, 7);
    init.createEdgeWeights();

    return 0;
}