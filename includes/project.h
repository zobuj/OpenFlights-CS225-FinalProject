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
#include <queue>
#include <stack>


using namespace std;
class Project {
    public:
        /**
         * Constructor: Constructs a Project Object which reads from a routes and airports dat file and
         *              creates an adjacency list and assigns edge weights
         *              Calls readRoutes, readAirports, createAdjacencyList, and createEdgeWeights
         * 
         * @param routes_path The path of the routes.dat file
         * @param airports_path The path of the airports.dat file
         * @param title Name of the file graph is written to.
         */
        Project(string routes_path, string airports_path,string title);

        /**
         * Data Parser
         * Reads from the routes.dat file and fills the from and to vectors whose indices store corresponding directed routes
         * 
         * @param path The path of the routes.dat file
         */
        void readRoutes(string path);

        /**
         * Data Parser
         * Reads from the airports.dat file and fills the airports, airportCode vectors, 
         * the latitudes map, longitudes map, and airportMap map for each airport
         * 
         * @param path The path of the airports.dat file
         */
        void readAirports(string path);

        /**
         * Creates Adjacency List of the graph based on the vector and maps loaded in the constructor.
         * Adjacency List is stored as a map where the key is an airport ID and
         * the value is a vector which contains all the neighbours of that airport.
         * 
         */
        void createAdjacencyList();

        /**
         * Assigns Edge Weights between connected airports
         * 
         * Traverses the from and to vectors and
         * uses calculates the distance between those airports based on their latitudes and longitudes.
         * 
         * Uses a map to store the edge weights whose key is a vector that stores the source airport at the zeroth index
         * and the destination at the first index and the value is the edge weight between those airport nodes.
         * 
         */
        void createEdgeWeights();
        /**
        * Prints the entire graph output that shows all airport nodes and connections between airports to a file.
        * It uses latitudes and longitudes to place nodes, so it ends up giving the shape of continents on the world map.
        *
        * @param title The name of the file to which the graph will be written
        */
        void printFullMap(string title) const;
        
        /**
         * Traverses the adjacency list using Depth First Search 
         * Searches for another airport in the starting aiports traversal
         * 
         * @param source the starting airport (or source) passed as a string
         * @param destinaion the destination airport passed as a string
         * @return a bool to indicate whether a path (or connection) exist between two airports
         */
        bool AirportConnection(string source, string destination);

        /**
         * Finds the airport node with the minimum edge weight out of all the nodes that have been reached through the sptSet.
         * 
         * Uses maps to store the reachability and shortest distance for every airport ID node.
         * 
         * @param dist The map that stores the shortest distance (value as double) for every airport ID node (key as int)
         * @param sptSet The map that stores the reachability (value as bool) for every airport ID node (key as int)
         * @return The airport ID with the minimum distance reachable based on the sptSet and dist maps
         */
        int minDistance(map<int, double> dist, map<int, bool> sptSet);

        /**
         * Main Algorithm
         * 
         * Implements Dijkstras Algorithm to build the Minimum Spanning Tree for a source airport ID
         * 
         * @param graph The adjacency list of the graph
         * @param source The source airport ID for which we build the minimum spanning tree
         * @return The minimum spanning tree for the source airport as a map
         */
        map<int, double> dijkstras(map<int, vector<int>> graph, int source);

        /**
         * Calls the dijkstras function to get the minimum spanning tree for the source airport ID.
         * The spanning tree is stord as a map with the key as diferent reachable airport ID nodes from the source.
         * This function returns the value of the shortest distance for the destination node stored in the map of the minimum spanning tree.
         * 
         * @param from The source airport ID
         * @param to The destination airport ID
         * @return The value of the shortest path between the source and destination airports
         */
        double shortestPath(string from, string to);

        // Helpers and Getters

        /**
         * Returns the from vector of airports IDs based on routes.dat
         * 
         * @return The from vector of airports IDs
         */
        vector<int> getFrom() const {return from;}

        /**
         * Returns the to vector of airports IDs based on routes.dat
         * 
         * @return The to vector of airports IDs
         */
        vector<int> getTo() const {return to;}

        /**
         * Returns the airportCode vector of airports IDs based on airports.dat
         * 
         * @return The airportCode vector storing 4 letter airport codes
         */
        vector<int> getAirports() const {return airports;}

        /**
         * Returns the latitudes map whose key is airport ID and value is the latitude for that aiport
         * 
         * @return The latitudes map storing airport latitudes
         */
        map<int, double> getLatitudes() const {return latitudes;}

        /**
         * Returns the longitudes map whose key is airport ID and value is the longitude for that aiport
         * 
         * @return The longitudes map storing airport longitudes
         */
        map<int, double> getLongitudes() const {return longitudes;}

        /**
         * Returns the adjacency list (map) whose key is airport ID and value is a vector storing all neighbouring airport IDs
         * 
         * @return The adjacency list of the graph
         */
        map<int, vector<int>> getGraph() const {return adjacencyLists;}

        /**
         * Returns the distance between two airports based on the Euclidian Distance betweem their latitudes and longitudes
         * 
         * @param latFrom The latitude of the source airport
         * @param longFrom The longitude of the source airport
         * @param latTo The latitude of the destination airport
         * @param longTo The longitude of the destination airport
         * @return The distance/edge weights between two airports
         */
        double calculateDistance(double latFrom, double longFrom, double latTo, double longTo);

        /**
         * Returns the airport code for a matching airport id
         *
         * @param id The Airport ID
         * @return Airport Code
         */
        string getCode(const int id)const;

        /**
         * Uses BFS to iterate through the adjacency list of the MST and returns the
         * shortest path.
         * @param Source The ID for the source airport
         * @param dest The ID for the destination airport
         * @return Vector storing the shortest path from source to destination
         */
        vector<int> findPath(int source, int dest);
        
        
    private:
        vector<int> from;
        vector<int> to;
        map<int, double> latitudes;
        map<int, double> longitudes;
        vector<int> airports;
        vector<string> airportCode;
        map<string, int> airportMap;
        map<int, vector<int> > adjacencyLists;
        map<int, vector<int> > adjacencyListDijkstras;
        map<int, bool> verticesLabel;
        map<vector<int>, double> edgesLabel;
        bool DFSHelper(int v, int w);
        void printMST(string title,string source,string destinaion)const;
        void printSinglePath(string name,string source,string dest);
};
