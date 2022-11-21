#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;
class Project {
    private:
        vector<int> from;
        vector<int> to;
        vector<double> latitudes;
        vector<double> longitudes;
        vector<int> airports;
        map<int, vector<int>> adjacencyLists;

    public:
        void readRoutes();
        void readAirports();
        void createAdjacencyList();
};