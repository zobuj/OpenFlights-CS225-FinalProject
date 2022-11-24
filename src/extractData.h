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
#include <math.h>




using namespace std;
class Project {
    private:
        vector<int> from;
        vector<int> to;
        map<int, double> latitudes;
        map<int, double> longitudes;
        vector<int> airports;
        map<int, vector<int>> adjacencyLists;
        map<int, bool> verticesLabel;
        map<vector<int>, double> edgesLabel;
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
        double calculateDistance(double latFrom, double longFrom, double latTo, double longTo);
        void createEdgeWeights();
        // to implement
};