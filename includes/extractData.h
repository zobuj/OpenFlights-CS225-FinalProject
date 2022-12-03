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
        vector<string> airportCode;
        map<int, vector<int> > adjacencyLists;
        map<int, bool> verticesLabel;
        map<vector<int>, double> edgesLabel;
        //bool DFSHelper(int from, int to);
        bool DFSHelper(int v, int w);
        void printConnectedHelper(int v, string & neatoFile);
    public:
        void printCoord();
        Project(string routes_path, string airports_path);
        void readRoutes(string path);
        void readAirports(string path);
        void createAdjacencyList();
        void printMap();
        void savePNG(string title) const;
        //bool DFS(int from, int to);
        bool DFS(int v, int w);
        void printConnected(int v,string title);
        double calculateDistance(double latFrom, double longFrom, double latTo, double longTo);
        void createEdgeWeights();
        vector<int> getFrom() const {return from;}
        vector<int> getTo() const {return to;}
        vector<int> getAirports() const {return airports;}
        map<int, double> getLatitudes() const {return latitudes;}
        map<int, double> getLongitudes() const {return longitudes;}
        map<int, vector<int>> getMap() const {return adjacencyLists;}
        int minDistance(map<int, double> dist, map<int, bool> sptSet);
        map<int, double> dijkstras(map<int, vector<int>> graph, int source);
        double shortestPath(int from, int to);
};