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
        map<int, bool> verticesLabel;
        vector<vector<int>> edgesLabel;
        //bool DFSHelper(int from, int to);
        void DFSHelper(int v);
    public:
        void readRoutes(string path);
        void readAirports(string path);
        void createAdjacencyList();
        void printMap();
        void savePNG(string title) const;
        //bool DFS(int from, int to);
        void DFS(int v);
        // to implement
};