#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>


#include <list>
#include <unordered_map>
#include <utility>
#include <algorithm>

#include <cstdlib>
#include <climits>


#include <iomanip>
#include <set>
#include <sstream>





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
        void savePNG(string title) const;
        void printTo();
        bool DFS(int from, int to);
        // to implement
};