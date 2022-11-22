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
        bool DFSHelper(int from, int to);
    public:
        void readRoutes(string path);
        void readAirports(string path);
        void createAdjacencyList();
        void printMap();
        bool DFS(int from, int to);
        // to implement
};