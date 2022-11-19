#include "extractData.h"
#include <fstream>
#include <iostream>
using namespace std;
int main() {
    Project init;
    init.readRoutes();
    init.readAirports();
    init.createAdjacencyList();
    return 0;
}